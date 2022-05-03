# Insert module to allow accessing PMUs
insmod ./module/user_enable_pmu.ko 

# Clean and compile
make -f make_v2 clean
make -f make_v2

# Add the current shell to the cgroup with realtime scheduling information
echo $$ > /sys/fs/cgroup/cpu/tasks

# Run the program 
./main

# Uncomment if you are not in sudo mode  
# sudo LD_LIBRARY_PATH=/usr/xenomai/lib/ ./main

# Remove module to allow accessing PMUs
rmmod ./module/user_enable_pmu.ko

exit
