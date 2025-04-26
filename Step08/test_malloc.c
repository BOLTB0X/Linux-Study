#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int* arr = (int*)malloc(sizeof(int) * 5);

	if (arr == NULL) {
		printf("메모리 할당 실패\n");
		return 1;

	}

	for (int i = 0; i < 5; ++i) {
		arr[i] = i * 10;
	}

	for (int i = 0; i < 5; ++i) {
		printf("arr[%d] = %d\n", i, arr[i]);
	}

	free(arr);
	return 0;
}
