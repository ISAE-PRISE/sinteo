/*************************************************************************
 * SINTEO project
 * Copyright (C) 2022 ISAE-SUPAERO / ONERA
*************************************************************************/

/*--------------------------- main.c -------------------------------------
 |  File main.c
 |
 |  Description:  Profiling functions are defined and used
 |                for analyzing the effect of 
 |                benchmarks on the Sitara AM5728 SoC.
 |                The current configuration makes two ARM Cortex A15
 |				  execute in parallel.
 |				  Alchemy API is used.
 |
 |  Version: 1.0V
 |
 |  Contact:
 |  alfonso.mascarenas-gonzalez@isae-supaero.fr
 |  jean-baptiste.chaudron@isae-supaero.fr
 |  youcef.bouchebaba@onera.fr
 |  frederic.boniol@onera.fr
 |  jean-loup.bussenot@onera.fr
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>

#include "DDR3MemoryController.h"

#define LOOP_PERIOD 1e9 //Expressed in ticks

// Define dummy matrices size
#define C_MATRIX_SIZE 1024
#define NC_MATRIX_SIZE 1024

// Tasks to use
RT_TASK critical_task, noncritical_task;

// Dummy matrices to work with
unsigned int mat1[C_MATRIX_SIZE][C_MATRIX_SIZE];
unsigned int mat2[NC_MATRIX_SIZE][NC_MATRIX_SIZE];

// EMIF0 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif0,t2_ddr_cycles_emif0, result_ddr_cycles_emif0, t1_ddr_evt0_emif0, t2_ddr_evt0_emif0, result_ddr_evt0_emif0, t1_ddr_evt1_emif0, t2_ddr_evt1_emif0, result_ddr_evt1_emif0;
// EMIF1 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif1,t2_ddr_cycles_emif1, result_ddr_cycles_emif1, t1_ddr_evt0_emif1, t2_ddr_evt0_emif1, result_ddr_evt0_emif1, t1_ddr_evt1_emif1 ,t2_ddr_evt1_emif1, result_ddr_evt1_emif1;

// Virtual address for EMIF 0 and 1
void *ptr_emifA;
void *ptr_emifB;


/* DDR_configure_eval
 *
 * Description: Sets the performance counters events and master (MSTID) from who the event are captured.
 *
 *
 * Parameter:
 *              - unsigned filter_events: Chooses whether to filter by master ID or to globally analyze the system
 * 		        - void* emif0_addr: Indicates the base address of the EMIF 0
 *              - void* emif1_addr: Indicates the base address of the EMIF 1
 *
 * Returns:     Nothing
 *
 * */
void DDR_configure_eval(unsigned filter_events, void* emif0_addr, void* emif1_addr){
    /* EMIF1, performance counter 0 */
    set_PERF_CNT_EVENT(0, 0x0, emif0_addr);

    if (filter_events){
        enable_CNT_MSTID(0, emif0_addr);
        set_MSTID(0, 0x0, emif0_addr); // Filter by Master ID
    }

    /* EMIF1, performance counter 1 */
    set_PERF_CNT_EVENT(1, 0x1, emif0_addr);

    if (filter_events){
        enable_CNT_MSTID(1, emif0_addr);
        set_MSTID(1, 0x0, emif0_addr); // Filter by Master ID
    }

    /* EMIF2, performance counter 0 */
    set_PERF_CNT_EVENT(0, 0x0, emif1_addr);

    if (filter_events){
        enable_CNT_MSTID(0, emif1_addr);
        set_MSTID(0, 0x0, emif1_addr); // Filter by Master ID
    }

    /* EMIF2, performance counter 1 */
    set_PERF_CNT_EVENT(1, 0x1, emif1_addr);

    if (filter_events){
        enable_CNT_MSTID(1, emif1_addr);
        set_MSTID(1, 0x0, emif1_addr); // Filter by Master ID
    }
}



/* DDR_start_eval
 *
 * Description: Reads both EMIFs performance counters for the first time.
 *
 * Parameter:
 * 		        - void* emif0_addr: Indicates the base address of the EMIF 0
 *              - void* emif1_addr: Indicates the base address of the EMIF 1
 *
 * Returns:     Nothing
 *
 * */
void DDR_start_eval(void* emif0_addr, void* emif1_addr){
    t1_ddr_evt0_emif0 = get_PERF_CNT_1(emif0_addr);
    t1_ddr_evt1_emif0 = get_PERF_CNT_2(emif0_addr);
    t1_ddr_cycles_emif0 = get_PERF_CNT_TIMER(emif0_addr);

    t1_ddr_evt0_emif1 = get_PERF_CNT_1(emif1_addr);
    t1_ddr_evt1_emif1 = get_PERF_CNT_2(emif1_addr);
    t1_ddr_cycles_emif1 = get_PERF_CNT_TIMER(emif1_addr);
}

/* DDR_end_eval
 *
 * Description: Reads both EMIFs performance counters a final time and calculates the final time.
 *
 * Parameter:
 * 		        - void* emif0_addr: Indicates the base address of the EMIF 0
 *              - void* emif1_addr: Indicates the base address of the EMIF 1
 *
 * Returns:     Nothing
 *
 * */
