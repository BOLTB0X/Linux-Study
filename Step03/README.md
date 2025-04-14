# Step 03 - 패키지와 빌드 시스템

## Package

> 리눅스 시스템에서 소프트웨어를 실행하는데 필요한 파일들(실행 파일, 설정 파일, 라이브러리 등)이 담겨 있는 설치 파일 묶음

SW를 설치하기 쉽게 포장한 파일

cf. *Window 에서 `.exe` or `.msi`*

cf. *Mac 에서 `.dmg`*

cf. *Linux 에서 `.deb`(Ubuntu) or `.rpm`(RedHat)* 

- Source Package

   - Source Code 가 들어 있는 패키지
   
   - 컴파일 과정을 통해 바이너리 파일로 만들어야 실행 가능

   - 소스 패키지를 사용하는 이유

      - 내가 원하는 대로 소프트웨어를 수정해서 사용할 수 있음
   <br/>

- Binary Package

   - 컴파일된 바이너리 파일이 들어 있는 패키지

   - 소스 패키지에 비해 설치 시간도 짧고 오류가 발생할 가능성도 적음

   - 리눅스의 기본 설치 패키지들은 대부분 바이너리 패키지

   - 내 컴퓨터 환경과 바이너리 패키지가 컴파일된 환경이 달라서 문제가 발생할 수 있음

   - 바이너리 패키지를 제대로 실행하기 위해서는 특정 라이브러리나 다른 패키지가 필요한 경우가 존재 -> 이런 패키지 간의 의존성을 **Package Dependencies**
   <br/>

## apt Package

1. `apt` 란 ?

   - Advanced Packaging Tool

   - 우분투/데비안 계열에서 패키지를 쉽게 설치하고 관리해주는 Tool
   <br/>

2. 기본 명령어

   | 명령어                        | 설명                   |
   |-----------------------------|------------------------|
   | `sudo apt update`           | 패키지 목록 최신화     |
   | `sudo apt upgrade`          | 설치된 패키지 최신화   |
   | `sudo apt install 패키지` | 새 패키지 설치         |
   | `sudo apt remove 패키지`  | 패키지 제거             |
   | `apt search 키워드`       | 패키지 검색             |
   <br/>

3. ex

   ```
   sudo apt update
   sudo apt install gcc make cowsay
   ```
   
   ```
   cowsay "패키지는 이런 거야~"
   figlet Step 03
   ```
   <br/>

## 컴파일과 빌드(Build)

C 같은 고급 언어를 기계어로 번역해서 CPU가 실행할 수 있도록 만드는 작업

```
gcc hello.c -o hello
```

이 명령은 hello.c를 컴파일해서 실행 가능한 hello 바이너리를 생성

`gcc`는 GNU 컴파일러이고, C/C++ 외에도 다양한 언어를 지원

## Makefile과 빌드 시스템

> 하나의 `.c` 파일만 있으면 `gcc hello.c -o hello`로 끝나지만

> `.c` 파일이 수십 개고, 헤더파일 `.h` , 라이브러리 등도 존재할 경우 

**make** 라는 자동화 도구와 **Makefile** 이라는 스크립트를 사용

```
# 예시

# 변수 정의
CC = gcc
TARGET = hello
SRC = hello.c

# 기본 빌드 명령
all:
    $(CC) $(SRC) -o $(TARGET)

# 정리(clean)
clean:
    rm -f $(TARGET)
```

```
make       # hello 생성됨
./hello    # 실행
make clean # 실행 파일 제거
```

이 구조는 리눅스 커널, 드라이버, 펌웨어, 오픈소스 프로젝트 전반에서 널리 사용

## 참고

- [블로그 - bradbury(리눅스 패키지(Linux Package)에 대한 이해)](https://bradbury.tistory.com/227)

- [블로그 - killsia(Make 기반 빌드 시스템: Makefile 기초)](https://killsia.tistory.com/entry/Make-%EA%B8%B0%EB%B0%98-%EB%B9%8C%EB%93%9C-%EC%8B%9C%EC%8A%A4%ED%85%9C-Makefile-%EA%B8%B0%EC%B4%88)
