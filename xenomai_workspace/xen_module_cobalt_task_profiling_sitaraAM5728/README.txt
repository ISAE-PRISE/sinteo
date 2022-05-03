How to run:
‾‾‾‾‾‾‾‾‾‾
1. Include the following directories in their respective PATHs:

export PATH=$PATH:/usr/xenomai/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/xenomai/lib

2. Execute "make_n_run.sh".


Warning:
‾‾‾‾‾‾‾
During the module creation many errors can be encountered. 
Some of them are described below:

E1. Linux headers not present.
S1. Download them: apt search linux-headers-$(uname -r).
    On Xenomai, the Xenaomai headers are downloaded instead.

E2. "Build" symbol at diretory /lib/modules/$(uname -r) is not properly set.
S2. Either create a new symbol pointing to the right headers path or use the header
    path directly when building the module.

E3. Makefile not recognized ("No such file ordirectory make[2]").
S3. Assure to call the make file as "Makefile" and not "makefile" (upper case M).

E4. When executing insmod, "disagrees about version of symbol module_layout" is returned by dmesg
S4. Retrieve the hexadecimal value of the symbol "module_layout" from an already created Linux module
    via "modprobe --dump-modversions module_name.ko".
    Check the symbol module_layout value of your module. If they are different, replace yours with the
    retrived symbol value through a hex editor, e.g., VIM. 

E5. Error when executing insmod or rmmod.
S5. The module was already charged (insmod error) or the module does not exists (rmmod error).