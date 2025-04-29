# Step09: 리눅스 자원 사용률 측정 툴 만들기


리눅스 `/proc` 가상 파일 시스템을 이용해 실시간으로 CPU, 메모리 사용량을 출력하는 시스템 모니터링 Tool 구현

## 주요 개념

| 항목 | 설명 |
|------|------|
| `/proc/stat` | CPU 사용 시간 통계 |
| `/proc/meminfo` | 전체 메모리 및 사용 가능 메모리 정보 |
| `sleep(1)` | 1초 주기로 값을 갱신하기 위한 함수 |
| 시스템 자원 모니터링 | 시스템 상태를 주기적으로 확인하여 자원 점유율 파악 |

## CPU 실습코드

```c
unsigned long long get_cpu_time() {
    FILE *fp = fopen("/proc/stat", "r");
    char line[256];
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
    fgets(line, sizeof(line), fp);

    sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(fp);
    return user + nice + system + idle + iowait + irq + softirq;
```

- `/proc/stat` 파일을 통해 Read 해오는 함수

   - `cpu  122334 100 22345 9876543 1234 0 456 0 0 0`

   -  CPU가 지금까지 사용한 시간을 나타내며, 각각의 값은 단위가 **jiffies (1/100초 단위)**

-  모든 시간 값을 읽어 합산함

- 합산한 시간은 CPU가 작동한 총 시간을 의미하며, 이를 이전 시점과 비교해서 CPU 사용률을 계산할 수 있음

```c
total1 = get_cpu_total_time();
idle1 = get_cpu_idle_time();
sleep(1);
total2 = get_cpu_total_time();
idle2 = get_cpu_idle_time();
```

- 1초 간격으로 두 번 읽어서 두 시점 사이의 변화를 보고 사용률 = `(1 - idle 차이 / total 차이)` 로 계산

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

- `/proc/stat`의 첫 줄에서 idle + iowait 값을 읽어와 리턴

- 출력 예시

   ```
   CPU 사용률: 17.35%
   ```

## 메모리 실습 코드

```c
void print_memory_usage() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("fopen");
        return;
    }

    char key[32];
    unsigned long value;
    char unit[8];
    unsigned long mem_total = 0, mem_available = 0;

    while (fscanf(fp, "%s %lu %s", key, &value, unit) == 3) {
        if (strcmp(key, "MemTotal:") == 0) mem_total = value;
        if (strcmp(key, "MemAvailable:") == 0) {
            mem_available = value;
            break;
        }
    }
    fclose(fp);

    printf("Memory Usage: %.2f%% (%lu KB / %lu KB)\n",
           100.0 * (mem_total - mem_available) / mem_total,
           mem_total - mem_available, mem_total);
}
```

| 항목             | 설명                                                                 |
|------------------|----------------------------------------------------------------------|
| `/proc/meminfo`  | 시스템 메모리 정보를 텍스트로 보여주는 가상 파일 시스템              |
| MemTotal         | 전체 물리 메모리 용량 (단위: KB)                                     |
| MemAvailable     | 현재 사용 가능한 메모리 (캐시 및 버퍼 고려, 단위: KB)                |
| 사용률 계산      | `(MemTotal - MemAvailable) / MemTotal * 100`

- `fopen()`, `fscanf()`, `fclose()` : `/proc/meminfo` 파일 파싱

- `strcmp()` : 키 비교

- 출력 예시
  
   ```
   Memory Usage: 46.87% (3832876 KB / 8178304 KB)
   ```

