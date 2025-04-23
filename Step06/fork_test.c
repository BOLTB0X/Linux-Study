#include <stdio.h>
#include <unistd.h>

int main(void) {
	pid_t pid = fork();

	if (pid == 1) {
		perror("fork 실패");
		return 1;
	} else if (pid == 0) {
		// 자식 프로세스
		printf("자식 프로세스: PID=%d, 부모 PID=%d\n", getpid(), getppid());
	} else {
		// 부모 프로세스
		printf("부모 프로세스: PID=%d, 자식 PID=%d\n", getpid(), pid);
	}

	return 0;
}
