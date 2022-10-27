/*************************************************************************
 * SINTEO project
 * Copyright (C) 2022 ISAE-SUPAERO / ONERA
*************************************************************************/

/*--------------------------- main.c -------------------------------------
 |  File main.c
 |
 |  Description:  Profiling functions are defined and used
 |                for analyzing the effect of different
 |                benchmarks on the system. A Linux module for
 |                enabling User mode access to the Performance Monitors
 |                is required. 
 |
 |  Version: 1.1
 |
 | Contact:
 | alfonso.mascarenas-gonzalez@isae-supaero.fr
 | jean-baptiste.chaudron@isae-supaero.fr
 | youcef.bouchebaba@onera.fr
 | frederic.boniol@onera.fr
 | jean-loup.bussenot@onera.fr
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
#include "arm_pmu_management.h"
#include "emif_management.h"


#define C_MATRIX_SIZE 1024
#define T1 500000

#define DDR3A_EMIF1_BASE_ADDRESS 0x4C000000
#define DDR3A_EMIF2_BASE_ADDRESS 0x4D000000


/* ----------------------- LOCAL FUNCTIONS DECLARATION ---------------- */

void *thread0(void *arg);
void *thread1(void *arg);
int main(int argc, char **argv);


/* ----------------------- GLOBAL VARIABLES --------------------------- */

// Dummy matrix to work with
unsigned int mat1[C_MATRIX_SIZE][C_MATRIX_SIZE];

// Virtual address for EMIF 0 and 1
void *ptr_emifA, *ptr_emifB;

// IDs for threads
pthread_t t0_id, t1_id;



/* ----------------------- LOCAL FUNCTIONS DEFINITION ----------------- */

void *thread0(void *arg){

 struct periodic_info info;
 unsigned int i,j,temp = 0, ctr = 0;
 unsigned long accum;

 make_periodic (T1, &info);

 while(1){
    // Read the DDR memory controller PMCs for the first time
    DDR_start_eval(ptr_emifA, ptr_emifB);

    // Read the PMUs for the first time
    critical_task_start_eval();

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

    // Read the PMUs for the second time and calculate the execution time
    critical_task_end_eval();

    // Read the DDR memory controller PMCs for the second time
    DDR_end_eval(ptr_emifA, ptr_emifB);

    // Print the metrics
    print_pmu_results(ctr);
    print_emif_results(ctr);


    temp = 0;
    ctr++;

    wait_period (&info);
  }

  return NULL;
}


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
  ptr_emifA = mmap(NULL,4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, DDR3A_EMIF1_BASE_ADDRESS);
  ptr_emifB = mmap(NULL,4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, DDR3A_EMIF2_BASE_ADDRESS);

  if (ptr_emifA == MAP_FAILED || ptr_emifB == MAP_FAILED) {
        perror("Can't map memory");
        return -1;
  }

  close(fd);

  // Configure the EMIFs
  DDR_configure_eval(1, ptr_emifA, ptr_emifB); // 1 = Filter by master enabled

  // Configure ARM Cortex A15 performance counters
  counters_init();

  // set CPU affinity of task 1
  cpu_set_t t0_mask;
  CPU_ZERO(&t0_mask);    // clear all CPUs
  CPU_SET(0, &t0_mask);    // select CPU 0

  // set CPU affinity of task 2
  cpu_set_t t1_mask;
  CPU_ZERO(&t1_mask);    // clear all CPUs
  CPU_SET(1, &t1_mask);    // select CPU 1


  //Lock the memory to avoid memory swapping
  mlockall(MCL_CURRENT | MCL_FUTURE);

  printf("\nTask profiling: Start-Stop pattern on ARMs \n");
  printf("Task profiling: Start-Read pattern on memory controller \n\n");

  char str[64];

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


