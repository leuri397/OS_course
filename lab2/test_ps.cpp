#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <kvm.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/proc.h>
#include <sys/param.h>
#include <libprocstat.h>
#include <sys/user.h>

struct Process {
	int PID;
	int PPID;
	int PGID;
	char start_time[8];
	char status[2];
	char cpu[5];
	int UID;
	int TT;
	int VSZ;
	int RSS;
	char memory[5];
	char command[19];
	char LF;
};

int main() {
	const int VAL_SIZE = 8;
	const int DATA_SIZE = 300000;
	const char* lastMemory = "/PS_STATUS";
	const char* namesMemory = "/PS_VALUE";
	//const char* baseName = "/LOG_";
	//char lineBuffer[1024];
	int last_shm_fd, names_shm_fd;
	int *last_shm_memory;
	char *names_shm_memory;
	last_shm_fd = shm_open(lastMemory, O_RDWR, 0666);
	perror("1:");
	ftruncate(last_shm_fd, VAL_SIZE);
	last_shm_memory = (int*)mmap(0, VAL_SIZE, PROT_WRITE, MAP_SHARED, last_shm_fd, 0);
	perror("2:");
	names_shm_fd = shm_open(namesMemory, O_RDWR, 0666);
	ftruncate(names_shm_fd, DATA_SIZE);
	names_shm_memory = (char*)mmap(0, DATA_SIZE, PROT_READ, MAP_SHARED, names_shm_fd, 0);
	perror("3:");
	//names_shm_memory[30] = 0;
	struct Process *buffer = (Process*)names_shm_memory;
	for(int i = 0; i < 268; i++)
	{
		printf("PID: %d\nPPID: %d\nPGID: %d\nSTART: %.8s \nSTAT: %.2s\n", buffer[i].PID, buffer[i].PPID, buffer[i].PGID, buffer[i].start_time, buffer[i].status );
		printf("CPU: %.5s%%\nUID: %d\nTT: %d\nVSZ: %d\nRSS: %d\nMEM: %.5s%%\nCOMM: %.19s\n========\n", buffer[i].cpu, buffer[i].UID, buffer[i].TT, buffer[i].VSZ, buffer[i].RSS, buffer[i].memory, buffer[i].command);
	}
	//perror("4:");
}
