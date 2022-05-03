#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

unsigned const PMUSERENR_MASK = 0xFFFFFFFE;


// Allow Users to access the ARM Cortex A15 performance counter
static int user_enable_pmu_init(void){
    unsigned value=0;
    unsigned cpu=0;

    printk(KERN_ALERT "User mode access to performance monitors enabled \n");

    for_each_possible_cpu(cpu){
    	 __asm__ __volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(value));
     	__asm__ __volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"((value&PMUSERENR_MASK)|0x1));
    }

    return 0;
}

// Deny access to the ARM Cortex A15 performance counter to Users
static void user_disable_pmu_exit(void){
    unsigned value=0;
    unsigned cpu=0;
    printk(KERN_ALERT "User mode access to performance monitors disabled \n");

    for_each_possible_cpu(cpu){
    	 __asm__ __volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(value));
     	__asm__ __volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"((value&PMUSERENR_MASK)|0x0));
    }
}

module_init(user_enable_pmu_init);
module_exit(user_disable_pmu_exit);
