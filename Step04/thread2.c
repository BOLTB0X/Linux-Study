#include <stdio.h>
#include <pthread.h>

void* myThreadFunc(void* arg) {
	    printf("스레드 실행 중! 받은 값: %s\n", (char*)arg);
	        return NULL;
}

int main(void) {
	pthread_t tid;

	// 스레드 생성
        pthread_create(&tid, NULL, myThreadFunc, "Hello Thread");
		
        // 스레드 종료 대기
	pthread_join(tid, NULL);
		
	printf("메인 함수 종료!\n");
	
	return 0;
}                     
