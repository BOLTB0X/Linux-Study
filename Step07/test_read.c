#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	char buffer[128];
	int fd = open("output.txt", O_RDONLY);

	if (fd < 0) {
		perror("파일 열기 실패");
		return 1;
	}

	int n = read(fd, buffer, sizeof(buffer) - 1);
	buffer[n] = '\0';
	printf("읽은 내용: %s", buffer);

	close(fd);
	return 0;
}
