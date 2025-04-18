#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (fd == -1) {
		write(2, "파일 열기 실패 \n", 17);
		return 1;
	}

	const char *message = "Hello, 리눅스 시스템 콜!\n";
	write(fd, message, strlen(message));
	close(fd);

	return 0;
}
