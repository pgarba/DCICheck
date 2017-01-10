# DCICheck

Simple tool to verify if the DCI feature is enabled on your system.

If you don't know what this is about check:

https://media.ccc.de/v/33c3-8069-tapping_into_the_core

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


