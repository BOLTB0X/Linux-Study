#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("exec 전에 출력\n");

	execl("/bin/ls", "ls", "-l", NULL);

	// 만약 exec가 실패하면 아래 코드 실행
	perror("exec 실패");
	return 1;
}
