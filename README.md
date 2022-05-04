# SINTEO - Sdram INTErference Optimization

Copyright (C) 2022 ISAE-SUPAERO / ONERA

Optimization of tasks interference on Heterogeneous Multi-core Platforms

### Description:

"DDR_SDRAM_cost_function": This file is used for analyzing and testing the DDR cost function.
"task_memory_mapping_optimization_2D.ipynb": This file is used for the task/memory mapping optimization.
					     By default, it minimizes (1) the workload variance and (2) the 
					     maximum DDR interference. The deadline constraint is applied.
					     The optimal variables and objectives value are exported.
					     The resulting graphs are also exported.
"task_memory_mapping_optimization_3D.ipynb": Like "task_memory_mapping_optimization_2D.ipynb" but
					     considering a third objective to optimize.

"task_profiling_sitaraAM5728/": This workspace contains the projects regarding the methods 
						for tasks profiling on both cores, ARM Cortex A15 and DSP C66x 
						for Sitara AM5728 SoC (SoC used by BeagleBoard X15).
"task_profiling_keystoneII/": This workspace contains the projects regarding the methods
						for tasks profiling on both cores, ARM Cortex A15 and DSP C66x
						for the Keystone II TCI6636K2H SoC.

"xen_cobalt_task_profiling_sitaraAM5728/": This workspace contains a project regarding the tasks 
						profiling on the ARM Cortex A15 on Xenomai RTOS using the Cobalt POSIX 
				          implementation for Sitara AM5728 SoC (SoC used by BeagleBoard X15).
				          Only User programing is carried out, hence, performance counters
				          on ARM are not accessed.					     
"xen_module_cobalt_task_profiling_sitaraAM5728/": This workspace contains a project regarding the tasks 
						profiling on the ARM Cortex A15 on Xenomai RTOS using the Cobalt POSIX 
				          implementation for Sitara AM5728 SoC (SoC used by BeagleBoard X15).
				          Unlike xen_cobalt_task_profiling_sitaraAM5728/ workspace, the performance 
				          counters on the ARM cores are used. This is achieved through a Kernel module which
						  enables the User mode access to the Performance Monitors Units. 
"xen_alchemy_task_profiling_sitaraAM5728/": This workspace contains a project regarding the tasks 
						profiling on the ARM Cortex A15 on Xenomai RTOS using the Alchemy API 
				          for Sitara AM5728 SoC (SoC used by BeagleBoard X15).
				          Only User programing is carried out, hence, performance counters
				          on ARM are not accessed.
						  
"DDR_SDRAM_cost_function_equation_development_for_heterogeneous_MPSoCs.pdf": Document explaining the creation of a cost function for 
																			 estimating the SDRAM interference cost on a heterogeneous 
																			 multicore platform. The SoC Keystone II is used for the
																			 evaluation of the cost function.

### Software Requirements:

1. Jupyter Notebook is required for opening the three Ipynb files 
   inside the workspace "jupyter_notebook" 
   (tested with Jupyter version 6.3.0 and python 3.8.8).
   
2. jMetalPy libraries are required to run "task_memory_mapping_optimization_2D.ipynb"
   and "task_memory_mapping_optimization_3D.ipynb"
   See how to install at https://github.com/jMetal/jMetalPy
   (tested with version 1.5.5).
   
3. Code Composer Studio (CCS TUDIO) IDE by Texas Instruments is required for 
   opening the projects inside the workspace "ccs_workspace" (tested with CCS version 9.3.0).
   Download the Chip Support Libraries (CSL) during installation.
   
4. Xenomai 3.0 required for executing the projects inside the workspace "xenomai_workspace" in real-time
   (tested with Xenomai cobalt v3.0.5 and Debian GNU/Linux 8 (jessie) with Linux kernel 4.4.87+).

### Directory Hierarchy:

