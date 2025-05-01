# Step07 입출력과 표준 스트림

> 리눅스에서 **C 언어로 파일 입출력과 표준 스트림을 다루는 이유** 는 단순히 `printf` , `scanf` 보다

> 더 **낮은 수준의 제어와 성능** , 그리고 **시스템 자원과 직접 통신** 하는 능력을 주기 때문

## 왜 C에서 파일 입출려과 표준 스트림을 배우는 가?

1. **시스템 프로그래밍의 기본**

   - 리눅스는 모든 걸 **file** 처럼 다두는 구조

      - 일반 파일, 디바이스(마우스, 키보드) , 네트워크 소켓까지 전부 **파일 디스크립터** 로 접근

   - **C의 시스템 콜(`open` , `read` , `write` , `close`)** 은 실제 HW 나 커널 과의 통신을 가능하게 함

   <br/>

2. **고성능, 직접 제어**

   - `fopen` , `fwrite` 같은 고수준 함수보다 더 빠르고 유연함

      - ex) *버퍼를 건너뛰고 바로 디스크에 쓰거나, 파일 권한 설정 등도 세세하게 조절 가능*

   <br/>

3. **에러 핸들링과 디버깅에 유리**

   - `write(2, "에러!\n", 7);` 같이 `stderr` 직접 제어 가능

   - `perror` , `errno` 를 활요하면 왜 실패 했는지 추척 가능


##  표준 스트림 (Standard Stream)

| 이름     | 파일 디스크립터 번호 | 설명             |
|----------|----------------------|------------------|
| `stdin`    | 0                    | 표준 입력 (키보드) |
| `stdout`   | 1                    | 표준 출력 (터미널) |
| `stderr`   | 2                    | 표준 에러 출력     |

## 파일 디스크립터 (File Descriptor)


- 리눅스에서 **파일, 디바이스, 소켓 등 자원을 숫자로 식별** 하는 방식

- `open()` 등의 함수는 파일 디스크립터를 반환

## 파일 열기 모드 (flag)

`open()` 함수에서 사용하는 **flag** , 파일을 어떤 목적으로 열지 지정해주는 역할

| 플래그       | 설명                                |
|--------------|-------------------------------------|
| `O_RDONLY`     | 읽기 전용으로 열기                   |
| `O_WRONLY`     | 쓰기 전용으로 열기                   |
| `O_RDWR`       | 읽기/쓰기 모두 가능하게 열기         |
| `O_CREAT`      | 파일이 없으면 새로 생성              |
| `O_TRUNC`      | 기존 파일 내용 모두 지우고 열기       |
| `O_APPEND`     | 파일 끝에 내용 추가                   |

- ex:) `int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);`

   - `O_WRONLY` : 쓰기 전용 으로 open

   - `O_CREAT` : 파일이 없으면 생성

   - `O_TRUNC` : 기존에 있던 파일 내용은 전부 삭제

   - `0644` : 파일 권한 (소유자 읽기/쓰기, 그룹과 다른 사용자는 읽기만 가능)

## 실습

### 1. `write()` 로 파일에 문자열 저장하기

```c
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        write(2, "파일 열기 실패\n", 16);
        return 1;
    }

    write(fd, "Hello, Linux!\n", 14);
    close(fd);
    return 0;
}
```

### 2. `read()` 로 파일 내용 읽기

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char buffer[128];
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        perror("파일 열기 실패");
        return 1;
    }

    int n = read(fd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0'; // 문자열 끝 처리
    printf("읽은 내용: %s", buffer);

    close(fd);
    return 0;
}
```

## 결과


![ㅇ](https://github.com/BOLTB0X/Linux-Study/blob/main/img/Step07.jpg?raw=true)