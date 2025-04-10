# Step 01 Linux File / Directory 다루기 + Process 다루기 기초

## File / Directory 다루기

1. File

   ```bash
   touch memo,txt
   ```
   
   ```bash
   echo "이게 내 최고 지점이야...!" > memo.txt
   cat memo.txt
   ```

   ```bash
   cp memo.txt momo2.txt
   mv memo.txt memo2.txt 
   ```

2. Directory

   ```bash
   mkdir testdir
   cp -r testdir testdir_copy
   rm -r testdir_copy
   ```

## Process

> Process 는 실행 중인 프로그램을 의미


1. Linux = Process 관리의 세계

   - 리눅스는 곧 **MultiTasking OS**

   - 여러 개의 프로그램(=프로세스)이 동시에 실행 되어짐

   - 리눅스의 핵심 역할 = Procees 관리

2. 실습

   - 현재 Process 확인

      ```bash
      ps aux | less
      ```

   - sleep.c

      ```c
      #include <stdio.h>
      #include <unistd.h>

      int main(void) {
         printf("Sleeping for 30 sec....\n");
         sleep(30);
         return 0;
      }
      ```

      ```bash
      gcc sleep.c -o sleep
      ./sleep
      ```

3. 새로운 터미널에서 프로세스 확인 및 죽이기

   ```bash
   ps aux | grep sleep
   kill -9 [PID] # PID는 Process ID
   ```

## Process 를 다룰 수 있어야 한다

> 임베디드든 프론트든 서버든 최소한은 ...

- 어떤 Process 가 떠 있는 지 : `ps`

- 어떤 Process가 문제를 일으키는 지 : `top`

- Process를 죽이거나 : `kill`

- 백그라운드 실행을 하거나 : `&` , `nohup`

- ex)

   | 상황 | 해결|
   | ---- | --- |
   | 서버에 프로그램이 안돌아 감 | `ps` 로 Process 확인|
   | CPU 사용량이 너무 높음      | `top` 명령어로 확인 후 문제 Process `kill`|
   | 만든 프로그램이 멈췄음      | 로그 보기 , Process 죽이고 재실행|  
