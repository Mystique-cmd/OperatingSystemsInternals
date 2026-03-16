#include <stdio.h>
#include <unistd.h> // provides access to POSIX OS API
#include <sys/types.h> // for system spefici data types

int main() {
	pid_t pid;
	
	pid = fork ();

	if (pid < 0 ){
		fprintf(stderr, "Fork failed \n);
		return 1;
	}else if (pid == 0){
		printf("Child Process: PID = %d\n", getpid());
	}else{
		printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
	}
	return 0;
}
