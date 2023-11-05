#include <stdlib.h>
#include <stdio.h>

struct fuel_stand {
	int occupy;
	int fuel;
	int end_rel;
};
typedef struct fuel_stand f;

int fuel_up(f* fst, int cur_rel, int car_fuel) {
	int temp_rel = 0;
	int index = 0;
	for (int i = 0; i < 2; i++) {
		if (fst[i].fuel < car_fuel) {
			if (i == 2 && temp_rel == 0) {
				return -1;
			}
			else continue;
		}
		if (fst[i].occupy == 0) {
			fst[i].fuel -= car_fuel;
			fst[i].end_rel = cur_rel + car_fuel;
			fst[i].occupy = 1;
			return cur_rel;
		}
		else {
			if (temp_rel == 0 || temp_rel > fst[i].end_rel) {
				temp_rel = fst[i].end_rel;
				index = i;
			}
		}
	}
	if (fst[index].end_rel > cur_rel) {
		fst[index].end_rel += car_fuel;
	}
	else {
		fst[index].end_rel = car_fuel + cur_rel;
		cur_rel = temp_rel;
	}
	return cur_rel;
}

int solution(int A[], int N, int X, int Y, int Z) {
    // Implement your solution here
    int cur_rel = 0;
	f fst[3] = {{0, X, 0}, {0, Y, 0}, {0, Z, 0},};
	for (int i = 0; i < N; i++) {
		cur_rel = fuel_up(fst, cur_rel, A[i]);
		if (cur_rel == -1) {
			return -1;
		}
	}
    return cur_rel;    
}