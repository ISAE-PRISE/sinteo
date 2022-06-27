################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc-7.2.1.exe" -c -mcpu=cortex-a15 -mtune=cortex-a15 -marm -mfloat-abi=soft -DSOC_K2H -I"C:/ti/pdk_c667x_2_0_15/packages" -I"C:/Users/alfon/OneDrive/Desktop/ISAE-SUPAERO/GitHub/ccs_workspace/task_periodic_profiling_keystoneII/arm0" -I"C:/ti/ccs930/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -specs="rdimon.specs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.S $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc-7.2.1.exe" -c -mcpu=cortex-a15 -mtune=cortex-a15 -marm -mfloat-abi=soft -DSOC_K2H -I"C:/ti/pdk_c667x_2_0_15/packages" -I"C:/Users/alfon/OneDrive/Desktop/ISAE-SUPAERO/GitHub/ccs_workspace/task_periodic_profiling_keystoneII/arm0" -I"C:/ti/ccs930/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major-win32/arm-none-eabi/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -specs="rdimon.specs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -x assembler-with-cpp $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


