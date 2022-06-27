################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c6000_8.3.5/bin/cl6x" -O2 --include_path="C:/Users/alfon/OneDrive/Desktop/ISAE-SUPAERO/GitHub/ccs_workspace/task_periodic_profiling_keystoneII/Dsp7" --include_path="C:/home/local/workspace_mama_ccs1/ti/pdk_OMAPL138_1_01_00_02/packages/ti/csl" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c6000_8.3.5/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


