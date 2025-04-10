# Step02 Linux File system 구조 와 권한

> Server / FW 에서의 필수 개념

- 리눅스는 모든 자원(Resorce)을 **파일** 로 관리

- Device , Process , Network Socket 까지 전부 **파일** 로 취급

## File System

> OS가 파일 , 디렉토리를 효율적 / 구조적으로 관리하기 위한 트리구조 시스템을 총칭

- `/` : Linux 파일 체제의 최상위 directory

- `bin` : binaryse의 약어로 기본 명령어 실행 파일

- `boot` : 부팅에 핵심적인 커널 이미지와 부팅 정보 파일을 담고 있는 directory

- `dev` : device 파일들이 저장되어 있는 directory

- `etc` : 시스템 환경 설정 파일이 있는 directory

- `home` : 사용자의 home directory(사용자 계정명과 동일)

- `media` : 외부 device 를 연결하는 directory

- `mnt` : 파일 시스템을 임시로 연결하는 directory

- `root` : 시스템 관리자의 Home directory

- `sbin` : `bin` 유사하지만 오직 root 유저만 실행할 수 있는 프로그램들이 있는 directory

- `sys` : 리눅스 커널 관련 정보가 있는 directory

- `tmp` : 시스템 사용 중에 발생한 임시 data가 저장되는 directory

- `usr` : 기본 실행파일과 라이브러리 파일, 헤더 파일등의 파일이 저장되어 있는 directory

- `var` : 시스템 운영중에 발생한 data와 로그가 저장 되는 디렉토리
 
## Linux 권한 (Permission)

Linux File은 아래와 같이 권한으로 구성

```
-rwxr-xr--  1  user  user  1234  Apr 9  hello
```

| 구간  | 의미               | 해석              |
|-------|------------------|-----------------|
| `rwx`   | Owner (파일 소유자)  | 읽기, 쓰기, 실행 |
| `r-x`   | Group (그룹 사용자)  | 읽기, 실행      |
| `r--`   | Others (그 외 사용자) | 읽기           |

| 문자 | 숫자 | 의미         |
|------|------|--------------|
|`r`    | 4    | read (읽기)  |
|`w`    | 2    | write (쓰기) |
|`x`    | 1    | execute (실행) |


- ex) `chmod 755 hello`

   - 7 (`rwx`) : Ower

   - 5 (`r-x`) : Group

   - 5 (`r-x`) : Others

