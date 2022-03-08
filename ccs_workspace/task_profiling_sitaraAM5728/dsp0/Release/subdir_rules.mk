################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.2.4/bin/cl6x" -O2 --include_path="/home/local/workspace_CCS_correlation/Dsp0" --include_path="/home/local/workspace_mama_ccs1/ti/pdk_OMAPL138_1_01_00_02/packages/ti/csl" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.2.4/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


