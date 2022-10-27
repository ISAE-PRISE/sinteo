/*--------------------------- benchmarks.h -------------------------------------
 |  File benchmarks.h
 |
 |  Description:  Provides function able to stress a specific element
 |                of the multicore platform, e.g., DDR memory row,
 |                unified/shared cache.
 |
 |  Version: 1.1
 *-----------------------------------------------------------------------*/


#ifndef BENCHMARKS_H_
#define BENCHMARKS_H_


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
void cpu_microbenchmark_store(unsigned base_address, unsigned value){

    __asm__ (" mov r2, %0" :: "r" (value));
    __asm__ (" mov r1, %0" :: "r" (base_address));

    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
    __asm__ __volatile(" str r2, [r1]");
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
void cpu_microbenchmark_load(unsigned base_address){

    __asm__(" mov r1, %0" :: "r" (base_address));

    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");
    __asm__ __volatile(" ldr r2, [r1]");

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
 *
 * Returns:     Nothing
 *
 * */
void cpu_pointer_chasing_microbenchmark(unsigned iter_numb, unsigned stride, unsigned array_size){
    volatile unsigned int *a, *b, i;
    volatile unsigned int M[array_size];
    a = (unsigned*)&M;

    for(i=0; i<array_size; i+=stride){
        if(i<array_size-stride)
            M[i] = (unsigned)&M[i+stride];
        else
            M[i] = (unsigned)M;
    }

    for (i = 0; i < iter_numb; i++) {
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
        b=(unsigned*)*a; a= (unsigned*)*b;
    }

}


/* sb0_benchmark
 *
 * Description: Synthetic benchmark whose aim is to cause stress at a given DDR memory bank and row. Use only without data caches enabled.
 *
 * Parameter:
 *              - unsigned base_address: Address of the DDR memory bank and row to stress
 *
 * Returns:     Dummy array addition
 *
 * */
unsigned bank_stress_benchmark(unsigned base_address){

    unsigned* temp = (unsigned*)base_address;
    *temp = 0;
    unsigned* i = (unsigned*)base_address + sizeof(unsigned);
    unsigned* size = (unsigned*)base_address + 2*sizeof(unsigned);
    *size = 128; // *size < 256
    unsigned* in0 = (unsigned*)base_address + 3*sizeof(unsigned);
    unsigned* in1 = (unsigned*)base_address + 3*sizeof(unsigned) + (*size)*sizeof(unsigned);


  for ((*i)=0; (*i) < (*size); (*i)++)
      in0[(*i)]=(*i)+1;

  for ((*i)=0; (*i) < (*size); (*i)++)
      in1[(*i)]=in0[(*size)-(*i)];

  for ((*i)=0; (*i)<(*size); (*i)++)
      in0[(*i)]= in0[(*i)]+ in0[(*i)]*in1[(*i)];

  for ((*i)=0; (*i)<(*size); (*i)++)
      (*temp) +=in0[(*i)]+in1[(*i)];


  return *temp;
}


/* matrix_stress1_task
 *
 * Description: Task that makes use of matrices to create interference
 *
 * Parameter:
 *              - unsigned size: Indicates the size of the matrices. Final memory usage is (number of matrices (2) * unsigned size (4) * size*size)
 *
 * Returns:     A dummy sum
 *
 * */
unsigned matrix_stress1_task(unsigned size)  {
   volatile int in0[size][size];
   volatile int in1[size][size];
   volatile int sum = 0;

   for (unsigned i=0; i < size; i++)
       for (unsigned j=0; j < size; j++)
           in0[i][j]=i+j+1;

   for (unsigned i=0; i < size; i++)
       for (unsigned j=0; j < size; j++)
           in1[i][j]=in0[i-1][j]+in0[i][j-1]+in0[i][j]+in0[i][j+1]+in0[i+1][j];

   for (unsigned i=0; i < size; i++)
       for (unsigned j=0; j < size; j++)
           sum+=in1[i][j];

   return sum;
}

/* matrix_stress2_task
 *
 * Description: Task that makes use of matrices to create interference
 *
 * Parameter:
 *              - unsigned size: Indicates the size of the matrices. Final memory usage is (number of matrices (2) * unsigned size (4) * size*size)
 *
 * Returns:     A dummy sum
 *
 * */
unsigned matrix_stress2_task(unsigned size)  {
   volatile int in0[size][size];
   volatile int in1[size][size];
   volatile int sum = 0;

   for (unsigned i=0; i < size; i++)
       for (unsigned j=0; j < size; j++)
           in0[i][j]=i+j+1;

   for (unsigned i=0; i < size; i++)
       for (unsigned j=0; j < size; j++)
           in1[i][j]=in0[j][i-1]+in0[j-1][i]+in0[j][i]+in0[j+1][i]+in0[j][i+1];

   for (unsigned i=0; i < size; i++)
       for (unsigned j=0; j < size; j++)
           sum+=in1[i][j];

   return sum;
}




#endif /* BENCHMARKS_H_ */
