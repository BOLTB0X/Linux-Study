#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	pid_t pid = fork();
	
	if (pid == 0) {
		printf("자식 프로세스 실행 중... PID=%d\n", getpid());
		sleep(2);
		printf("자식 프로세스 종료\n");
	} else {
		printf("부모가 자식 기다리는 중...\n");
		wait(NULL);
		printf("부모도 이제 종료\n");
	}
	return 0;
}
