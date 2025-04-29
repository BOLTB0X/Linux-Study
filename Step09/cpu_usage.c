#include <stdio.h>
#include <unistd.h>

unsigned long long get_cpu_time() {
	FILE *fp = fopen("/proc/stat", "r");
	
	if (!fp)
		return 0;
	
	char buffer[1024];
	fgets(buffer, sizeof(buffer), fp);
	fclose(fp);

	unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
	sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
		&user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);

	return user + nice + system + idle + iowait + irq + softirq + steal;
}

unsigned long long get_cpu_idle_time() {
	FILE *fp = fopen("/proc/stat", "r");
	
	if (!fp)
		return 0;
	
	char buffer[1024];
	fgets(buffer, sizeof(buffer), fp);
	fclose(fp);
	
	unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
	sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
			&user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
	
	return idle + iowait;
}

int main(void) {
	unsigned long long total1 = get_cpu_time();
	unsigned long long idle1 = get_cpu_idle_time();

	sleep(3);
	
	unsigned long long total2 = get_cpu_time();
        unsigned long long idle2 = get_cpu_idle_time();
	
	double usage = 100.0 * (1.0 - (double)(idle2 - idle1) / (total2 - total1));
	printf("CPU 사용률: %.2f%%\n", usage);
	
	return 0;
}
