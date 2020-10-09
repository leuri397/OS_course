#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <stdio.h>

int main() {
	const int LAST_SIZE = 8;
	const int NAMES_SIZE = 1024;
	const char* namesMemory = "/LOG_NAMES";
	const char* lastMemory = "/LOG_LAST";
	//const char* baseName = "/LOG_";
	//char lineBuffer[1024];
	int last_shm_fd, names_shm_fd;
	int *last_shm_memory;
	char *names_shm_memory;
	last_shm_fd = shm_open(lastMemory, O_CREAT | O_RDWR, 0666);
	perror("1:");
	ftruncate(last_shm_fd, LAST_SIZE);
	last_shm_memory = (int*)mmap(0, LAST_SIZE, PROT_WRITE, MAP_SHARED, last_shm_fd, 0);
	perror("2:");
	names_shm_fd = shm_open(namesMemory, O_CREAT | O_RDWR, 0666);
	ftruncate(names_shm_fd, NAMES_SIZE);
	names_shm_memory = (char*)mmap(0, NAMES_SIZE, PROT_WRITE, MAP_SHARED, names_shm_fd, 0);
	perror("3:");
	sprintf(names_shm_memory, "%s", "TestLog\nTestLogAnother\nOneMoreTest\nLastTest\n");
	int fd = shm_open("/LOG_1", O_CREAT | O_RDWR, 0666);
	ftruncate(fd, 1024);
	perror("4:");
	char* memory = (char*)mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
	while(__sync_val_compare_and_swap(last_shm_memory, 0, 1))
	{}
	sprintf(memory, "%s", "This is a test log message\n\0");
	perror("5:");
	int PID;
	scanf("%d", &PID);
	kill(PID, SIGUSR1);
	while(__sync_val_compare_and_swap(last_shm_memory, 0, 1))
	{}
	sprintf(memory, "%s", "Another log test message\n\0");
	*last_shm_memory = 1;
	kill(PID, SIGUSR1);
}
