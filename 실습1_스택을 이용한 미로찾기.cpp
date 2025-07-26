#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 6
//스택의 원소를 행렬로 다룬다.(위치를 행렬로 다루기 때문이다)
typedef struct {
	short r;
	short c;
}element;

typedef struct {
	int top; //현재 스택의 맨 윗부분. -1이면 스택이 비었음을 의미.
	element *data ; //스택 안의 원소들. 여기선 자료들이 순서쌍이므로, element로 교체해준다.
	int capacity ; //스택의 크기.
}stack;

//스택 초기화
void init(stack*s) {
	s->top = -1;
	s->capacity = 20;
	s->data = (element*)malloc(s->capacity * sizeof(element)); 
}

// 스택이 비었는지 확인
bool isempty(stack* s) {
	if (s->top == -1) {
		return 1;
	}
	else return 0;
}
// 스택이 가득 차있는지 확인. 
bool isfull(stack* s) {
	if (s->top == s->capacity - 1) {
		return 1;
	}
	else return 0;
}

//push-스택이 꽉 차있지 않다면 원소를 집어넣고 인덱스를 1 증가시킴
void push(stack* s,element c) {
	if (isfull(s)) {
		fprintf(stderr,"the stack is full");
	}
	else {
		s->data[++(s->top)] = c;
	}
}
//pop- 스택이 비어있지 않다면 현재 top이 가리키고있는 원소를 꺼내고 삭제.
element pop(stack *s) {
	if (isempty(s)) {
		fprintf(stderr,"the stack is empty");
		exit(1);
	}
	else {
		return s->data[s->top--];
		
	}
}
//pop과 유사하나, 원소를 출력하고 삭제하지 않는다. 
element peek(stack* s) {
	if (isempty(s)) {
		fprintf(stderr,"the stack is empty");
		exit(1);
	}
	else {
		return s->data[s->top];
	}
}
//현재위치와 입구를 {1,0} 즉 2행 1열로 고정시킴.
element here{ 1,0 }, entry{ 1,0 };

char maze[MAX][MAX] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','1','1','1','1'},
	{'1','0','0','1','1','1'},
	{'1','1','0','0','0','1'},
	{'1','1','1','1','x','1'}
};// 미로를 6X6행렬처럼 다룬다. 시작-e 이동가능한 위치-0 이동불가능한 위치-1 출구-x

//r - 행, c - 열. 이동가능한 위치를 스택에 push한다. 
void push_loc(stack* s, int r, int c){

	if (r < 0 || c < 0) return;
	//막혀있는 부분을 '1'로, 이미 갔던 위치를 .으로 표현한다. 
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

//이동에 따른 미로의 진행상황을 화면에 출력. 
void maze_print(char maze[MAX][MAX])
{
	printf("\n");
	for (int r = 0; r < MAX; r++) {
		for (int c = 0; c < MAX; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}
int main(void)
{	
	int r, c; //행과 열에 해당하는 변수 선언.
	
	//경로를 담을 stack 선언 및 초기화
	stack s;
	init(&s);
	//현위치를 입구로 설정.
	here = entry;
	
	//출구를 찾을때까지 반복한다. 
	while (maze[here.r][here.c] != 'x') {
		//현위치를 r과 c에 대입한다. 
		r = here.r;
		c = here.c;
		//이미 지나간 위치는 .으로 표현한다.
		maze[r][c] = '.';
		maze_print(maze);
		//상/하/좌/우 갈수있는곳을 stack에 push. 상-하-좌-우 순서로 시행한다. 
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		//스택이 비어있으면, 갈 수 있는 곳이 없다는 뜻이다. 즉. 실패를 의미한다.
		if (isempty(&s)) {
			printf("실패\n");
			return 0;
		}
		//스택에서 pop한 element를 현위치로 설정한다. 
		else
			here = pop(&s);
	}
	printf("성공\n");
	return 0;
}









