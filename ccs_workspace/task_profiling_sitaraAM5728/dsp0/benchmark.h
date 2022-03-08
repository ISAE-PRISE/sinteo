/*--------------------------- benchmarks.h -------------------------------------
 |  File benchmarks.h
 |
 |  Description:  Provides function able to stress a specific element
 |                of the multicore platform, e.g., DDR memory row,
 |                unified/shared cache.
 |
 |  Version: 1.0V
 *-----------------------------------------------------------------------*/

#ifndef BENCHMARK_H_
#define BENCHMARK_H_


/* cpu_microbenchmark_store
 *
 * Description: Executes 128 store instructions aiming to a specific location
 *
 * Parameter:
 *              - unsigned base_address: Address to where stores are issued
 *              - unsigned value: Value to store
 *
 * Returns:     Nothing
 *
 * */
void cpu_microbenchmark_store(unsigned address, unsigned value){
/*
    __asm__ __volatile("STW.D2T2 B4,*B15[4]");
    __asm__ __volatile("STW.D1T1 A3,*A4[0]");
    __asm__ __volatile("LDW.D2T2 *B15[2],B4");
    */
    volatile unsigned* store = address;

    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;
    *store = value;

if(0)
    printf("%d \n", *store);

}


/* cpu_microbenchmark_load
 *
 * Description: Executes 128 load instructions to retrieve a value from a specific location
 *
 * Parameter:
 *              - unsigned base_address: Address to where loads are issued
 *
 * Returns:     Nothing
 *
 * */
void cpu_microbenchmark_load(unsigned address){

    volatile unsigned* load = address;
    volatile unsigned temp = 0;


    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;
    temp = *load;

if(0)
    printf("%d \n", temp);

}


/* cpu_pointer_chasing_microbenchmark
 *
 * Description: Executes a continuous cyclical chain of loads by reading a pointer whose value contains the next address to read from. The last pointer contains the address to the first pointer.
 *              The address spacing is equivalent to a cache line size (stride), to force the use of a new cache line every time.
 *
 * Parameter:
 *              - unsigned iter_numb: Number of times we carry out 128 pointer reads
 *              - unsigned stride: Cache line size
 *              - unsigned array_size: Number of pointer chasing before starting the cycle again. Number of pointer jumps before cycle completion = array_size/stride
 *              - unsigned M[array_size]: Vector containing the pointers to the pointers
 *
 * Returns:     Nothing
 *
 * */
void cpu_pointer_chasing_microbenchmark(unsigned iter_numb, unsigned stride, unsigned array_size, unsigned M[array_size]){
    unsigned int *a, *b, i;

    for(i=0; i<array_size; i+=stride){
        if(i<array_size-stride)
            M[i] = (int*)&M[i+stride];
        else
            M[i] = (int*)M;
    }

    for (i = 0; i < iter_numb; i++) {
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
        b=*a; a=*b;
    }

}


/* sb0_benchmark
 *
 * Description: Synthetic benchmark whose aim is to cause stress at a given DDR memory bank and row. Use only without data caches enabled.
 *
 * Parameter:
 *              - unsigned base_address: Address of the DDR memory bank and row to stress
 *
 * Returns:     Nothing
 *
 * */
void bank_stress_benchmark(unsigned base_address){

    unsigned* temp = base_address;
    *temp = 0;
    unsigned* i = base_address + sizeof(unsigned);
    unsigned* size = base_address + 2*sizeof(unsigned);
    *size = 128; // *size < 256
    unsigned* in0 = base_address + 3*sizeof(unsigned);
    unsigned* in1 = base_address + 3*sizeof(unsigned) + (*size)*sizeof(unsigned);


  for ((*i)=0; (*i) < (*size); (*i)++)
      in0[(*i)]=(*i)+1;

  for ((*i)=0; (*i) < (*size); (*i)++)
      in1[(*i)]=in0[(*size)-(*i)];

  for ((*i)=0; (*i)<(*size); (*i)++)
      in0[(*i)]= in0[(*i)]+ in0[(*i)]*in1[(*i)];

  for ((*i)=0; (*i)<(*size); (*i)++)
      (*temp) +=in0[(*i)]+in1[(*i)];


if(0)
    printf("%u", (*temp));


}


/* matrix_stress1_task
 *
 * Description: Task that makes use of matrices to create interference
 *
 * Parameter:
 *              - unsigned size: Indicates the size of the matrices
 *              - int in0[size][size]: First matrix
 *              - int in1[size][size]: Second matrix
 *
 * Returns:     Nothing
 *
 * */
void matrix_stress1_task(unsigned size, int in0[size][size], int in1[size][size])  {
    unsigned i = 0, j = 0;
   for (i=0; i < size; i++)
       for (j=0; j < size; j++)
           in0[i][j]=i+j+1;

   for (i=0; i < size; i++)
       for (j=0; j < size; j++)
           in1[i][j]=in0[i-1][j]+in0[i][j-1]+in0[i][j]+in0[i][j+1]+in0[i+1][j];
}

/* matrix_stress2_task
 *
 * Description: Task that makes use of matrices to create interference
 *
 * Parameter:
 *              - unsigned size: Indicates the size of the matrices
 *              - int in0[size][size]: First matrix
 *              - int in1[size][size]: Second matrix
 *
 * Returns:     Nothing
 *
 * */
void matrix_stress2_task(unsigned size, int in0[size][size], int in1[size][size])  {
    unsigned i = 0, j = 0;
   for (i=0; i < size; i++)
       for (j=0; j < size; j++)
           in0[i][j]=i+j+1;

   for (i=0; i < size; i++)
       for (j=0; j < size; j++)
           in1[i][j]=in0[j][i-1]+in0[j-1][i]+in0[j][i]+in0[j+1][i]+in0[j][i+1];

}




#endif /* BENCHMARK_H_ */
