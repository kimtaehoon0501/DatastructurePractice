#include<stdio.h>

//Stack�� �ִ� ũ��
#define MAX 100

//���Ҹ� ���������� ����.
typedef int element;

//Stack����ü
typedef struct {
	element e[MAX];
	int top;
}Stack;

// Stack�� �ʱ�ȭ�ϴ� �Լ�.
void initStack(Stack *s) {
	s->top = -1;
}

//Stack�� ��������� 1, �׷��������� 0 ���
int isEmpty(Stack *s) {
	if (s->top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

//Stack�� �� �������� 1, �׷��������� 0 ���
int isFull(Stack* s) {
	if (s->top == MAX - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// Stack�� ���Ҹ� ����
void Push(Stack* s,element e) {
	if (isFull(s)) {
		printf("Stack is Full");
	}
	else {
		s->top++;
		s->e[s->top] = e;
	}
}

// Stack�� top�� ����Ű�� �ִ� ���Ҹ� ���. stack�� ����ִٸ� -1�� ����
element Pop(Stack* s) {
	if (isEmpty(s)) {
		printf("Stack is empty");
		return -1;
	}
	else {
		return s->e[s->top--];
	}
}

// Stack�ΰ��� ������ queue�� enqueue����.
void enqueue(Stack* s1,Stack* s2,element e) {
	// �켱 ���ÿ� ���Ҹ� ����. 
	Push(s1, e);
	printf("\n[ENQUEUE] %d\n", e);
	// Stack1, Stack2�� ���¸� ����Ѵ�. 
	printf("stack1 [bottom -> top]: ");
	if (isEmpty(s1)) {
		printf("(empty)");
	}
	else {
		for (int i = 0; i <= s1->top; i++) {
			printf("%d ", s1->e[i]);
		}
	}
	printf("\nstack2 [bottom -> top]: ");
	if (isEmpty(s2)) {
		printf("(empty)");
	}
	else {
		for (int i = 0; i <= s2->top ; i++) {
			printf("%d ", s2->e[i]);
		}
	}

}

//Stack �ΰ��� ������ dequeue�����̴�. 
void dequeue(Stack* s1, Stack* s2) {
	printf("\n[DEQUEUE]\n");
	element e;
	//s2�� ����ִٸ�, s1���ִ� ��� ���Ҹ� s2�� push�ϰ� pop������ �Ѵ�.
	if (isEmpty(s2)) {
		// s1�� ����ִ� ��� ���ҵ��� s2�� �־��ִ� �۾�.
		int s1top = s1->top;
		while (!isEmpty(s1)) {
			Push(s2, Pop(s1));
		}
	}
	// s2�� ������� �ʴٸ�, �׳� s2�� pop�ϸ� �ȴ�. 
	e = Pop(s2);
	
	printf("��ȯ�� ��: %d\n", e);
	for (int i = 0; i <= s1->top; i++) {
		printf("%d ", s1->e[i]);
	}
	
	// ������ ���� ��, �� Stack���� ���¸� ���
	printf("stack1 [bottom -> top]: ");
	if (isEmpty(s1)) {
		printf("(empty)");
	}
	else {
		for (int i = 0; i <= s1->top ; i++) {
			printf("%d ", s1->e[i]);
		}
	}
	printf("\nstack2 [bottom -> top]: ");
	if (isEmpty(s2)) {
		printf("(empty)");
	}
	else {
		for (int i = 0; i <= s2->top; i++) {
			printf("%d ", s2->e[i]);
		}
	}

}
int main() {
	// Stack�ΰ��� ���� �� �ʱ�ȭ�Ѵ�. 
	Stack s1;
	Stack s2;
	initStack(&s1);
	initStack(&s2);
	// ������ ���Ǵ� ��ɾ� �迭.
	int operations[] = { 10, 20, 30, -1, 40, 50, -1, -1, 60, -1, -1, -1 };

	// �迭�� ���� ��
	int num = sizeof(operations) / sizeof(operations[0]);
	
	// ��ɾ ����Ѵ�. 
	printf("�Էµ� ���� (���: enqueue, -1: dequeue): ");
	for (int i = 0; i <num; i++) {
		printf("%d ", operations[i]);
	}

	// n�� ũ�⸦ �������Ѱ���, ��ɾ ���������� ó���Ѵ�. 
	int n = 0;

	//��ɾ� �迭���� ���Ұ� ��� ���ɶ����� �ݺ��Ѵ�.  
	while (n<num) {
		if (operations[n] > 0&&n<num) {
			enqueue(&s1, &s2, operations[n]);
			n++;
		}
		else if (operations[n] == -1 && n < num) {
		n++;
		dequeue(&s1, &s2);
		}
	}

	return 0;

}
