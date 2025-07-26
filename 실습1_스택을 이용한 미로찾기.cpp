#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 6
//������ ���Ҹ� ��ķ� �ٷ��.(��ġ�� ��ķ� �ٷ�� �����̴�)
typedef struct {
	short r;
	short c;
}element;

typedef struct {
	int top; //���� ������ �� ���κ�. -1�̸� ������ ������� �ǹ�.
	element *data ; //���� ���� ���ҵ�. ���⼱ �ڷ���� �������̹Ƿ�, element�� ��ü���ش�.
	int capacity ; //������ ũ��.
}stack;

//���� �ʱ�ȭ
void init(stack*s) {
	s->top = -1;
	s->capacity = 20;
	s->data = (element*)malloc(s->capacity * sizeof(element)); 
}

// ������ ������� Ȯ��
bool isempty(stack* s) {
	if (s->top == -1) {
		return 1;
	}
	else return 0;
}
// ������ ���� ���ִ��� Ȯ��. 
bool isfull(stack* s) {
	if (s->top == s->capacity - 1) {
		return 1;
	}
	else return 0;
}

//push-������ �� ������ �ʴٸ� ���Ҹ� ����ְ� �ε����� 1 ������Ŵ
void push(stack* s,element c) {
	if (isfull(s)) {
		fprintf(stderr,"the stack is full");
	}
	else {
		s->data[++(s->top)] = c;
	}
}
//pop- ������ ������� �ʴٸ� ���� top�� ����Ű���ִ� ���Ҹ� ������ ����.
element pop(stack *s) {
	if (isempty(s)) {
		fprintf(stderr,"the stack is empty");
		exit(1);
	}
	else {
		return s->data[s->top--];
		
	}
}
//pop�� �����ϳ�, ���Ҹ� ����ϰ� �������� �ʴ´�. 
element peek(stack* s) {
	if (isempty(s)) {
		fprintf(stderr,"the stack is empty");
		exit(1);
	}
	else {
		return s->data[s->top];
	}
}
//������ġ�� �Ա��� {1,0} �� 2�� 1���� ������Ŵ.
element here{ 1,0 }, entry{ 1,0 };

char maze[MAX][MAX] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','1','1','1','1'},
	{'1','0','0','1','1','1'},
	{'1','1','0','0','0','1'},
	{'1','1','1','1','x','1'}
};// �̷θ� 6X6���ó�� �ٷ��. ����-e �̵������� ��ġ-0 �̵��Ұ����� ��ġ-1 �ⱸ-x

//r - ��, c - ��. �̵������� ��ġ�� ���ÿ� push�Ѵ�. 
void push_loc(stack* s, int r, int c){

	if (r < 0 || c < 0) return;
	//�����ִ� �κ��� '1'��, �̹� ���� ��ġ�� .���� ǥ���Ѵ�. 
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

//�̵��� ���� �̷��� �����Ȳ�� ȭ�鿡 ���. 
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
	int r, c; //��� ���� �ش��ϴ� ���� ����.
	
	//��θ� ���� stack ���� �� �ʱ�ȭ
	stack s;
	init(&s);
	//����ġ�� �Ա��� ����.
	here = entry;
	
	//�ⱸ�� ã�������� �ݺ��Ѵ�. 
	while (maze[here.r][here.c] != 'x') {
		//����ġ�� r�� c�� �����Ѵ�. 
		r = here.r;
		c = here.c;
		//�̹� ������ ��ġ�� .���� ǥ���Ѵ�.
		maze[r][c] = '.';
		maze_print(maze);
		//��/��/��/�� �����ִ°��� stack�� push. ��-��-��-�� ������ �����Ѵ�. 
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		//������ ���������, �� �� �ִ� ���� ���ٴ� ���̴�. ��. ���и� �ǹ��Ѵ�.
		if (isempty(&s)) {
			printf("����\n");
			return 0;
		}
		//���ÿ��� pop�� element�� ����ġ�� �����Ѵ�. 
		else
			here = pop(&s);
	}
	printf("����\n");
	return 0;
}









