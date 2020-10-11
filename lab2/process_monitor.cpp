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

bool refresh = true;

struct RawProcess {
	int PID;
	std::string status;
};

struct Process {
	int PID; //
	std::string name; //
	int PPID; //
	int PGID; //
	std::string status;//
	std::string start_time; //
	double cpu_use; //
	double memory;
	unsigned int VSZ; //
	int RSS;
	int TT; //
	std::string command; //
	int UID;//
};

void sighandler(int number) 
{
	refresh = true;
}

int main() {
	DIR* proc_dir;
	proc_dir = opendir("/proc");
	if (proc_dir == NULL)
	{
		perror("Dir:");
		return -1;
	}
	std::vector<RawProcess> raw;
	std::vector<Process> parsed;
	struct dirent* entry = readdir(proc_dir);
	struct Process kernel;
	while(entry != NULL)
	{
		struct RawProcess buffer;
		std::string dirname = entry->d_name;
		if ((dirname != ".") && (dirname != "..") && (dirname != "curproc"))
		{
			buffer.PID = std::stoi(dirname, 0, 10);
			char status_buffer[256];
			int status = open(("/proc/" + dirname + "/status").c_str(), O_RDONLY);
			read(status, status_buffer, 512);
			buffer.status = status_buffer;
			buffer.status = buffer.status.substr(0, buffer.status.find('\n'));
			close(status);
			raw.push_back(buffer);
		}
		entry = readdir(proc_dir);
	}
	struct kinfo_proc kp[1000] = {};
	size_t len = sizeof(kp);
	int mib[] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
	sysctl(mib, 3, &kp, &len, NULL, 0);
	for (int i = 0; i < 1000; i++)
	{
		struct Process buffer;
		buffer.PID = kp[i].ki_pid;
		buffer.PGID = kp[i].ki_pgid;
		buffer.name = kp[i].ki_tdname;
		buffer.command = kp[i].ki_comm;
		struct tm *start = localtime(&kp[i].ki_start.tv_sec);
		buffer.start_time = std::to_string(start->tm_hour) + ":" + std::to_string(start->tm_min) + ":" + std::to_string(start->tm_sec);
		buffer.TT = static_cast<int>(kp[i].ki_tdev);
		buffer.status = std::to_string(kp[i].ki_stat);
		buffer.PPID = kp[i].ki_ppid;
		buffer.VSZ = kp[i].ki_size;
		buffer.RSS = kp[i].ki_rssize;
		buffer.cpu_use = (double)kp[i].ki_pctcpu/100;
		if(buffer.start_time != "3:0:0")
		parsed.push_back(buffer);
	}

	//printf("PID\tPPID\tGROUP\tSTARTTIME\tSTATE\tCPU\tUSER\tTT\tVSZ\t\tRSS\tCOMM\n");
	for(int i = 0; i < parsed.size(); i++)
	{
		write(1, &parsed[i].PID, 8);
		write(1, &parsed[i].PPID, 8);
		write(1, &parsed[i].PGID, 8);
		write(1, parsed[i].start_time.c_str(), 8);
		write(1, parsed[i].status.c_str(), 2);
		write(1, std::to_string(parsed[i].cpu_use).c_str(), 5);
		write(1, &parsed[i].UID, 8);
		write(1, &parsed[i].TT, 8);
		write(1, &parsed[i].VSZ, 8);
		write(1, &parsed[i].RSS, 8);
		write(1, parsed[i].command.c_str(), 19);
		write(1, "\n", 1);
		/*printf("%d\t", parsed[i].PID);
		printf("%d\t", parsed[i].PPID);
		printf("%d\t", parsed[i].PGID);
		printf("%s\t", parsed[i].start_time.c_str());
		if(parsed[i].start_time.size() < 8)
		printf("\t");
		printf("%s\t", parsed[i].status.c_str());
		printf("%0.1f", parsed[i].cpu_use);
		std::string percent = "%\t";
		printf("%s", percent.c_str());
		printf("%d\t", parsed[i].UID);
		printf("%s\t", parsed[i].TT.c_str());
		printf("%d\t", parsed[i].VSZ);
		printf("%d\t", parsed[i].RSS);
		printf("%s", parsed[i].command.c_str());
		printf("\n");*/
	}
	write(1, 0, 1);
}

