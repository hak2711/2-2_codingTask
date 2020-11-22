#include <stdio.h>		//입출력 헤더파일
#include <string.h>		//문자열 함수 사용
#include <ctype.h>      //isdigit 함수 사용
#include <stdlib.h>		//exit 함수 사용

#define MAX_STACK_SIZE 100		
#define MAX_INPUT 100

typedef char element;					//연산자 스택이 사용하는 element type 정의
typedef int lelement;					//피연산자 스택이 사용하는 lelement type 정의

typedef struct {						//연산자 스택. 배열로 구현.
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

typedef struct {						//피연산자 스택. 연결 리스트로 구현.
	lelement data;
	struct StackNode* link;
}StackNode;

typedef struct {
	StackNode* top;
}LinkedStackType;

void init(StackType* s);				//연산자 스택에 사용되는 함수들 선언
int is_empty(StackType* s);
int is_full(StackType* s);
void push(StackType* s, element item);
element pop(StackType* s);
element peek(StackType* s);
int isp(char ch);
int icp(char ch);

void init_link(LinkedStackType* s);						//피연산자 스택에 사용되는 함수들 선언.
int is_empty_link(LinkedStackType* s);					//연산자 스택에 사용되는 함수들과 구분하기 위해 함수명 말단에 _link를 공통적으로 붙임.
void push_link(LinkedStackType* s, lelement item);
lelement pop_link(LinkedStackType* s);

void infix_to_postfix(char exp[], char post[]);			//중위표기식을 후위표기식으로 변환하는 함수
int eval(char exp[]);									//후위표기식의 값을 반환하는 함수
void printArray(char exp[], int i);						//수식을 형식에 맞게 출력하는 함수

/*Main Function*/
int main() {
	int pnum, value;			//문장 개수 저장하는 pnum 변수와 수식의 값 저장할 value 변수
	element infix[MAX_INPUT] = { NULL };			//infix 배열 생성.

	FILE* fp = fopen("infix.txt", "r");				//파일 열기
	fscanf(fp, "%d", &pnum);						//수식의 개수 입력 받음.

	for (int i = 0; i < pnum; i++) {				//수식의 개수만큼 반복문 시행.
		element postfix[MAX_INPUT] = { NULL };		//postfix는 반복문을 시행할 때마다 별도로 초기화해줘야 하므로 반복문 내에 선언.

		fscanf(fp, "%s", infix);					//중위표기식 입력받아서 infix에 저장
		printArray(infix, 0);						//중위표기식 출력
		infix_to_postfix(infix, postfix);			//중위표기식을 후위표기식으로 변환해 postfix에 저장
		printArray(postfix, 1);						//후위표기식 출력
		printf("value = %d", eval(postfix));		//후위표기식 값을 계산하여 출력
		printf("\n\n");
	}
}

/*중위표기식 -> 후위표기식*/
void infix_to_postfix(char exp[], char post[]) {
	char token, element;			//exp의 문자를 post로 이동시키는 데 필요한 문자 변수
	int index = 0, count = 0;		//exp의 index를 표기하는 index 변수와 post의 index를 표기하는 count 변수
	StackType s;		//수식 변환에 사용할 스택 생성

	init(&s);						//스택 초기화
	push(&s, '#');					//스택의 마지막에 추가해 수식이 끝나는 시점 파악.
	for (token = exp[index++]; token != ';'; token = exp[index++]) {	//;를 제외한 중위표기식을 왼쪽부터 읽어나감.

		if (isdigit(token)) post[count++] = token;					//피연산자인 경우. post에 바로 저장한 후 count값 증가시켜줌.
		else if (token == ')') {									//오른쪽 괄호인 경우. 스택 최상단 값이 왼쪽 괄호가 될 때까지 스택에 저장된 값들을 post에 저장한 후 count값 증가시킴.
			while (s.stack[s.top] != '(') {
				element = pop(&s);
				post[count++] = element;
			}
			pop(&s);												//왼쪽 괄호 스택에서 삭제
		}

		else {														//왼쪽 괄호 및 연산자인 경우.
			while (isp(s.stack[s.top]) >= icp(token)) {				//스택 최상단 값의 ISP값과 새로운 연산자의 ICP값을 비교해 스택 최상단의 ISP가 더 큰 경우.
				element = pop(&s);									//스택 최상단 값을 post에 저장한 후 count 증가시킴.
				post[count++] = element;
			}
			push(&s, token);										//새로운 연산자를 스택에 추가.
		}
	}
	while (peek(&s) != '#') {										//스택의 최상단 값이 #(스택 맨 밑에 깔려 있는 값)가 아닌 경우.
		element = pop(&s);											//스택에서 꺼내서 post에 저장한 후 count 증가시킴.
		post[count++] = element;
	}
	post[count++] = ';';											//post에 세미콜론 저장.
}

/*후위표기식의 값 계산*/
int eval(char exp[]) {
	int op1, op2, value, i = 0;					//피연산자 저장할 변수 2개, 수식의 값 저장할 변수 value, 반복문에 필요한 변수 i.
	int len = strlen(exp);						//수식 전체 길이 저장.
	char ch;									//문자 하나씩 읽어가는 데 필요한 변수.
	LinkedStackType s;							//수식 값 계산에 사용하는 피연산자 스택

	init_link(&s);								//스택 초기화
	for (i = 0; i < len - 1; i++) {				//후위표기식에서 세미콜론을 제외한 부분까지만 시행하는 반복문
		ch = exp[i];
		if (isdigit(ch)) {						//피연산자인 경우.
			value = ch - '0';					//char 형을 int 형으로 바꾸기 위한 과정.
			push_link(&s, value);				//피연산자 스택에 저장.
		}
		else {													//연산자인 경우.
			op2 = pop_link(&s);									//피연산자 두 개를 스택에서 꺼냄.
			op1 = pop_link(&s);
			switch (ch) {										//연산자 값에 따라 맞는 연산 시행.
			case '+': push_link(&s, op1 + op2); break;
			case '-': push_link(&s, op1 - op2); break;
			case '*': push_link(&s, op1 * op2); break;
			case '/': push_link(&s, op1 / op2); break;
			case '%': push_link(&s, op1 % op2); break;
			case '^': push_link(&s, op1 ^ op2); break;
			}
		}
	}

	return pop_link(&s);			//수식의 최종 연산 결과를 반환


}

/*중위표기식-> 후위표기식에 사용하는 연산자 스택 구현 함수*/
void init(StackType* s) {							//스택 초기화 함수.
	s->stack[0] = '\0';
	s->top = -1;
}

int is_empty(StackType* s) {						//스택이 비었는지 확인하는 함수
	return (s->top == -1);
}

int is_full(StackType* s) {							//스택이 꽉 찼는지 확인하는 함수
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {				//스택에 원소 추가하는 함수
	if (is_full(s)) {								//스택이 꽉 찬 경우.
		printf("스택이 포화상태입니다.");
		return;
	}
	else s->stack[++(s->top)] = item;				//스택에 공간이 남은 경우. top값을 먼저 증가시킨 후 값을 대입.
}

element pop(StackType* s) {							//스택에서 원소 빼내는 함수
	if (is_empty(s)) {								//스택이 빈 경우.
		printf("스택이 공백상태입니다.");
		exit(1);
	}
	else return s->stack[(s->top)--];				//스택에 원소가 있는 경우. 먼저 값을 빼낸 후 top값 감소시킴.
}

element peek(StackType* s) {						//스택의 최상단 원소 확인하는 함수
	if (is_empty(s)) {								//스택이 빈 경우.
		printf("스택이 공백상태입니다.");
		exit(1);
	}
	else return s->stack[(s->top)];					//스택에 원소가 있는 경우. 값을 빼내어 반환.
}


int isp(char ch) {					//연산자의 ISP(스택 내부 우선순위) 반환하는 함수
	switch (ch) {
	case '(':
	case '#':
		return 0;
	case '+':
	case '-':
		return 12;
	case '*':
	case '/':
	case '%':
		return 13;
	case '^':
		return 14;
	}

	return -1;						//예외
}

int icp(char ch) {					//연산자의 ICP(스택 진입 우선순위) 반환하는 함수
	switch (ch) {
	case '(':
		return 20;
	case '+':
	case '-':
		return 12;
	case '*':
	case '/':
	case '%':
		return 13;
	case '^':
		return 15;
	}

	return -1;						//예외
}

void printArray(char exp[], int i) {			//수식 출력하는 함수
	if (i == 0)									//중위표기식인 경우
		printf("infix notation = ");

	else										//후위표기식인 경우
		printf("postfix notation = ");

	for (int j = 0; j < strlen(exp); j++) printf("%c ", exp[j]);		//수식의 모든 원소에 대해 출력.
	printf("\n");
}


/*후위표기식의 값 구하는 데에 사용하는 피연산자 스택 구현 함수*/
void init_link(LinkedStackType* s) {						//스택 초기화하는 함수
	s->top = NULL;
}

int is_empty_link(LinkedStackType* s) {						//스택이 비었는지 확인하는 함수
	return s->top == NULL;
}

void push_link(LinkedStackType* s, lelement item) {			//스택에 원소를 삽입하는 함수
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));		//메모리를 새롭게 할당 받음.
	if (temp == NULL) {										//할당받을 수 있는 메모리가 없는 경우.
		printf("메모리 할당 에러");
		return;
	}

	else {													//메모리를 정상적으로 할당 받은 경우.
		temp->data = item;									//데이터값과 링크값을 새로운 노드에 넣은 후 top을 새로운 노드를 가르키게 변화시킴.
		temp->link = s->top;
		s->top = temp;
	}

}

lelement pop_link(LinkedStackType* s) {						//스택에서 원소를 꺼내는 함수
	if (is_empty_link(s)) {									//스택이 빈 경우.
		printf("스택이 공백상태입니다.");
		exit(1);
	}

	else {													//스택에 원소가 있는 경우
		StackNode* temp = s->top;							//스택 최상단 노드의 값을 반환하고 해당 메모리를 반납함.
		int item = temp->data;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}