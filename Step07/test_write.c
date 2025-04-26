#include <fcntl.h>
#include <unistd.h>

int main(void) {
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd < 0) {
		write(2, "파일 Open 실패\n", 17);
		return 1;
	}

	const char *msg = "Hello, Linux System Programming!\n";
	write(fd, msg, 34); // 문자열 길이만큼 저장
	close(fd);

	return 0;
}
