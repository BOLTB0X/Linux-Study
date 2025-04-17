#include <stdio.h>
#include <pthread.h>

void* say_hello(void* arg) {
	printf("Hello from thread!\n");
	return NULL;
}

int main() {
	pthread_t tid;
	
	if (pthread_create(&tid, NULL, say_hello, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}
	
	pthread_join(tid, NULL);
	printf("Main thread ends.\n");
	return 0;
}
