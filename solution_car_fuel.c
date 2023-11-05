#include <stdio.h>
#include <stdlib.h>

struct fuel_stand {
	int occupy;
	int fuel;
	int end_rel;
};
typedef struct fuel_stand f;

int fuel_up(f* fst, int cur_rel, int car_fuel) {
	int temp_rel = 0;
	int index = 0;
	for (int i = 0; i < 3; i++) {
		if (fst[i].fuel < car_fuel) {
			if (i == 2 && temp_rel == 0) {
				return -1;
			}
			else continue;
		}
		if (cur_rel >= fst[i].end_rel && fst[i].occupy == 1) {
		    fst[i].occupy = 0;
		}
		if (fst[i].occupy == 0) {
			fst[i].fuel -= car_fuel;
			fst[i].end_rel = cur_rel + car_fuel;
			fst[i].occupy = 1;
			printf("ocp=0, fst[%d].end_rel=%d,cur_rel:%d,car_fuel:%d\n",i,fst[i].end_rel,cur_rel,car_fuel);
			return cur_rel;
		}
		else {
			if (temp_rel == 0 || temp_rel > fst[i].end_rel) {
				temp_rel = fst[i].end_rel;
				index = i;
			}
		}
	}
	fst[index].fuel -= car_fuel;
	//fst[i].occupy = 1;
	if (fst[index].end_rel > cur_rel) {
		cur_rel = fst[index].end_rel;
		fst[index].end_rel += car_fuel;
	}
	else {
		fst[index].end_rel = car_fuel + cur_rel;
		cur_rel = temp_rel;
	}

	printf("ocp=1, fst[%d].end_rel=%d,cur_rel:%d,car_fuel:%d\n",index,fst[index].end_rel,cur_rel,car_fuel);
	return cur_rel;
}

int solution(int A[], int N, int X, int Y, int Z) {
// Implement your solution here
    int cur_rel = 0;
    f* fst;
    fst = malloc(3 * sizeof(*fst));
	fst[0] = (f) {0, X, 0};
	fst[1] = (f) {0, Y, 0};
	fst[2] = (f) {0, Z, 0};

	for (int i = 0; i < N; i++) {
		cur_rel = fuel_up(fst, cur_rel, A[i]);
		if (cur_rel == -1) {
			return -1;
		}
	}
    return cur_rel;    
}

int main()
{
    int A[10] = {2,8,4,3,2,4,1,3,7,3};
    int re = solution(A, 10, 7, 20, 10);
    //if (re == -1) re = 100;
    printf("%d", re);
    return 0;
}