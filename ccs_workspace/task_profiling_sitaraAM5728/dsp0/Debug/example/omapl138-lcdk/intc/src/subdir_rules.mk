################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
example/omapl138-lcdk/intc/src/%.obj: ../example/omapl138-lcdk/intc/src/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.2.4/bin/cl6x" -mv6500 --include_path="/home/local/workspace_mama_ccs1/Dsp0" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.2.4/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="example/omapl138-lcdk/intc/src/$(basename $(<F)).d_raw" --obj_directory="example/omapl138-lcdk/intc/src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

example/omapl138-lcdk/intc/src/%.obj: ../example/omapl138-lcdk/intc/src/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.2.4/bin/cl6x" -mv6500 --include_path="/home/local/workspace_mama_ccs1/Dsp0" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.2.4/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="example/omapl138-lcdk/intc/src/$(basename $(<F)).d_raw" --obj_directory="example/omapl138-lcdk/intc/src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


