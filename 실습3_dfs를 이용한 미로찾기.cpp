#include<stdio.h>

#define ROW 11
#define COL 10

typedef struct node {
	int x;
	int y;
};
int visited[11][10];

// a,b가 시작점이다. 
void dfs_maze(int maze[11][10], node start, node end) {
	// 이미 방문이 끝났으면 함수 즉시 종료. 
	if (visited[end.x][end.y] == 1) {
		return;
	}
	// 만약 start의 x,y 좌표가 범위 밖이거나, 이미 방문한 노드이거나, 갈 수 없는곳이라면 함수가 즉시 종료된다
	if (start.x < 0 || start.y < 0 || start.x>10 || start.y>9||visited[start.x][start.y]||maze[start.x][start.y]==1) {
		return;
	}
	
	// 현재위치를 시작점으로 놓는다. 
	node current = start;
	// 현재위치를 방문했다고 기록.
	visited[current.x][current.y] = 1;
	// 현재 위치를 화면에 출력.
	printf("\n");
	printf("Current position: (%d, %d)\n", current.x, current.y);
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			// 현재위치는 C로 출력. 
			if (i == current.x && j == current.y) {
				printf("C");
			}
			// 방문한 노드들은 .으로 출력
			else if (visited[i][j]) {
				printf(".");
			}
			// 이동할 수 없는 곳들은 #으로 출력. 
			else if (maze[i][j] == 1) {
				printf("#");
			}
			// 출구는 X로 출력한다. 
			else if (i == end.x && j == end.y) {
				printf("X");
			}
			// 이동할 수 있는 노드들은 0으로 출력한다. 
			else {
				printf("0");
			}	
		}
		printf("\n");
	}
	node up, down, right, left;
	up.x = current.x - 1, up.y = current.y; // 북
	down.x = current.x + 1, down.y = current.y; // 남
	left.x = current.x, left.y = current.y - 1; // 서
	right.x = current.x, right.y = current.y + 1; // 동
	dfs_maze(maze, up, end);
	dfs_maze(maze, down, end);
	dfs_maze(maze, left, end);
	dfs_maze(maze, right, end);
}

int main() {
	// 방문한 노드를 전부 0으로 초기화.
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			visited[i][j] = 0;
		}
	}
	// converted maze(given)
	int maze1[ROW][COL] = {

	   {1,1,1,1,1,1,1,1,0,1},

	   {1,0,0,0,0,0,0,1,0,1},

	   {1,0,1,1,1,1,1,1,0,1},

	   {1,0,1,0,0,0,0,0,0,1},

	   {1,0,1,0,1,1,1,1,1,1},

	   {1,0,0,0,0,0,0,0,0,1},

	   {1,0,1,1,1,1,0,1,0,1},

	   {1,0,1,0,0,1,0,1,0,1},

	   {1,1,1,0,1,1,0,1,0,1},

	   {1,0,0,0,0,0,0,1,0,1},

	   {1,1,1,1,1,1,1,1,0,1}

	};
	//start point(node)
	node start = {0,8};
	//end point(node)
	node end = {10,8};
	// dfs search
	dfs_maze(maze1, start, end);

	// if there is no path to end point
	if (!visited[end.x][end.y]) {
		printf("No path found");
	}

	return 0;
}