# Step04 Process & Thread

> 프로그램의 의미는 "어떤 작업을 위해 실행할 수 있는 파일"

## 프로세스 와 스레드

| 항목       | 프로세스 (Process)              | 스레드 (Thread)                |
|------------|----------------------------------|---------------------------------|
| 정의       | 실행 중인 프로그램 하나         | 프로세스 내 작업 단위           |
| 메모리     | 독립된 메모리 공간 사용         | 같은 메모리 공간 공유           |
| 통신       | 느린 IPC 필요 (파이프, 소켓 등) | 빠른 메모리 공유 가능           |
| 생성 비용  | 높음 (fork 등)                  | 낮음 (pthread 등)              |

- 프로세스 (Process)
 
   - 메모리에 올라와 실행되고 있는 프로그램의 독립적인 인스턴스

   - OS로부터 시스템 자원을 할당받는 작업의 단위

   - 동적인 개념으로는 실행된 프로그램

   - 각각 독립된 메모리 영역(**Code** , **Data** , **Stack** , **Heap** 의 구조)을 할당받음

   - 기본적으로 프로세스당 최소 1개의 스레드(메인 스레드)를 가지고 있음

      <br/>

- 스레드 (Thread)

   - 프로세스 내에서 실행되는 여러 흐름 단위

   - 프로세스 내에서 각각 Stack만 따로 할당받고 Code, Data, Heap 영역은 공유


| 항목     | 프로세스                           | 스레드                         |
|----------|-------------------------------------|--------------------------------|
| 장점     | 안정성 높음 (다른 프로세스 영향 없음) | 자원 공유로 빠른 처리 가능     |
| 단점     | 자원 소비 높음 , 생성 비용 높음           | 하나가 죽으면 전체 영향 줄 수 있음 |

- 프로세스 ex: 크롬 브라우저를 여러 창으로 띄우면 각각의 창이 독립된 프로세스로 동작

- 스레드 ex: 하나의 크롬 창에서 여러 탭이 각각 스레드로 처리됨

## 간단한 명령어

- 실행 중인 프로세스 보기

   ```
   $ ps aux
   ```

   <br/>

- 특정 명령어의 스레드 보기

   ```
   $ top -H -p <pid>
   ```
## 실습 : pthread

> pthread란 POSIX Thread의 약자로 유닉스계열 POSIX시스템에서 병렬적으로 작동하는 소프트웨어를 작성하기 위하여 제공하는 API

C에서는 **pthread** 로 스레드 제어 가능

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void *p_function(void * data) {
	pid_t pid; //process id
        pthread_t tid; // thread id
	pid = getpid(); //4
	tid = pthread_self();
	
	char* thread_name = (char *)data;
	int i = 0;
	
	while(i<3) {
		printf("thread name : %s, tid : %x, pid : %u\n", thread_name, (unsigned int)tid, (unsigned int)pid); //5
		i++;
		sleep(1);
	}
}

int main(void) {
	pthread_t pthread[2];
	int thr_id;
	int status;
	char p1[] = "thread_1";
	char p2[] = "thread_2";
	char p3[] = "thread_3";
	
	sleep(1); //1
		     
	thr_id = pthread_create(&pthread[0], NULL, p_function, (void*)p1); //2
	if(thr_id < 0) {
		perror("pthread0 create error");
		exit(EXIT_FAILURE);
	}
		     
	thr_id = pthread_create(&pthread[1], NULL, p_function, (void *)p2); //2
	if(thr_id < 0) {
		perror("pthread1 create error");                                                                  
		exit(EXIT_FAILURE);
	}
        p_function((void *)p3); //3
	
	pthread_join(pthread[0], (void **)&status); //6
       	pthread_join(pthread[1], (void **)&status);
	
	printf("end??\n");
	
	return 0;
}	
```

- `pthread_create` : 스레드를 생성하는 함수

   ```c
   #include <pthread.h>

   int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                      void *(*start_routine)(void *), void *arg);
   ```
   
   - `thread` : 생성된 스레드 ID를 담는 변수

   - `attr` : 스레드 속성 (NULL로 주면 기본값 사용)

   - `start_routine` : 스레드가 실행할 함수 (반드시 `void*` 리턴, `void*` 인자 받음)

   - `arg` : 스레드 함수에 전달할 인자

   <br/>

- `pthread_join` : 스레드 종료 대기

   ```c
   #include <pthread.h>

   int pthread_join(pthread_t thread, void **retval);
   ```

   - `thread` : 기다릴 스레드의 ID

   - `retval` : 스레드가 반환한 값을 받을 포인터 (필요 없으면 NULL)

   <br/>

- 결과

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step04-2.jpg?raw=true" alt="Example Image" width="90%">
   </div>


## 실습 : thread

1. **ex01**

   ```c
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
   ```

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step04-3.jpg?raw=true" alt="Example Image" width="90%">
   </div>

   <br/>


2. **ex02**

   ```c
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
   ```

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step04-4.jpg?raw=true" alt="Example Image" width="90%">
   </div>


## 참고

- [블로그 참고 - gmlwjd9405(프로세스와 스레드 차이)](https://gmlwjd9405.github.io/2018/09/14/process-vs-thread.html)

- [블로그 참고 - whtie5500(pthread란? pthread예제)](https://blog.naver.com/whtie5500/221692793640)


