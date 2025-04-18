#include <stdio.h>
#include <unistd.h>

int main(void) {
	pid_t pit = getpid();
	printf("현재 프로세스 ID: %d\n", pit);
	return 0;
}
