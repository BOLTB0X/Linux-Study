#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100

double get_memory_usage_percent() {
	FILE *fp = fopen("/proc/meminfo", "r");
	
	if (!fp) {
		perror("fopen");
		return -1;
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
	
	if (mem_total == 0) return -1;

	return 100.0 * (mem_total - mem_available) / mem_total;
}

int main(void) {
	FILE *fp = fopen("mem_usage.csv", "r");

	if (!fp) {
		perror("fopen");
		return 1;
	}

	double x[MAX_DATA];
	double y[MAX_DATA];

	int n = 0;
	char line[128];

	fgets(line, sizeof(line), fp);
	
	while (fgets(line, sizeof(line), fp)) {
		if (sscanf(line, "%lf,%lf", &x[n], &y[n]) == 2) {
			n++;
		}
	}
	
        fclose(fp);
	
	double today_usage = get_memory_usage_percent();
	
	if (today_usage < 0) {
		fprintf(stderr, "메모리 사용량 측정 실패\n");
		return 1;
	}

	x[n] = n;  // 오늘은 day n
	y[n] = today_usage;
	n++;

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
	    
	printf("오늘의 메모리 사용량: %.2f%%\n", today_usage);
	printf("Linear Regression: y = %.2fx + %.2f\n\n", a, b);
	    
	printf("예측 메모리 사용량 (다음 7일):\n");
	for (int i = x[n - 1] + 1; i <= x[n - 1] + 7; i++) {
		double pred = a * i + b;
		printf("  day %d: %.2f%%\n", i, pred);
	}

	return 0;
}
