# Step06 - 프로세스 생성 및 제어

- `fork()`로 자식 프로세스 생성하기

- `exec()`로 다른 프로그램 실행하기

- `wait()`로 자식 프로세스 종료 대기하기

## `fork()` : 프로세스 복제

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork 실패");
        return 1;
    } else if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스: PID=%d, 부모 PID=%d\n", getpid(), getppid());
    } else {
        // 부모 프로세스
        printf("부모 프로세스: PID=%d, 자식 PID=%d\n", getpid(), pid);
    }

    return 0;
}
```

```
부모 프로세스: PID=1234, 자식 PID=1235
자식 프로세스: PID=1235, 부모 PID=1234
```

## `exec()` : 다른 프로그램 실행

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("exec 전에 출력\n");

    execl("/bin/ls", "ls", "-l", NULL);

    // exec 실패 시 아래 코드 실행
    perror("exec 실패");
    return 1;
}
```

```
exec 전에 출력
total 40
-rwxr-xr-x 1 box box 16048 Apr 23 18:22 exec_test
-rw-r--r-- 1 box box   219 Apr 23 18:21 exec_test.c
-rwxr-xr-x 1 box box 16136 Apr 23 18:19 fork_test
-rw-r--r-- 1 box box   386 Apr 23 18:18 fork_test.c
```

## `wait()` : 자식 프로세스 종료 대기

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("자식 프로세스 실행 중... PID=%d\n", getpid());
        sleep(2);
        printf("자식 프로세스 종료\n");
    } else {
        printf("부모가 자식 기다리는 중...\n");
        wait(NULL);
        printf("부모도 이제 종료\n");
    }

    return 0;
}
```

```
부모가 자식 기다리는 중...
자식 프로세스 실행 중... PID=5678
자식 프로세스 종료
부모도 이제 종료
```

