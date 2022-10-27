/*--------------------------- PMH.h -------------------------------------
 |  File PMH.h
 |
 |  Description: This file provides functions for managing the
 |  ARM Performance Monitor Hardware
 |
 |  Version: 2.1
 *-----------------------------------------------------------------------*/

#define PMSELR_MASK  0xFFFFFFE0
#define PMXEVTYPER_MASK  0xFFFFFF00
#define PMCNTENSET_MASK  0x7FFFFFC0
#define PMCR_MASK  0xFFFFFFC0
#define PMCNTENCLR_MASK  0x7FFFFFC0
#define PMOVSR_MASK  0x7FFFFFC0


/* select_evt_counter
 *
 * Description: The counter used in the coprocessor is selected, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int counter_id_f: Indicates which counter is selected (between 0 and 5 in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void select_evt_counter(int counter_id_f)  {
	   unsigned int value=0;
     __asm__ __volatile("mrc p15, 0, %0, c9, c12, 5" : "=r"(value));

	 __asm__ __volatile("mcr p15, 0, %0, c9, c12, 5" :: "r"((value&PMSELR_MASK)|counter_id_f));

}

/* event_track
 *
 * Description: The event type is selected, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int event_id_f: Indicates which event is selected (between 0x00 and 0x7E in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void event_track(int event_id_f)  {
	  unsigned int value=0;
	  __asm__ __volatile("mrc p15, 0, %0, c9, c13, 1" : "=r"(value));
      __asm__ __volatile("mcr p15, 0, %0, c9, c13, 1" :: "r"((value&PMXEVTYPER_MASK)|event_id_f));
}


/* enable_evt_counter
 *
 * Description: Enables the counters to be used, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int counter_id_f: Indicates which counter you want to enable (between 0 and 5 in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void enable_evt_counter(int counter_id_f)  {
	 unsigned int value=0;
   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) | 1<<counter_id_f)); // 0x80000000 = Cycle counter enable set

}

/* enable_evt_counters
 *
 * Description: Enables the counters to be used, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int counter_id_f: Indicates which counters you want to enable (between 0x0 and 0x3F in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void enable_evt_counters(int counter_id_f)  {
	 unsigned int value=0;
   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) | counter_id_f)); // 0x80000000 = Cycle counter enable set

}


/* enable_all_counters
 *
 * Description: Enables the cycle and event counters to be used, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int counter_id_f: Indicates which EVT counters you want to enable (between 0x0 and 0x3F in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void enable_all_counters(int counter_id_f)  {
	 unsigned int value=0;

  __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
  __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) | (counter_id_f) | (0x80000000))); // 0x80000000 = Cycle counter enable set

}


/* disable_counters
 *
 * Description: Disables all the counters leaving just the reserved bits.
 *
 * Parameter:
 * 				- int counter_id_f: Indicates which EVT counters you want to enable (between 0x0 and 0x3F in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void disable_counters(int counter_id_f) {
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 2" :: "r" (PMCNTENCLR_MASK | counter_id_f));

}

/* disable_all_counters
 *
 * Description: Disables all the counters leaving just the reserved bits.
 *
 * Parameter:
 * 				- int counter_id_f: Indicates which EVT counters you want to enable (between 0x0 and 0x3F in ARM Cortex A15)
 *
 * Returns:		Nothing
 *
 * */
static inline void disable_all_counters(int counter_id_f) {
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 2" :: "r" (PMCNTENCLR_MASK | counter_id_f | (0x80000000))); // 0x80000000 = Cycle counter disable set

}



/* reset_evt_counter
 *
 * Description: Enables all counters and resets the general counters and setting its count divider, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int enable_divider: Indicates if cycle count divider is used(0 or 1)
 *
 * Returns:		Nothing
 *
 * */
static inline void reset_evt_counter(unsigned int enable_divider) {
	unsigned int value=0;
	unsigned int temp=0;

	temp = (1 | 2);
	if (enable_divider)
		temp |= 8;

   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 0" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 0" :: "r" ((value & PMCR_MASK) | temp));
}

/* reset_all_counter
 *
 * Description: Enables and resets the general counters as well as the selected cycle counter and setting its count divider (if required), without modifying the reserved bits.
 *
 * Parameter:
 * 				- int enable_divider: Indicates if cycle count divider is used(0 or 1)
 *
 * Returns:		Nothing
 *
 * */
static inline void reset_all_counters(unsigned int enable_divider) {
	unsigned int value=0;
	unsigned int temp=0;

	temp = (1 | 2 | 4);
	if (enable_divider)
		temp |= 8;

   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 0" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 0" :: "r" ((value & PMCR_MASK) | temp));

}

/* enable_counter_divider
 *
 * Description: Enables the clock divider. PMCCNTR counts every clock cycle.
 *
 * Parameter:
 *              None
 *
 * Returns:     Nothing
 *
 * */
static inline void enable_counter_divider() {
    unsigned int value=0;
    unsigned int temp=0;

    temp = 0x8;
   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 0" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 0" :: "r" ((value & PMCR_MASK) | temp));

}

/* read_evt_counter
 *
 * Description: Reads the event counter register (Performance Monitor Count Registers).
 *
 * Parameter:
 *              None
 *
 *
 * Returns:		The event value is returned
 *
 * */
static inline unsigned int read_evt_counter()  {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c9, c13, 2\t\n": "=r"(value));
   return value;
}


/* enable_cycle_counter
 *
 * Description: Enables only the cycle counter, without modifying the reserved bits.
 *
 * Parameter:
 * 				None
 *
 * Returns:		Nothing
 *
 * */
