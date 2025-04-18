#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("내 PID (getpid): %d\n" , getpid());
	printf("부모 PID (getppid) %d\n" , getppid());
	
	return 0;
}
