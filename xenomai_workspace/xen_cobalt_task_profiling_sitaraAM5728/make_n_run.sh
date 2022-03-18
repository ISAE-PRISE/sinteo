# Add xenomai bin path to the environment varible PATH used by our make_v1
export PATH=$PATH:/usr/xenomai/bin

# Clean and compile
make -f make_v1 clean
make -f make_v1

# Add the current shell to the cgroup with realtime scheduling information
echo $$ > /sys/fs/cgroup/cpu/tasks

# Add dynamic library and run the program 
sudo LD_LIBRARY_PATH=/usr/xenomai/lib/ ./main

exit
