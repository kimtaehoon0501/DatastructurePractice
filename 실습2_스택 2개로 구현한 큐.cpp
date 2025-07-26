#include<stdio.h>

//Stack의 최대 크기
#define MAX 100

//원소를 정수형으로 정의.
typedef int element;

//Stack구조체
typedef struct {
	element e[MAX];
	int top;
}Stack;

// Stack을 초기화하는 함수.
void initStack(Stack *s) {
	s->top = -1;
}

//Stack이 비어있으면 1, 그렇지않으면 0 출력
int isEmpty(Stack *s) {
	if (s->top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

//Stack이 꽉 차있으면 1, 그렇지않으면 0 출력
int isFull(Stack* s) {
	if (s->top == MAX - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// Stack에 원소를 삽입
void Push(Stack* s,element e) {
	if (isFull(s)) {
		printf("Stack is Full");
	}
	else {
		s->top++;
		s->e[s->top] = e;
	}
}

// Stack의 top이 가리키고 있는 원소를 출력. stack이 비어있다면 -1을 리턴
element Pop(Stack* s) {
	if (isEmpty(s)) {
		printf("Stack is empty");
		return -1;
	}
	else {
		return s->e[s->top--];
	}
}

// Stack두개로 구현한 queue의 enqueue연산.
void enqueue(Stack* s1,Stack* s2,element e) {
	// 우선 스택에 원소를 삽입. 
	Push(s1, e);
	printf("\n[ENQUEUE] %d\n", e);
	// Stack1, Stack2의 상태를 출력한다. 
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

//Stack 두개로 구현한 dequeue연산이다. 
void dequeue(Stack* s1, Stack* s2) {
	printf("\n[DEQUEUE]\n");
	element e;
	//s2가 비어있다면, s1에있는 모든 원소를 s2에 push하고 pop연산을 한다.
	if (isEmpty(s2)) {
		// s1에 들어있는 모든 원소들을 s2에 넣어주는 작업.
		int s1top = s1->top;
		while (!isEmpty(s1)) {
			Push(s2, Pop(s1));
		}
	}
	// s2가 비어있지 않다면, 그냥 s2를 pop하면 된다. 
	e = Pop(s2);
	
	printf("반환된 값: %d\n", e);
	for (int i = 0; i <= s1->top; i++) {
		printf("%d ", s1->e[i]);
	}
	
	// 연산이 끝난 후, 각 Stack들의 상태를 출력
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
	// Stack두개를 선언 및 초기화한다. 
	Stack s1;
	Stack s2;
	initStack(&s1);
	initStack(&s2);
	// 구현에 사용되는 명령어 배열.
	int operations[] = { 10, 20, 30, -1, 40, 50, -1, -1, 60, -1, -1, -1 };

	// 배열의 원소 수
	int num = sizeof(operations) / sizeof(operations[0]);
	
	// 명령어를 출력한다. 
	printf("입력된 연산 (양수: enqueue, -1: dequeue): ");
	for (int i = 0; i <num; i++) {
		printf("%d ", operations[i]);
	}

	// n의 크기를 증가시켜가며, 명령어를 순차적으로 처리한다. 
	int n = 0;

	//명령어 배열안의 원소가 모두 사용될때까지 반복한다.  
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
