# Linux-Study

![으앙아ㅏ아아아아아아앆!!!!!!!!!!!!!!!!!!!!](https://mblogthumb-phinf.pstatic.net/MjAyMzA3MjJfMjk1/MDAxNjkwMDAwMjcxNTMy.QzlvysvM4AS6aq9DXrrsIdjZb89bBoE2scnhRGwwnTEg.HWqcHMAuZaMcY5skL-w_UJ01rmUzqKeO3Pc-aQME1C4g.GIF.dydtmd4/%EB%84%B7.gif?type=w800)


## Step 0 Setup

- 우분투 환경 설정

- 리눅스 기본 명령어

- vim 사용해서 "Hello Linux World!" 출력

- git 업로드

## [Step 1 Linux File / Directory 다루기 + Process 다루기](https://github.com/BOLTB0X/Linux-Study/tree/main/Step01)


- 프로세스 관리를 통해 시스템을 운영하는 운영체제 가 리눅스

   Sleep 30초 실습

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step01-%EA%B2%B0%EA%B3%BC.jpg?raw=true" alt="Example Image" width="90%">
   </div>

## [Step 2 Linux File system 구조 와 권한](https://github.com/BOLTB0X/Linux-Study/tree/main/Step02)


- 리눅스는 모든 것을 **File** 형태로 인식하고 처리

- HW 장치, 디렉토리, 프로세스 등 다양한 자원을 **File**처럼 다룸

## [Step 3 Linux 패키지 와 빌드 시스템](https://github.com/BOLTB0X/Linux-Study/tree/main/Step03)

- 패키지

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/%EB%A6%AC%EB%88%85%EC%8A%A4%20%EC%8B%A4%EC%8A%B5%20step03.jpg?raw=true" alt="Example Image" width="70%">
   </div>

   *리눅스 시스템에서 소프트웨어를 실행하는데 필요한 파일들(실행 파일, 설정 파일, 라이브러리 등)이 담겨 있는 설치 파일 묶음*
   
   <br/>

- 컴파일과 빌드(Build), Makefile과 빌드 시스템
   
   - `gcc hello.c -o hello`
   
   
   - `make` 라는 자동화 도구와 **Makefile** 이라는 스크립트를 사용

## [Step 4 Process & Thread](https://github.com/BOLTB0X/Linux-Study/tree/main/Step04)

- **Process**

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step04-1.jpg?raw=true" alt="Example Image" width="90%">
   </div>

   *프로그램의 의미는 "어떤 작업을 위해 실행할 수 있는 파일"*

- **Thread**

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step04-3.jpg?raw=true" alt="Example Image" width="90%">
   </div>

   *프로세스 내에서 실행되는 여러 흐름 단위*

## [Step 5 System Call 과 사용자/커널 모드 이해](https://github.com/BOLTB0X/Linux-Study/tree/main/Step05)

- **System Call**

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step05-2.jpg?raw=true" alt="Example Image" width="90%">
   </div>

   *운영 체제의 커널이 제공하는 서비스에 대해, 응용 프로그램의 요청에 따라 커널에 접근하기 위한 인터페이스*

- 커널

   *운영체제의 핵심(Core) 으로, 하드웨어와 소프트웨어를 연결해주는 중재자(bridge) 역할*

## [Step 6 프로세스 생성 및 제어](https://github.com/BOLTB0X/Linux-Study/tree/main/Step06)

- `fork()`

   *자식 프로세스 생성하기*

- `exec()`
 
    *다른 프로그램 실행하기*

- `wait()`

   *자식 프로세스 종료 대기하기*

## [Step 7 파일 입출력과 표준 스트림](https://github.com/BOLTB0X/Linux-Study/tree/main/Step07)

- 리눅스에서 C 언어로 파일 입출력과 표준 스트림을 다루는 이유 는 단순히 `printf` , `scanf` 보다 더 낮은 수준의 제어와 성능 , 그리고 시스템 자원과 직접 통신 하는 능력을 주기 때문

## [Step 8 메모리 구조와 동적 메모리 할당](https://github.com/BOLTB0X/Linux-Study/tree/main/Step08)

|영역 | 설명|
|----|-----|
| **Text** | 코드가 저장된 영역 (기계어, 읽기 전용) |
| **Data** | 초기화된 전역/정적 변수 저장 영역 |
| **BSS** | 초기화되지 않은 전역/정적 변수 저장 영역 |
| **Heap** | 실행 중 동적으로 할당되는 메모리 영역 (`malloc` 등) |
| **Stack** | 함수 호출 시 생성되는 지역 변수 및 함수 프레임 저장 영역|

## [Step 9 리눅스 자원 사용률 측정 툴 만들기](https://github.com/BOLTB0X/Linux-Study/tree/main/Step09)

<div style="text-align: center;">
   <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step09.jpg?raw=true" alt="Example Image" width="90%">
</div>

```c
unsigned long long get_cpu_idle_time() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return 0;

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);

    return idle + iowait;
}
```

## [Step 10 메모리 사용량 예측기 (CSV 기반 + 자동 측정)](https://github.com/BOLTB0X/Linux-Study/tree/main/Step10)

<div style="text-align: center;">
   <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step10.jpg?raw=true" alt="Example Image" width="90%">
</div>

```c
// 선형 회귀
double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
for (int i = 0; i < n; i++) {
	sum_x += x[i];
	sum_y += y[i];
		
	sum_xy += x[i] * y[i];
	sum_x2 += x[i] * x[i];
}

double a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
double b = (sum_y - a * sum_x) / n;
```
