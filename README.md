# DCICheck

# prerequisite

Linux and MSR module:
http://man7.org/linux/man-pages/man4/msr.4.html

If the msr device is missing run the script supplied by the msr-tools

https://github.com/01org/msr-tools/blob/master/MAKEDEV-cpuid-ms
If the msr device is missing run the script supplied by the msr-tools

# Compile
compile with clang main.c -o checkdci


# Run
sudo ./checkdci


