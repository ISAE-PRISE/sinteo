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
"task_profiling_sitaraAM5728": This workspace contains the projects regarding the methods
			       for tasks profiling on both cores, ARM Cortex A15 and DSP C66x

### Software Requirements:

1. Jupyter Notebook is required for opening the two Ipynb files entitled 
   "DDR_SDRAM_cost_function" and "task_memory_mapping_optimization_2D.ipynb"
   (tested with Jupyter version 6.3.0 and python 3.8.8).
   
2. jMetalPy libraries are required to run "task_memory_mapping_optimization_2D.ipynb"
   See how to install at https://github.com/jMetal/jMetalPy
   (tested with version 1.5.5).
   
3. Code Composer Studio (CCSTUDIO) IDE by Texas Instruments is required for 
   opening the projects inside the workspace "workspace_CCS_task_profiling_sitaraAM5728"
   (tested with CCS version 9.3.0). Download the Chip Support Libraries (CSL) during installation.

### Directory Hierarchy:


root <br />
├── README.txt  -->  Important information to consider  <br />
├── ccs_workspace/  -->  Bare-metal TI Code Composer Studio workspaces required for profiling and testing <br />
│   └── task_profiling_sitaraAM5728/  -->  Sitara AM5728 profiling projects for ARM Cortex A15 and DSP C66x <br />
└── jupyter_notebook/  -->  Jupyter python notebooks code for task/memory mapping <br />
    ├── DDR_SDRAM_cost_function  -->  Tests the DDR3 SDRAM interference cost function <br />
    ├── task_memory_mapping_optimization_2D.ipynb  --> Two objectives optimization <br />
    ├── task_memory_mapping_optimization_3D.ipynb  --> Three objectives optimization <br />
    ├── FUN/  -->  CSV files with the selected cost functions outcome <br />
    ├── VAR/  -->  CSV files with the near-optimal task-core and core-bank mapping <br />
    ├── Graphs/  --> Contains the graphs depicting the two objectives optimization solutions <br />
    └── 3DGraphs/  --> Contains the graphs depicting the three objectives optimization solutions <br />

## Authors

Alfonso Mascarenas-Gonzalez (ISAE-SUPAERO) <br />
Jean-Baptiste Chaudron (ISAE-SUPAERO) <br />
Youcef Bouchebaba (ONERA) <br />
Frederic Boniol (ONERA) <br />

## Contacts

alfonso.mascarenas-gonzalez@isae-supaero.fr <br />
jean-baptiste.chaudron@isae-supaero.fr <br />
youcef.bouchebaba@onera.fr <br />
frederic.boniol@onera.fr <br />

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