```
root
│
├── ccs_workspace/  -->  Bare-metal TI Code Composer Studio workspaces required for profiling and testing  
│   ├── task_profiling_keystoneII/  -->  Keystone II TCI6636K2H profiling projects for ARM Cortex A15 and DSP C66x 
│   └── task_profiling_sitaraAM5728/  -->  Sitara AM5728 profiling projects for ARM Cortex A15 and DSP C66x   
│
│── doc/ --> Documents related to the SDRAM understanding and configuration are found here
│   └── DDR_SDRAM_cost_function_equation_development_for_heterogeneous_MPSoCs/  -->  Development of the SDRAM interference cost function for task mapping
│
│── jupyter_notebook/  -->  Jupyter python notebooks code for task/memory mapping
│   ├── 3DFUN/  -->  CSV files with the selected cost functions outcome for task_memory_mapping_optimization_3D
│   ├── 3DGraphs/  --> Contains the graphs depicting the three objectives optimization solutions for task_memory_mapping_optimization_3D
│   ├── 3DVAR/  -->  CSV files with the near-optimal task-core and core-bank mapping for task_memory_mapping_optimization_3D
│   ├── FUN/  -->  CSV files with the selected cost functions outcome for task_memory_mapping_optimization_2D
│   ├── Graphs/  --> Contains the graphs depicting the two objectives optimization solutions for task_memory_mapping_optimization_2D
│   ├── VAR/  -->  CSV files with the near-optimal task-core and core-bank mapping for task_memory_mapping_optimization_2D
│   ├── DDR_SDRAM_cost_function  -->  Tests the DDR3 SDRAM interference cost function
│   ├── task_memory_mapping_optimization_2D.ipynb  -->  Two objectives optimization
│   └── task_memory_mapping_optimization_3D.ipynb  -->  Three objectives optimization
│
│── xenomai_workspace/  -->  Code workspaces created for profiling and testing on Xenomai 3 
│    ├── xen_alchemy_task_profiling_sitaraAM5728/  -->  Sitara AM5728 profiling project for ARM Cortex A15 using the Alchemy API   
│    ├── xen_cobalt_task_profiling_sitaraAM5728/  -->  Sitara AM5728 profiling project for ARM Cortex A15 using Cobalt POSIX implementation  
│    └── xen_module_cobalt_task_profiling_sitaraAM5728/  -->  Sitara AM5728 profiling project for ARM Cortex A15 using Cobalt POSIX implementation using PMCs
│
└── README.md  -->  Important information to consider 
```
## Authors

Alfonso Mascarenas-Gonzalez (ISAE-SUPAERO).
Jean-Baptiste Chaudron (ISAE-SUPAERO).
Youcef Bouchebaba (ONERA).
Frederic Boniol (ONERA).
Jean-Loup Bussenot (ONERA).

## Contacts

alfonso.mascarenas-gonzalez@isae-supaero.fr

jean-baptiste.chaudron@isae-supaero.fr

youcef.bouchebaba@onera.fr

frederic.boniol@onera.fr

jean-loup.bussenot@onera.fr

## License

This project is distributed as an open-source software under GPL version 3.0.

## BibTeX Citation

If you use our work in a scientific publication, please use this citation for now (another paper is under review):

```
@inproceedings{sinteo-ref1,
  TITLE = {{Heterogeneous multicore SDRAM interference analysis}},
  AUTHOR = {Mascare{\~n}as Gonz{\'a}lez, Alfonso and Boniol, Fr{\'e}d{\'e}ric and Bouchebaba, Youcef and Bussenot, Jean-Loup and Chaudron, Jean-Baptiste},
  BOOKTITLE = {{The 29th International Conference on Real-Time Networks and Systems (RTNS '21)}},
  ADDRESS = {Virtual event, France},
  PAGES = {12-23},
  YEAR = {2021},
  MONTH = April,
  KEYWORDS = {Multicore ; DDR3 SDRAM Controller ; WCET ; Cost functions},
}





