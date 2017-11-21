#include <stdio.h>

char py[12][7], visit[12][7];
int cb;


#define MAX_H 12
#define MAX_W 6
#define MAX_NUM MAX_W * MAX_H

typedef struct s_info{

	int x;
	int y;
	char CH;

}Sinfo;

Sinfo Stackbuf[MAX_NUM + 1];
int stackcnt = 0;

int Push(Sinfo info){

	if (stackcnt > MAX_NUM - 1)
		return -1;

	Stackbuf[stackcnt++] = info;
	return stackcnt;

}

Sinfo Pop(void){

	return Stackbuf[--stackcnt];
}

void Clear(void){

	stackcnt = 0;
}



void mark(void){

	Sinfo info_pop;

	while (stackcnt > 0) {

		info_pop = Pop();
		py[info_pop.y][info_pop.x] = '.';
	}

	Clear();

}


void drop() {
	int i, j, k;
	for (j = 0; j <= 5; j++) {
		for (i = 11; i >= 0; i--) {
			if (py[i][j] == '.') {
				for (k = i - 1; k >= 0 && py[k][j] == '.'; k--);
				if (k >= 0) {
					py[i][j] = py[k][j];
					py[k][j] = '.';
				}
			}
		}
	}
}

int find(int x, int y, char CH) {
	if (x < 0 || x > 5 || y < 0 || y > 11 || py[y][x] != CH || visit[y][x] == cb) return 0;

	visit[y][x] = cb;
	if (CH == '.') return 0;
	int cnt = 1;


	Sinfo  info;

	info.x = x;
	info.y = y;
	info.CH = CH;


	Push(info);

	cnt += find(x + 1, y, CH);
	cnt += find(x - 1, y, CH);
	cnt += find(x, y + 1, CH); 
	cnt += find(x, y - 1, CH);

	return cnt;

}

int bomb(int x, int y, char clr) {

	if (x < 0 || x > 5 || y < 0 || y > 11 || py[y][x] != clr) return 0;
	
	py[y][x] = '.';

	bomb(x + 1, y, clr);
	bomb(x - 1, y, clr);
	bomb(x, y + 1, clr);
	bomb(x, y - 1, clr);

	return 0;
}

int main() {
	int i, j;
	char flg = 1;

	freopen("input.txt", "r", stdin);
	for (i = 0; i < 12; i++) 		scanf("%s", py[i]);

	for (cb = 1; flg; cb++) {
		flg = 0;
		for (i = 0; i <= 11; i++) {
			for (j = 0; j <= 5; j++) {
				if (find(j, i, py[i][j]) >= 4) {
					flg = 1;
					//bomb(j, i, py[i][j]);
					mark();

				}
				else {
					Clear();
				}
			}
		}
		drop();
	}
	printf("%d\n", cb - 2);
}