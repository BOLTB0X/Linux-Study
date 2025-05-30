# Step05 System Call 과 사용자/커널 모드 이해하기

## 시스템 콜 (System Call)

> 운영 체제의 커널이 제공하는 서비스에 대해, 응용 프로그램의 요청에 따라 커널에 접근하기 위한 인터페이스

- 응용 프로그램은 OS가 제공하는 인터페이스를 통해서만 자원을 사용 함

   - 이러한 인터페이스를 **System Call** 이라 함

- 사용자 프로그램은 직접 하드웨어나 커널 자원에 접근할 수 없기 때문에, 시스템 콜을 통해 커널에 기능을 요청

   - **시스템콜** 을 **API(라이브러리 함수)** 를 통해 사용

## 시스템 콜 종류

1. 프로세스 제어

   > 프로세스 생성 , 종료 , 상태 제어 등을 위한 시스템 콜

   - `fork()` : 현재 프로세스를 복제하여 자식 프로세스 생성

   - `exec()` 계열 : 새 프로그램을 현재 프로세스에 로드하여 실행

   - `exit()` : 현재 프로세스 종료

   - `wait()` : 자식 프로세스 종료까지 대기

   - `getpid()` : 현재 프로세스 ID 반환

   - `getppid()` : 부모 프로세스 ID 반환

   - `kill()` : 특정 프로세스에 시그널 전송

2. 파일 조작

   > 파일 생성 , 열기 , 읽기 , 쓰기 , 닫기 등

   - `open()` : 파일 열기

   - `read()` : 파일에서 data 읽기

   - `write()` : 파일에 data 쓰기

   - `close()` : 열린 파일 닫기

   - `lseek()` : 파일 오프셋(커서) 이동

   - `unlink()` : 파일 삭제

   - `stat()` : 파일 정보 가져오기

3. Device 관리

   > 하드웨어 장치 접근 및 제어

   - `ioctl()` : 장치 제어를 위한 인터페이스

   - `read()` : 장치에서 데이터 읽기 (파일처럼 사용)

   - `write()` : 장치에 데이터 쓰기

   - `open()`/`close()` : 장치 열기 및 닫기

   cf. 리눅스에서 대부분 device 는 파일 형태 (`/dev/...`) 로 접근함

   <br/>

4. 정보 유지

   > 시간 , UID , 시스템 정보 등을 조회하거나 설정

   - `getuid()` : 사용자 ID 가져오기

   - `getgid()` : 그룹 ID 가져오기

   - `gettimeofday()` : 현재 시간 정보 가져오기

   - `uname()` : 시스템 이름, 버전 등 정보 조회

   - `times()` : 프로세스 실행 시간 정보 조회

      <br/>


5. 통신

   > 프로세스 간 통신 (IPC), 네트워크 통신 등

   - `pipe()` : 파이프 생성 (부모-자식 프로세스 통신)

   - `socket()` : 소켓 생성 (네트워크 통신)

   - `bind()` : 소켓에 주소 할당

   - `listen()` : 연결 요청 대기

   - `accept()` : 연결 수락

   - `send()` / `recv()` : 데이터 송수신 (소켓 기반)

   - `shmget()` : 공유 메모리 영역 생성

   - `mmap()` : 메모리 매핑

      <br/>


6. 보호

   > 접근 권한 , 권한 변경 등 시스템 보호 관련

   - `chmod()` : 파일 권한 변경

   - `chown()` : 파일 소유자 변경

   - `umask()` : 기본 권한 마스크 설정

   - `setuid()` : 사용자 ID 설정 (권한 상승)

   - `access()` : 파일 접근 권한 확인

      <br/>


cf. 각 시스템 콜을 대부분 `man 2 <함수명>` 으로 확인 가능
   - ex : `man 2 fork` , `man 2 write`

      <br/>


## 커널 (Kernel)

> 사전적인 의미는 "알맹이, 핵심"

> 컴퓨터 운영 체제의 핵심이 되는 컴퓨터 프로그램

- **운영체제의 핵심(Core)** 으로, 하드웨어와 소프트웨어를 연결해주는 **중재자(bridge)** 역할

- 프로그램이 하드웨어 자원(CPU, 메모리, 저장장치 등)을 효율적이고 안전하게 사용할 수 있도록 도와주는 것

## 커널의 주요 역할

역할 | 설명
---- | ----
프로세스 관리 | 프로세스 생성, 종료, 스케줄링, 상태 전이 관리 등
메모리 관리 | 각 프로세스에 메모리를 적절히 할당하고 보호
파일 시스템 관리 | 파일 생성/삭제, 읽기/쓰기, 디렉토리 구조 관리 등
입출력 장치 제어 | 키보드, 마우스, 디스크, 네트워크 등 하드웨어 장치 제어
시스템 콜 인터페이스 | 사용자 프로그램이 커널 기능을 요청할 수 있도록 인터페이스 제공
보안 및 권한 관리 | 사용자 권한, 파일 접근 제어 등 시스템 보안 유지

## 커널의 종류

유형 | 설명
---- | ----
모놀리식 커널 | 모든 기능이 하나의 큰 커널 공간에서 동작. 빠르지만 오류 시 전체 시스템에 영향. ex: Linux
마이크로커널 | 최소한의 기능만 커널에 포함. 나머지는 사용자 공간에서 동작. 안정성 높음. ex: Minix, QNX
하이브리드 커널 | 모놀리식과 마이크로커널의 장점을 결합한 형태. ex: Windows NT, macOS

## 리눅스 커널의 특징

- 모놀리식 커널 구조를 기반으로 하지만, 동적으로 모듈을 삽입할 수 있는 유연함을 가짐 (`insmod` , `rmmod` 명령어 등)

- 다양한 하드웨어를 지원

- 오픈 소스로 누구나 수정/배포 가능

- 리눅스 배포판(Debian, Ubuntu, CentOS 등)들은 모두 같은 커널을 기반으로 사용

cf. 리눅스 시스템에서 커널은 일반적으로 `/boot` 디렉토리에 존재

   - ex: `/boot/vmlinuz-<커널버전>`

cf. 커널 업데이트

```
# 커널 업그레이드 명령어 (Ubuntu 기준)
sudo apt update
sudo apt upgrade

# 설치된 커널 목록 확인
dpkg --list | grep linux-image
```

## 실습

- `pid_check`

   ```c
   #include <stdio.h>
   #include <unistd.h>

   int main(void) {
	   printf("내 PID (getpid): %d\n" , getpid());
	   printf("부모 PID (getppid) %d\n" , getppid());
	
	   return 0;
   }
   ```

   <br/>

1. **ex01**

   ```c
   #include <stdio.h>
   #include <unistd.h>

   int main(void) {
	   pid_t pit = getpid();
	   printf("현재 프로세스 ID: %d\n", pit);
	   return 0;
   }
   ```

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step05-1.jpg?raw=true" alt="Example Image" width="90%">
   </div>

   <br/>

2. **ex02**

   ```c
   #include <unistd.h>

   int main(void) {
	   const char *msg = "hello, System Call!\n";
	   write(1, msg, 21);
	   return 0;
   }
   ```

   <div style="text-align: center;">
      <img src="https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step05-2.jpg?raw=true" alt="Example Image" width="90%">
   </div>


## 참고

- [블로그 참고 - brightstarit(운영체제(OS), 시스템 콜(System Call))](https://brightstarit.tistory.com/13)

- [블로그 참고 - seohee-ha(커널(Kernel)이란 ?)](https://seohee-ha.tistory.com/255)


