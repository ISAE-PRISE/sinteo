################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup_ARMCA15.S 

LDS_SRCS += \
../keystoneII.lds 

C_SRCS += \
../DDR3MemoryController.c \
../arm_pmu_management.c \
../main.c \
../memory_controller_management.c 

C_DEPS += \
./DDR3MemoryController.d \
./arm_pmu_management.d \
./main.d \
./memory_controller_management.d 

OBJS += \
./DDR3MemoryController.o \
./arm_pmu_management.o \
./main.o \
./memory_controller_management.o \
./startup_ARMCA15.o 

S_UPPER_DEPS += \
./startup_ARMCA15.d 

S_UPPER_DEPS__QUOTED += \
"startup_ARMCA15.d" 

OBJS__QUOTED += \
"DDR3MemoryController.o" \
"arm_pmu_management.o" \
"main.o" \
"memory_controller_management.o" \
"startup_ARMCA15.o" 

C_DEPS__QUOTED += \
"DDR3MemoryController.d" \
"arm_pmu_management.d" \
"main.d" \
"memory_controller_management.d" 

C_SRCS__QUOTED += \
"../DDR3MemoryController.c" \
"../arm_pmu_management.c" \
"../main.c" \
"../memory_controller_management.c" 

S_UPPER_SRCS__QUOTED += \
"../startup_ARMCA15.S" 


