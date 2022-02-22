#include<graphics.h>
#include<deque>
#include<cstdlib>
#include<time.h>
using namespace std;
typedef struct {
	int x;
	int y;
}board;
deque<board> Snake(1);
board fruit;
int Direction=1;
int map[50][30];
time_t Start_t, End_t;
void Initgame();
void Gamedraw();
void Gamemove();
void Playermove();
void BlockDraw();
void Gameover();
int main() {
	Initgame();
	BeginBatchDraw();
	while (1) {
		Gamemove();
		Gamedraw();
		BlockDraw();
		Playermove();
		FlushBatchDraw();
		Sleep(100);
	}
	return 0;
}
void Initgame() {
	initgraph(1000, 600);
	setbkcolor(WHITE);
	cleardevice();
	memset(map, 0, sizeof(map));
	board First;
	First.x = rand() % 50;
	First.y = rand() % 30;
	fruit.x= rand() % 50;
	fruit.y= rand() % 30;
	map[fruit.x][fruit.y] = 1;
	for (int i = 0; i < 50; i++) {
		map[i][0] = 2;
		map[i][29] = 2;
	}
	for (int i = 0; i < 30; i++) {
		map[0][i] = 2;
		map[49][i] = 2;
	}
	Snake.push_front(First);
}
void Gamedraw() {
	cleardevice();
	setfillcolor(RED);
	for (auto i = Snake.begin(); i < Snake.end(); i++) {
		fillrectangle((*i).x * 20, (*i).y * 20, (*i).x * 20 + 20, (*i).y * 20 + 20);
		if (i == Snake.begin()) {
			setfillcolor(BLACK);
		}
		else {
			map[(*i).x][(*i).y] = -1;
		}
	}
}
void Gamemove() {
	if (map[Snake.front().x][Snake.front().y] == 0) {
		map[Snake.back().x][Snake.back().y] = 0;
		Snake.pop_back();
	}
	else if(map[Snake.front().x][Snake.front().y] ==1){
		map[Snake.front().x][Snake.front().y] = 0;
		fruit.x = rand() % 50;
		fruit.y = rand() % 30;
		map[fruit.x][fruit.y] = 1;
	}
	else if(map[Snake.front().x][Snake.front().y] == -1|| map[Snake.front().x][Snake.front().y] == 2){
		Gameover();
	}
	board Tem;
	switch (Direction) {
	case 1:Tem.x = Snake.front().x; Tem.y = Snake.front().y + 1; break;//向下运动
	case 2:Tem.x = Snake.front().x; Tem.y = Snake.front().y - 1; break;//向上运动
	case 3:Tem.x = Snake.front().x+1; Tem.y = Snake.front().y; break;//向右运动
	case 4:Tem.x = Snake.front().x - 1; Tem.y = Snake.front().y; break;//向左运动
	}
	Snake.push_front(Tem);
}
void Playermove() {
	if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))&&Direction!=1) {
		Direction = 2;
	}
	if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && Direction != 2) {
		Direction = 1;
	}
	if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && Direction != 3) {
		Direction = 4;
	}
	if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && Direction != 4) {
		Direction = 3;
	}
}
void BlockDraw() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 30; j++) {
			if (map[i][j] == 1) {
				setfillcolor(BLUE);
				solidcircle(i * 20 + 10, j * 20 + 10, 10);
			}
			else if (map[i][j] == 2) {
				setfillcolor(DARKGRAY);
				fillrectangle(i * 20, j * 20, i * 20 + 20, j * 20 + 20);
			}
		}
	}
}
void Gameover() {
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(120, 0, _T("楷体"));
	outtextxy(200, 220, _T("Game Over!"));
	FlushBatchDraw();
	Sleep(2000);
	ExitProcess(0);
}