#include <unistd.h>

int main(void) {
	const char *msg = "hello, System Call!\n";
	write(1, msg, 21);
	return 0;
}
