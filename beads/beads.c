/*
 ID: arka.ma1
 LANG: C
 TASK: beads
 */

/*
 * beads.c
 *
 *  Created on: Nov 21, 2015
 *      Author: Arka Majumdar
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

char* array_rotl1(int num_beads, char* necklace) {
	char temp = necklace[0];
	int i;
	for (i = 0; i < num_beads - 1; i++) {
		necklace[i] = necklace[i + 1];
	}
	necklace[num_beads - 1] = temp;
	return necklace;
}

int count_beads(int num_beads, char* necklace, unsigned char reverse) {
	char current_color;
	char bead;
	int i, count = 1;
	if (num_beads == 0) {
		return 0;
	}
	current_color = necklace[(reverse) ? num_beads - 1 : 0];
	for (i = (reverse) ? num_beads - 2 : 1;
			(reverse) ? (i >= 0) : (i < num_beads); i += (reverse) ? -1 : 1) {
		bead = necklace[i];
		if (current_color == 'w' && bead != 'w') {
			count++;
			current_color = bead;
		} else if (bead == current_color || bead == 'w') {
			count++;
		} else {
			break;
		}
	}
	return count;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	FILE* input, *output;
	int num_beads, i, count = 0, just_taken;
	char* necklace;
	input = fopen("beads.in", "r");
	output = fopen("beads.out", "w");
	assert(input != NULL && output != NULL);
	fscanf(input, "%d", &num_beads);
	necklace = malloc(sizeof(char) * (size_t) num_beads);
	fscanf(input, "%s", necklace);
	for (i = 0; i < num_beads; i++) {
		just_taken = count_beads(num_beads, necklace, 0);
		count = max(count,
				just_taken
						+ count_beads(num_beads - just_taken,
								necklace + just_taken, 1));
		necklace = array_rotl1(num_beads, necklace);
	}
	fprintf(output, "%d\n", count);
	free(necklace);
	fclose(input);
	fclose(output);
	return 0;
}
