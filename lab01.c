#include "stdio.h"
#include "time.h"

int count_zeroes(int n, char *buf){
	short zero = 0;
	for(int i = 0; i<n; i++){
		unsigned char j = buf[i];
		for(char k = 0; k<8; k++) {
			zero += !(j % 2);
			j /= 2;
		}
	}
	return zero;
}

int main(int argc, char** argv){
	size_t n;
	FILE* file;
	file = fopen("C:\\test.txt", "r");
	if (file == NULL){
		printf("Could not open %s.\n", "C:\\test.txt");
		return 1;
	}
	char buf[100];

	clock_t start = clock();

	int count = 0;
	while(1){
		n = fread(buf, 1, 100, file);
		if(n == 0){
			break;
		}
		count += count_zeroes(n, buf);
	}

	clock_t end = clock();

	fclose(file);
	double time = (double)(end - start)/(double)(CLOCKS_PER_SEC/1000);
	printf("Number of zeros: %d\n", count);
	printf("Time: %.3f ms\n", time);
	return 0;
}
