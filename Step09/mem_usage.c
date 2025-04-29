#include <stdio.h>
#include <string.h>

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
		if (strcmp(key, "MemTotal:") == 0) 
			mem_total = value;
		
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

int main(void) {
	print_memory_usage();
	return 0;
}

