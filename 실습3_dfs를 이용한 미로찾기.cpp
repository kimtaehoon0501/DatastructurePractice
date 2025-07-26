#include<stdio.h>

#define ROW 11
#define COL 10

typedef struct node {
	int x;
	int y;
};
int visited[11][10];

// a,b�� �������̴�. 
void dfs_maze(int maze[11][10], node start, node end) {
	// �̹� �湮�� �������� �Լ� ��� ����. 
	if (visited[end.x][end.y] == 1) {
		return;
	}
	// ���� start�� x,y ��ǥ�� ���� ���̰ų�, �̹� �湮�� ����̰ų�, �� �� ���°��̶�� �Լ��� ��� ����ȴ�
	if (start.x < 0 || start.y < 0 || start.x>10 || start.y>9||visited[start.x][start.y]||maze[start.x][start.y]==1) {
		return;
	}
	
	// ������ġ�� ���������� ���´�. 
	node current = start;
	// ������ġ�� �湮�ߴٰ� ���.
	visited[current.x][current.y] = 1;
	// ���� ��ġ�� ȭ�鿡 ���.
	printf("\n");
	printf("Current position: (%d, %d)\n", current.x, current.y);
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			// ������ġ�� C�� ���. 
			if (i == current.x && j == current.y) {
				printf("C");
			}
			// �湮�� ������ .���� ���
			else if (visited[i][j]) {
				printf(".");
			}
			// �̵��� �� ���� ������ #���� ���. 
			else if (maze[i][j] == 1) {
				printf("#");
			}
			// �ⱸ�� X�� ����Ѵ�. 
			else if (i == end.x && j == end.y) {
				printf("X");
			}
			// �̵��� �� �ִ� ������ 0���� ����Ѵ�. 
			else {
				printf("0");
			}	
		}
		printf("\n");
	}
	node up, down, right, left;
	up.x = current.x - 1, up.y = current.y; // ��
	down.x = current.x + 1, down.y = current.y; // ��
	left.x = current.x, left.y = current.y - 1; // ��
	right.x = current.x, right.y = current.y + 1; // ��
	dfs_maze(maze, up, end);
	dfs_maze(maze, down, end);
	dfs_maze(maze, left, end);
	dfs_maze(maze, right, end);
}

int main() {
	// �湮�� ��带 ���� 0���� �ʱ�ȭ.
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