void DDR_end_eval(void* emif0_addr, void* emif1_addr){
    t2_ddr_evt0_emif0 = get_PERF_CNT_1(emif0_addr);
    t2_ddr_evt1_emif0 = get_PERF_CNT_2(emif0_addr);
    t2_ddr_cycles_emif0 = get_PERF_CNT_TIMER(emif0_addr);

    t2_ddr_evt0_emif1 = get_PERF_CNT_1(emif1_addr);
    t2_ddr_evt1_emif1 = get_PERF_CNT_2(emif1_addr);
    t2_ddr_cycles_emif1 = get_PERF_CNT_TIMER(emif1_addr);

    result_ddr_cycles_emif0 = t2_ddr_cycles_emif0 - t1_ddr_cycles_emif0;
    result_ddr_evt0_emif0 = t2_ddr_evt0_emif0 - t1_ddr_evt0_emif0;
    result_ddr_evt1_emif0 = t2_ddr_evt1_emif0 - t1_ddr_evt1_emif0;

    result_ddr_cycles_emif1 = t2_ddr_cycles_emif1 - t1_ddr_cycles_emif1;
    result_ddr_evt0_emif1 = t2_ddr_evt0_emif1 - t1_ddr_evt0_emif1;
    result_ddr_evt1_emif1 = t2_ddr_evt1_emif1 - t1_ddr_evt1_emif1;

}

/* critical_task_proc
 *
 * Description: Dummy periodic benchmark with metric measurement capabililties
 *
 * Parameter:   
 *              - void* arg: General pointer
 *
 * Returns:     Nothing
 *
 * */
void critical_task_proc(void *arg){

  //Make the task periodic with a specified loop period
  rt_task_set_periodic(NULL, TM_NOW, LOOP_PERIOD);

  unsigned long int t1=0, t2=0, tdiff=0;
  unsigned int i,j,temp = 0, ctr = 0;

  //Start the dummy task loop
  while(1){
    DDR_start_eval(ptr_emifA, ptr_emifB);

    t1 = rt_timer_read();

    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                mat1[i][j] = i+j;
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                mat1[i][j] = mat1[j][i]+i;
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                temp = temp + mat1[j][i];

    t2 = rt_timer_read();
    tdiff = t2-t1;

    DDR_end_eval(ptr_emifA, ptr_emifB);

    printf("%u %u %lu %u \n", ctr, C_MATRIX_SIZE, tdiff, temp);
    printf("%u %u %u %u %u %u %u\n\r", ctr, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0, result_ddr_cycles_emif1, result_ddr_evt0_emif1, result_ddr_evt1_emif1);

    temp = 0;
    ctr++;

    rt_task_wait_period(NULL);
  }
}


/* noncritical_task_proc
 *
 * Description: Dummy periodic benchmark
 *
 * Parameter:   
 *              - void* arg: General pointer
 *
 * Returns:     Nothing
 *
 * */
void noncritical_task_proc(void *arg){

  //Make the task periodic with a specified loop period
  rt_task_set_periodic(NULL, TM_NOW, LOOP_PERIOD);

  unsigned long int t1=0, t2=0, tdiff=0;
  unsigned int i,j,temp = 0;

  //Start the dummy task loop
while(1){

    for(i = 0; i<NC_MATRIX_SIZE; i++)
        for(j = 0; j<NC_MATRIX_SIZE; j++)
                mat2[i][j] = i+j;
    for(i = 0; i<NC_MATRIX_SIZE; i++)
        for(j = 0; j<NC_MATRIX_SIZE; j++)
                mat2[i][j] = mat1[j][i]+i;
    for(i = 0; i<NC_MATRIX_SIZE; i++)
        for(j = 0; j<NC_MATRIX_SIZE; j++)
                temp = temp + mat2[j][i];

    temp = 0;

    rt_task_wait_period(NULL);

  }

}


int main(int argc, char **argv){

 // Access the memory file and extract the virtual address for both EMIFs
  int fd = open("/dev/mem", O_RDWR);
  ptr_emifA = mmap(NULL,4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, DDR3A_EMIF1_CONFIGURATION);
  ptr_emifB = mmap(NULL,4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, DDR3A_EMIF1_CONFIGURATION);

  if (ptr_emifA == MAP_FAILED || ptr_emifB == MAP_FAILED) {
        perror("Can't map memory");
        return -1;
  }

  close(fd);

  // Configure the EMIFs
  DDR_configure_eval(1, ptr_emifA, ptr_emifB);

  // set tasks affinity
  cpu_set_t critical_mask, noncritical_mask;
  CPU_ZERO(&critical_mask);    // clear all CPUs
  CPU_SET(0, &critical_mask);    // select CPU 0
  CPU_ZERO(&noncritical_mask);    // clear all CPUs
  CPU_SET(1, &noncritical_mask);    // select CPU 1

  //Lock the memory to avoid memory swapping for this program
  mlockall(MCL_CURRENT | MCL_FUTURE);

  char str[64];
  char non_str[64];

  printf("\nTask profiling: Start-Read pattern on ARMs \n");
  printf("Task profiling: Start-Read pattern on memory controller \n\n");

  //Create the real time tasks
  sprintf(str, "main_task");
  sprintf(str, "noncritical_task");

  rt_task_create(&critical_task, str, 0, 99, 0);
  printf("Affinity status: %d \n",rt_task_set_affinity(&critical_task, &critical_mask));

  rt_task_create(&noncritical_task, non_str, 0, 50, 0);
  printf("Affinity status: %d \n",rt_task_set_affinity(&noncritical_task, &noncritical_mask));

  //Since task starts in suspended mode, start task
  rt_task_start(&noncritical_task, &noncritical_task_proc, 0);
  rt_task_start(&critical_task, &critical_task_proc, 0);

  //Wait for Ctrl-C
  pause();

  return 0;
}
