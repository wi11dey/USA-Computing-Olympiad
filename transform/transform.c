/*
 ID: arka.ma1
 LANG: C
 TASK: transform
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef unsigned char** square;

square allocate_square(int n) {
	int i;
	square retval;
	retval = malloc(sizeof(unsigned char*) * (size_t) n);
	for (i = 0; i < n; i++) {
		retval[i] = malloc(sizeof(unsigned char) * (size_t) n);
	}
	return retval;
}

void free_square(int n, square square) {
	int i;
	for (i = 0; i < n; i++) {
		free(square[i]);
	}
	free(square);
}

square read_square(int n, square into, FILE* input) {
	int i, j;
	char c;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(input, "%c ", &c);
			into[i][j] = c == '@' ? 1 : 0;
		}
	}
	return into;
}

void copy_square(int n, square src, square dest) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			dest[i][j] = src[i][j];
		}
	}
}

square transform_90_deg_rot(int n, square sq) {
	square temp = allocate_square(n);
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			temp[i][j] = sq[n - j - 1][i];
		}
	}
	copy_square(n, temp, sq);
	free_square(n, temp);
	return sq;
}

square transform_horiz_refl(int n, square sq) {
	square temp = allocate_square(n);
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			temp[i][j] = sq[i][n - j - 1];
		}
	}
	copy_square(n, temp, sq);
	free_square(n, temp);
	return sq;
}

unsigned char check_squares_equal(int n, square one, square two) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (one[i][j] != two[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

/* For debugging purposes only */
/*
 void print_square(int n, square square) {
 int i, j;
 for (i = 0; i < n; i++) {
 for (j = 0; j < n; j++) {
 printf("%c", (square[i][j]) ? '@' : '-');
 }
 printf("\n");
 }
 printf("\n");
 }
 */

int main() {
	FILE* input, *output;
	int n;
	square square1, square2;
	input = fopen("transform.in", "r");
	output = fopen("transform.out", "w");
	assert(input != NULL && output != NULL);
	fscanf(input, "%d ", &n);
	square1 = allocate_square(n);
	square2 = allocate_square(n);
	read_square(n, square1, input);
	read_square(n, square2, input);
	transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("1\n", output);
		goto exit;
	}
	transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("2\n", output);
		goto exit;
	}
	square1 = transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("3\n", output);
		goto exit;
	}
	transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("6\n", output);
		goto exit;
		/* a goto for exiting shouldn't be thaaat bad */
	}
	transform_horiz_refl(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("4\n", output);
		goto exit;
	}
	transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("5\n", output);
		goto exit;
	}
	transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("5\n", output);
		goto exit;
	}
	transform_90_deg_rot(n, square1);
	if (check_squares_equal(n, square1, square2)) {
		fputs("5\n", output);
		goto exit;
	}
	fputs("7\n", output);
	exit: fclose(input);
	fclose(output);
	free_square(n, square1);
	free_square(n, square2);
	return 0;
}
