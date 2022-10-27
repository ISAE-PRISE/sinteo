#include <linux/init.h>
#include <linux/module.h>
#include <linux/smp.h>   // for on_each_cpu

MODULE_LICENSE("GPL");

unsigned const PMUSERENR_MASK = 0xFFFFFFFE;

// Set the User Enable Register
void user_enable_pmu(void *info){
    unsigned value=0;
    __asm__ __volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(value));
    __asm__ __volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"((value&PMUSERENR_MASK)|0x1));
}

// Allow Users to access the ARM Cortex A15 performance counter on each available core
static int user_enable_pmu_init(void){
    printk(KERN_ALERT "User mode access to performance monitors enabled \n");
    on_each_cpu(user_enable_pmu, NULL, 1);

    return 0;
}

// Clear the User Enable Register
void user_disable_pmu(void *info){
    unsigned value=0;
    __asm__ __volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(value));
    __asm__ __volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"((value&PMUSERENR_MASK)|0x0));
}

// Deny access to the ARM Cortex A15 performance counter to Users
static void user_disable_pmu_exit(void){
    printk(KERN_ALERT "User mode access to performance monitors disabled \n");
    on_each_cpu(user_disable_pmu, NULL, 1);
}

module_init(user_enable_pmu_init);
module_exit(user_disable_pmu_exit);