static inline void enable_cycle_counter()  {
	 unsigned int value=0;

   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) |(0x80000000)));

}


/* reset_cycle_counter
 *
 * Description: Enables all counters as well as reseting cycle counter value and setting its count divider, without modifying the reserved bits.
 *
 * Parameter:
 * 				- int enable_divider: Indicates if cycle count divider is used(0 or 1)
 *
 * Returns:		Nothing
 *
 * */
static inline void reset_cycle_counter(unsigned int enable_divider) {
	unsigned int value=0;
	unsigned int temp=0;
	temp = 1|4;
	if (enable_divider)
		temp |= 8;
  __asm__ __volatile("mrc p15, 0, %0, c9, c12, 0" : "=r" (value));
  __asm__ __volatile("mcr p15, 0, %0, c9, c12, 0" :: "r" ((value & PMCR_MASK) | temp));

}


/* read_cycle_counter
 *
 * Description: Reads the Cycle Counter Register (CCNT).
 *
 * Parameter:   None
 *
 *
 * Returns:		The cycle counter value is returned
 *
 * */
static inline unsigned int read_cycle_counter()  {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));
   return value;
}

/* read_counters_overflow
 *
 * Description: Reads the Performance Monitor Overflow Flag Status Register (PMSOVSR ).
 *
 * Parameter:   None
 *
 *
 * Returns:     The counters overflow flags are returned
 *
 * */
static inline unsigned int read_counters_overflow()  {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c9, c12, 3\t\n": "=r"(value));

   return (value&0x8000003F); // MSB = Counter cycle overflow
}

/* clear_overflows
 *
 * Description: Clears all counters overflows flags (MSB = Counter cycle overflow)
 *
 * Parameter:   None
 *
 *
 * Returns:		Nothing
 *
 * */
static inline void clear_overflows()  {
	unsigned int value=0;

	__asm__ __volatile("MRC p15, 0, %0, c9, c12, 3" : "=r"(value));
	__asm__ __volatile("MCR p15, 0, %0, c9, c12, 3" :: "r"((value & PMOVSR_MASK) | 0x8000003F));
}


/* Example of use */
/*
	unsigned long value0i = 0, value0f = 0, diff0 = 0, value1i  = 0, value1f = 0, diff1 = 0, value2i = 0, value2f = 0, diff2 = 0, value3i = 0, value3f = 0, diff3 = 0,
             value4i = 0, value4f = 0, diff4 = 0, value5i = 0, value5f = 0, diff5 = 0, valueCi = 0, valueCf = 0, diffC = 0;

	// Counter to use
	#define counter_id_0 0x0
	#define counter_id_1 0x1
	#define counter_id_2 0x2
	#define counter_id_3 0x3
	#define counter_id_4 0x4
	#define counter_id_5 0x5

    // Event identification
	#define event_id_0   0x11
	#define event_id_1   0x04
	#define event_id_2   0x03
	#define event_id_3   0x16
	#define event_id_4   0x17
	#define event_id_5   0x10
	
	// Select counter to program: counter_number can be between 0-5
	select_evt_counter(counter_id_0);

	// Select event to track in selected counter: event_id numbers are in the ARM A15 TRM
	event_track(event_id_0);

	select_evt_counter(counter_id_1);
	event_track(event_id_1);

	select_evt_counter(counter_id_2);
	event_track(event_id_2);

	select_evt_counter(counter_id_3);
	event_track(event_id_3);

	select_evt_counter(counter_id_4);
	event_track(event_id_4);

	select_evt_counter(counter_id_5);
	event_track(event_id_5);

	// Clear possible overflows of every counter
    clear_overflows();

    // Select counter to program: counter_number can be between 0-5
    select_evt_counter(counter_id_0);

    // Reset the actual value and enables the counter and don't enable the divider
    reset_all_counters(0);

    // Start reading the event's register (save current value)
    value0i=read_evt_counter();

    select_evt_counter(counter_id_1);
    reset_all_counters(0);
    value1i=read_evt_counter();

    select_evt_counter(counter_id_2);
    reset_all_counters(0);
    value2i=read_evt_counter();

    select_evt_counter(counter_id_3);
    reset_all_counters(0);
    value3i=read_evt_counter();

    select_evt_counter(counter_id_4);
    reset_all_counters(0);
    value4i=read_evt_counter();

    select_evt_counter(counter_id_5);
    reset_all_counters(0);
    value5i=read_evt_counter();

    reset_all_counters(0);
    valueCi = read_cycle_counter();

    // Synchronize context (Instruction Synchronization Barrier)
    __asm__ __volatile("isb");

    // Enable counters
    enable_all_counters(0x3F);

    *** Do something ***

    // Disable counters
    disable_all_counters(0x3F);

    select_evt_counter(counter_id_0);
    value0f=read_evt_counter();
    diff0=value0f-value0i;

    select_evt_counter(counter_id_1);
    value1f=read_evt_counter();
    diff1=value1f-value1i;

    select_evt_counter(counter_id_2);
    value2f=read_evt_counter();
    diff2=value2f-value2i;

    select_evt_counter(counter_id_3);
    value3f=read_evt_counter();
    diff3=value3f-value3i;

    select_evt_counter(counter_id_4);
    value4f=read_evt_counter();
    diff4=value4f-value4i;

    select_evt_counter(counter_id_5);
    value5f=read_evt_counter();
    diff5=value5f-value5i;

    valueCf = read_cycle_counter();
    diffC=valueCf-valueCi;
    */

