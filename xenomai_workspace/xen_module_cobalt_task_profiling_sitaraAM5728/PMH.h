/*--------------------------- PMH.h -------------------------------------
 |  File PMH.h
 |
 |  Description: This file provides functions for managing the ARMv7 
 |               Performance Monitor Hardware
 |
 |  Version: 2.0
 *-----------------------------------------------------------------------*/

#define PMSELR_MASK 0xFFFFFFE0
#define PMXEVTYPER_MASK 0xFFFFFF00
#define PMCNTENSET_MASK 0x7FFFFFC0
#define PMCR_MASK 0xFFFFFFC0
#define PMCNTENCLR_MASK 0x7FFFFFC0
#define PMOVSR_MASK 0x7FFFFFC0

/* select_evt_counter
 *
 * Description: The counter used in the coprocessor is selected, without modifying the reserved bits.
 *
 * Parameter:
 * - int counter_id_f: Indicates which counter is selected (between 0 and 5 in ARM 15)
 *
 * Returns: Nothing
 *
 * */ static inline void select_evt_counter(int counter_id_f) {
	   unsigned int value=0;
     __asm__ __volatile("mrc p15, 0, %0, c9, c12, 5" : "=r"(value));
     __asm__ __volatile("mcr p15, 0, %0, c9, c12, 5" :: "r"((value&PMSELR_MASK)|counter_id_f));
}

/* event_track
 *
 * Description: The event type is selected, without modifying the reserved bits.
 *
 * Parameter:
 * - int event_id_f: Indicates which event is selected (between 0x00 and 0x7E in ARM 15)
 *
 * Returns: Nothing
 *
 * */
static inline void event_track(int event_id_f) {
       unsigned int value=0;
      __asm__ __volatile("mrc p15, 0, %0, c9, c13, 1" : "=r"(value));
      __asm__ __volatile("mcr p15, 0, %0, c9, c13, 1" :: "r"((value&PMXEVTYPER_MASK)|event_id_f));
}

/* enable_evt_counter
 *
 * Description: Enables the counters to be used, without modifying the reserved bits.
 *
 * Parameter:
 * - int counter_id_f: Indicates which counter you want to enable (between 0 and 5 in ARM 15)
 *
 * Returns: Nothing
 *
 * */
static inline void enable_evt_counter(int counter_id_f) {
      unsigned int value=0;
      __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
      __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) | 1<<counter_id_f)); 
// 0x80000000 = Cycle counter enable set
}

/* enable_evt_counters
 *
 * Description: Enables the counters to be used, without modifying the reserved bits.
 *
 * Parameter:
 * - int counter_id_f: Indicates which counters you want to enable (between 0x0 and 03F in ARM cortex a15)
 *
 * Returns: Nothing
 *
 * */
static inline void enable_evt_counters(int counter_id_f) {
       unsigned int value=0;
       __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
       __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) | counter_id_f)); // 0x80000000 = Cycle counter enable set
}

/* enable_all_counters
 *
 * Description: Enables the cycle and event counters to be used, without modifying the reserved bits.
 *
 * Parameter:
 * - int counter_id_f: Indicates which EVT counters you want to enable (between 0x0 and 0x3F in ARM cortex 
a15)
 *
 * Returns: Nothing
 *
 * */
static inline void enable_all_counters(int counter_id_f) {
     unsigned int value=0;
     __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
     __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) | (counter_id_f) | 
(0x80000000))); // 0x80000000 = Cycle counter enable set
}

/* disable_counters
 *
 * Description: Disables all the counters leaving just the reserved bits.
 *
 * Parameter:
 * - int counter_id_f: Indicates which EVT counters you want to enable (between 0x0 and 0x3F in ARM cortex 
a15)
 *
 * Returns: Nothing
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
 * - int counter_id_f: Indicates which EVT counters you want to enable (between 0x0 and 0x3F in ARM cortex 
a15)
 *
 * Returns: Nothing
 *
 * */
static inline void disable_all_counters(int counter_id_f) {
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 2" :: "r" (PMCNTENCLR_MASK | counter_id_f | (0x80000000))); 
// 0x80000000 = Cycle counter disable set
}

/* reset_evt_counter
 *
 * Description: Enables all counters and resets the general counters as well as the cycle counter and 
setting its count divider, without modifying the reserved bits.
 *
 * Parameter:
 * - int enable_divider: Indicates if cycle count divider is used(0 or 1)
 *
 * Returns: Nothing
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
 * Description: Enables and resets the general counters as well as the selected cycle counter and setting 
its count divider (if required), without modifying the reserved bits.
 *
 * Parameter:
 * - int enable_divider: Indicates if cycle count divider is used(0 or 1)
 *
 * Returns: Nothing
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
 * None
 *
 * Returns: Nothing
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
 * None
 *
 *
 * Returns: The event value is returned
 *
 * */
static inline unsigned int read_evt_counter() {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c9, c13, 2\t\n": "=r"(value));
   return value;
}

/* enable_cycle_counter
 *
 * Description: Enables only the cycle counter, without modifying the reserved bits.
 *
 * Parameter:
 * None
 *
 * Returns: Nothing
 *
 * */
static inline void enable_cycle_counter() {
	 unsigned int value=0;
   __asm__ __volatile("mrc p15, 0, %0, c9, c12, 1" : "=r" (value));
   __asm__ __volatile("mcr p15, 0, %0, c9, c12, 1" :: "r" ((value & PMCNTENSET_MASK) |(0x80000000)));
}

/* reset_cycle_counter
 *
 * Description: Enables all counters as well as reseting cycle counter value and setting its count divider, 
without modifying the reserved bits.
 *
 * Parameter:
 * - int enable_divider: Indicates if cycle count divider is used(0 or 1)
 *
 * Returns: Nothing
 *
 * */
static inline void reset_cycle_counter(unsigned int enable_divider) {
	unsigned int value=0;
	unsigned int temp=0;
	temp = 1|4 ;
	if (enable_divider)
		temp |= 8;
  __asm__ __volatile("mrc p15, 0, %0, c9, c12, 0" : "=r" (value));
  __asm__ __volatile("mcr p15, 0, %0, c9, c12, 0" :: "r" ((value & PMCR_MASK) | temp));
}

/* read_cycle_counter
 *
 * Description: Reads the Cycle Counter Register (CCNT).
 *
 * Parameter: None
 *
 *
 * Returns: The cycle counter value is returned
 *
 * */
static inline unsigned int read_cycle_counter() {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));
   return value;
}

/* read_counters_overflow
 *
 * Description: Reads the Performance Monitor Overflow Flag Status Register (PMSOVSR ).
 *
 * Parameter: None
 *
 *
 * Returns: The counters overflow flags are returned
 *
 * */
static inline unsigned int read_counters_overflow() {
   unsigned int value=0;
   __asm__ __volatile("MRC p15, 0, %0, c9, c12, 3\t\n": "=r"(value));
   return (value&0x8000003F); // MSB = Counter cycle overflow
}

/* clear_overflows
 *
 * Description: Clears all counters overflows flags (MSB = Counter cycle overflow)
 *
 * Parameter: None
 *
 *
 * Returns: Nothing
 *
 * */
static inline void clear_overflows() {
	unsigned int value=0;
	__asm__ __volatile("MRC p15, 0, %0, c9, c12, 3" : "=r"(value));
	__asm__ __volatile("MCR p15, 0, %0, c9, c12, 3" :: "r"((value & PMOVSR_MASK) | 0x8000003F));
}
