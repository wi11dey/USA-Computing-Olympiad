/*
 ID: arka.ma1
 LANG: C
 TASK: milk2
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int start_time = 1000000, end_time = 0;

void mark(unsigned char* timeline, int start, int end) {
	int i;
	for (i = start; i < end; i++) {
		timeline[i] = 1;
	}
}

int check(unsigned char* timeline, int starting_from, unsigned char check_for) {
	int count = 0, i;
	for (i = starting_from; i < end_time; i++) {
		if (timeline[i] == check_for) {
			count++;
		} else {
			return count;
		}
	}
	return count;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	FILE* input, * output;
	int n, longest_milking = 0, longest_idle = 0, i, start, end, current;
	unsigned char* timeline;
	timeline = malloc(sizeof(char) * 1000000);
	input = fopen("milk2.in", "r");
	output = fopen("milk2.out", "w");
	assert(input != NULL && output != NULL);
	fscanf(input, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(input, "%d %d", &start, &end);
		mark(timeline, start, end);
		start_time = min(start_time, start);
		end_time = max(end_time, end);
	}
	for (i = start_time; i < end_time; i++) {
		current = check(timeline, i, 0);
		i += current;
		longest_idle = max(longest_idle, current);
		current = check(timeline, i, 1);
		i += current - 1;
		longest_milking = max(longest_milking, current);

	}
	fprintf(output, "%d %d\n", longest_milking, longest_idle);
	free(timeline);
	fclose(input);
	fclose(output);
	return 0;
}
