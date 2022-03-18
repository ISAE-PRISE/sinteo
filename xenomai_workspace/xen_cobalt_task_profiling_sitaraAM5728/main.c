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
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <errno.h>

#include "periodic_task.h"
#include "DDR3MemoryController.h"

// Define dummy matrix size
#define C_MATRIX_SIZE 1024

// Thread period
#define T1 500000

// Dummy matrix to work with
unsigned int mat1[C_MATRIX_SIZE][C_MATRIX_SIZE];

// EMIF0 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif0,t2_ddr_cycles_emif0, result_ddr_cycles_emif0, t1_ddr_evt0_emif0, t2_ddr_evt0_emif0, result_ddr_evt0_emif0, t1_ddr_evt1_emif0, t2_ddr_evt1_emif0, result_ddr_evt1_emif0;
// EMIF1 performance counters initial and final read variables
unsigned t1_ddr_cycles_emif1,t2_ddr_cycles_emif1, result_ddr_cycles_emif1, t1_ddr_evt0_emif1, t2_ddr_evt0_emif1, result_ddr_evt0_emif1, t1_ddr_evt1_emif1 ,t2_ddr_evt1_emif1, result_ddr_evt1_emif1;

// Virtual address for EMIF 0 and 1
void *ptr_emifA;
void *ptr_emifB;

// IDs for threads
pthread_t t0_id, t1_id;


/* DDR_configure_eval
 *
 * Description: Sets the performance counters events and master (MSTID) from who the event are captured.
 *
 *
 * Parameter:
 *              - unsigned filter_events: Chooses whether to filter by master ID or to globally analyze the system
 *              - void* emif0_addr: Indicates the base address of the EMIF 0
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
 *              - void* emif0_addr: Indicates the base address of the EMIF 0
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
 *              - void* emif0_addr: Indicates the base address of the EMIF 0
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

/* thread0
 *
 * Description: Dummy periodic benchmark with metric measurement capabililties
 *
 * Parameter:   
 *              - void* arg: General pointer
 *
 * Returns:     Nothing
 *
 * */
void* thread0(void* arg){

 struct periodic_info info;
 unsigned int i,j,temp = 0, ctr = 0;
 unsigned long accum;
 struct timespec start, stop;

 make_periodic (T1, &info);

 while(1){
    // Read the DDR memory controller PMCs for the first time
    DDR_start_eval(ptr_emifA, ptr_emifB);

    // Read the clock for the first time
    if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
      perror("clock gettime");
      exit(EXIT_FAILURE);
    }

    // Dummy task
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                mat1[i][j] = i+j;
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                mat1[i][j] = mat1[j][i]+i;
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                temp = temp + mat1[j][i];


    // Read the clock for the second time
    if(clock_gettime(CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit(EXIT_FAILURE);
    }

    // Read the DDR memory controller PMCs for the second time
    DDR_end_eval(ptr_emifA, ptr_emifB);

    // Calculate the execution time
    accum = ( stop.tv_sec - start.tv_sec )
       	  + ( stop.tv_nsec - start.tv_nsec );

    // Print the metrics
    printf("%u %u %lu %u \n", ctr, C_MATRIX_SIZE, accum, temp);
    printf("%u %u %u %u %u %u %u \n", ctr, result_ddr_cycles_emif0, result_ddr_evt0_emif0, result_ddr_evt1_emif0, result_ddr_cycles_emif1, result_ddr_evt0_emif1, result_ddr_evt1_emif1);

    temp = 0;
    ctr++;

    wait_period (&info);
  }

  return NULL;
}

/* thread1
 *
 * Description: Dummy periodic benchmark
 *
 * Parameter:   
 *              - void* arg: General pointer
 *
 * Returns:     Nothing
 *
 * */
void *thread1(void *arg){

 struct periodic_info info;
 unsigned int i,j,temp = 0;

 make_periodic (T1, &info);

 while(1){

    // Dummy task
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                mat1[i][j] = i+j;
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                mat1[i][j] = mat1[j][i]+i;
    for(i = 0; i<C_MATRIX_SIZE; i++)
        for(j = 0; j<C_MATRIX_SIZE; j++)
                temp = temp + mat1[j][i];

    temp = 0;

    wait_period (&info);
  }

  return NULL;
}


int main(int argc, char **argv){
  // Access the memory file and extract the virtual address for both EMIFs
  int fd = open("/dev/mem", O_RDWR);
  ptr_emifA = mmap(NULL,4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, DDR3A_EMIF1_CONFIGURATION);
  ptr_emifB = mmap(NULL,4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, DDR3A_EMIF2_CONFIGURATION);

  if (ptr_emifA == MAP_FAILED || ptr_emifB == MAP_FAILED) {
        perror("Can't map memory");
        return -1;
  }

  close(fd);

  // Configure the EMIFs
  DDR_configure_eval(1, ptr_emifA, ptr_emifB);

  // set task 0 affinity
  cpu_set_t t0_mask;
  CPU_ZERO(&t0_mask);    // clear all CPUs
  CPU_SET(0, &t0_mask);    // select CPU 0

  // set task 1 affinity
  cpu_set_t t1_mask;
  CPU_ZERO(&t1_mask);    // clear all CPUs
  CPU_SET(1, &t1_mask);    // select CPU 1

  //Lock the memory to avoid memory swapping
  mlockall(MCL_CURRENT | MCL_FUTURE);

  printf("\nTask profiling: Start-Read pattern on ARMs \n");
  printf("Task profiling: Start-Read pattern on memory controller \n\n");

  // Set priorities
  struct sched_param t0_param = {.sched_priority = 71 };
  struct sched_param t1_param = {.sched_priority = 70 };

 // Set up task 0 thread attributes
  pthread_attr_t t0_attr;
  pthread_attr_init(&t0_attr);
  pthread_attr_setdetachstate(&t0_attr, PTHREAD_CREATE_JOINABLE);
  pthread_attr_setinheritsched(&t0_attr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&t0_attr, SCHED_FIFO);
  pthread_attr_setschedparam(&t0_attr, &t0_param);
  pthread_attr_setaffinity_np(&t0_attr, sizeof(cpu_set_t), &t0_mask);

 // Set up task 1 thread attributes
  pthread_attr_t t1_attr;
  pthread_attr_init(&t1_attr);
  pthread_attr_setdetachstate(&t1_attr, PTHREAD_CREATE_JOINABLE);
  pthread_attr_setinheritsched(&t1_attr, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&t1_attr, SCHED_FIFO);
  pthread_attr_setschedparam(&t1_attr, &t1_param);
  pthread_attr_setaffinity_np(&t1_attr, sizeof(cpu_set_t), &t1_mask);

  // Create task 0
  errno = pthread_create(&t0_id, &t0_attr, &thread0, NULL);
  if (errno)
  	printf("task0 pthread_create error %u \n", errno);

  // Create task 1
  errno = pthread_create(&t1_id, &t1_attr, &thread1, NULL);
  if (errno)
        printf("task1 pthread_create error %u \n", errno);


  pthread_join(t0_id, NULL);
  pthread_join(t1_id, NULL);

  //Wait for Ctrl-C
  pause();

  return 0;
}


