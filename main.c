#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
        /* ecx is often an input as well as an output. */
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}

/*
C80H 3200 IA32_DEBUG_INTERFACE Silicon Debug Feature Control (R/W) If CPUID.01H:ECX.[11] = 1
0 Enable (R/W)
BIOS set 1 to enable Silicon debug features.
Default is 0
If CPUID.01H:ECX.[11] = 1
29:1 Reserved.
30 Lock (R/W): If 1, locks any further change
to the MSR. The lock bit is set automatically
on the first SMI assertion even if not
explicitly set by BIOS. Default is 0.
If CPUID.01H:ECX.[11] = 1
31 Debug Occurred (R/O): This “sticky bit” is
set by hardware to indicate the status of
bit 0. Default is 0.
If CPUID.01H:ECX.[11] = 1
63:32 Reserved. 
*/

static inline unsigned int readMSR_SDFC() {
	int fd;

	fd = open("/dev/cpu/0/msr",O_RDONLY);
	if (fd < -1) 
		return 0;

	lseek(fd, 3200, SEEK_SET);

	unsigned int buffer;
	read(fd, &buffer, 8);

	close(fd);

	return buffer;
}

int main(int argc, char **argv)
{
  unsigned eax, ebx, ecx, edx;

  eax = 1; /* processor info and feature bits */
  native_cpuid(&eax, &ebx, &ecx, &edx);

  //Get some cpu features
  printf("RAW ECX: %08X\n", ecx);
  //IA32_DEBUG_INTERFACE
  printf("SDBG: %d\n",(ecx >> 11) & 1);

  //Check if SDBG is avaliable
  if ((ecx >> 11) & 1) {
	printf("SDBG feature found!\n");
  	//Read MSR features
	unsigned int sdfc = readMSR_SDFC();
	printf("SDFC register: %08X\n", sdfc);
	printf("Debug Interface Enabled: %d\n", (sdfc) & 1);
	printf("Debug Interface Lock: %d\n", (sdfc >> 30) & 1);
	printf("Debug Interface Debug Occurred: %d\n", (sdfc >> 31) & 1);
  } else {
	printf("SDBG feature NOT found!\n");
  }
  
  return 0;
}


