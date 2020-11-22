#include <stdio.h>		//����� �������
#include <string.h>		//���ڿ� �Լ� ���
#include <ctype.h>      //isdigit �Լ� ���
#include <stdlib.h>		//exit �Լ� ���

#define MAX_STACK_SIZE 100		
#define MAX_INPUT 100

typedef char element;					//������ ������ ����ϴ� element type ����
typedef int lelement;					//�ǿ����� ������ ����ϴ� lelement type ����

typedef struct {						//������ ����. �迭�� ����.
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

typedef struct {						//�ǿ����� ����. ���� ����Ʈ�� ����.
	lelement data;
	struct StackNode* link;
}StackNode;

typedef struct {
	StackNode* top;
}LinkedStackType;

void init(StackType* s);				//������ ���ÿ� ���Ǵ� �Լ��� ����
int is_empty(StackType* s);
int is_full(StackType* s);
void push(StackType* s, element item);
element pop(StackType* s);
element peek(StackType* s);
int isp(char ch);
int icp(char ch);

void init_link(LinkedStackType* s);						//�ǿ����� ���ÿ� ���Ǵ� �Լ��� ����.
int is_empty_link(LinkedStackType* s);					//������ ���ÿ� ���Ǵ� �Լ���� �����ϱ� ���� �Լ��� ���ܿ� _link�� ���������� ����.
void push_link(LinkedStackType* s, lelement item);
lelement pop_link(LinkedStackType* s);

void infix_to_postfix(char exp[], char post[]);			//����ǥ����� ����ǥ������� ��ȯ�ϴ� �Լ�
int eval(char exp[]);									//����ǥ����� ���� ��ȯ�ϴ� �Լ�
void printArray(char exp[], int i);						//������ ���Ŀ� �°� ����ϴ� �Լ�

/*Main Function*/
int main() {
	int pnum, value;			//���� ���� �����ϴ� pnum ������ ������ �� ������ value ����
	element infix[MAX_INPUT] = { NULL };			//infix �迭 ����.

	FILE* fp = fopen("infix.txt", "r");				//���� ����
	fscanf(fp, "%d", &pnum);						//������ ���� �Է� ����.

	for (int i = 0; i < pnum; i++) {				//������ ������ŭ �ݺ��� ����.
		element postfix[MAX_INPUT] = { NULL };		//postfix�� �ݺ����� ������ ������ ������ �ʱ�ȭ����� �ϹǷ� �ݺ��� ���� ����.

		fscanf(fp, "%s", infix);					//����ǥ��� �Է¹޾Ƽ� infix�� ����
		printArray(infix, 0);						//����ǥ��� ���
		infix_to_postfix(infix, postfix);			//����ǥ����� ����ǥ������� ��ȯ�� postfix�� ����
		printArray(postfix, 1);						//����ǥ��� ���
		printf("value = %d", eval(postfix));		//����ǥ��� ���� ����Ͽ� ���
		printf("\n\n");
	}
}

/*����ǥ��� -> ����ǥ���*/
void infix_to_postfix(char exp[], char post[]) {
	char token, element;			//exp�� ���ڸ� post�� �̵���Ű�� �� �ʿ��� ���� ����
	int index = 0, count = 0;		//exp�� index�� ǥ���ϴ� index ������ post�� index�� ǥ���ϴ� count ����
	StackType s;		//���� ��ȯ�� ����� ���� ����

	init(&s);						//���� �ʱ�ȭ
	push(&s, '#');					//������ �������� �߰��� ������ ������ ���� �ľ�.
	for (token = exp[index++]; token != ';'; token = exp[index++]) {	//;�� ������ ����ǥ����� ���ʺ��� �о��.

		if (isdigit(token)) post[count++] = token;					//�ǿ������� ���. post�� �ٷ� ������ �� count�� ����������.
		else if (token == ')') {									//������ ��ȣ�� ���. ���� �ֻ�� ���� ���� ��ȣ�� �� ������ ���ÿ� ����� ������ post�� ������ �� count�� ������Ŵ.
			while (s.stack[s.top] != '(') {
				element = pop(&s);
				post[count++] = element;
			}
			pop(&s);												//���� ��ȣ ���ÿ��� ����
		}

		else {														//���� ��ȣ �� �������� ���.
			while (isp(s.stack[s.top]) >= icp(token)) {				//���� �ֻ�� ���� ISP���� ���ο� �������� ICP���� ���� ���� �ֻ���� ISP�� �� ū ���.
				element = pop(&s);									//���� �ֻ�� ���� post�� ������ �� count ������Ŵ.
				post[count++] = element;
			}
			push(&s, token);										//���ο� �����ڸ� ���ÿ� �߰�.
		}
	}
	while (peek(&s) != '#') {										//������ �ֻ�� ���� #(���� �� �ؿ� ��� �ִ� ��)�� �ƴ� ���.
		element = pop(&s);											//���ÿ��� ������ post�� ������ �� count ������Ŵ.
		post[count++] = element;
	}
	post[count++] = ';';											//post�� �����ݷ� ����.
}

/*����ǥ����� �� ���*/
int eval(char exp[]) {
	int op1, op2, value, i = 0;					//�ǿ����� ������ ���� 2��, ������ �� ������ ���� value, �ݺ����� �ʿ��� ���� i.
	int len = strlen(exp);						//���� ��ü ���� ����.
	char ch;									//���� �ϳ��� �о�� �� �ʿ��� ����.
	LinkedStackType s;							//���� �� ��꿡 ����ϴ� �ǿ����� ����

	init_link(&s);								//���� �ʱ�ȭ
	for (i = 0; i < len - 1; i++) {				//����ǥ��Ŀ��� �����ݷ��� ������ �κб����� �����ϴ� �ݺ���
		ch = exp[i];
		if (isdigit(ch)) {						//�ǿ������� ���.
			value = ch - '0';					//char ���� int ������ �ٲٱ� ���� ����.
			push_link(&s, value);				//�ǿ����� ���ÿ� ����.
		}
		else {													//�������� ���.
			op2 = pop_link(&s);									//�ǿ����� �� ���� ���ÿ��� ����.
			op1 = pop_link(&s);
			switch (ch) {										//������ ���� ���� �´� ���� ����.
			case '+': push_link(&s, op1 + op2); break;
			case '-': push_link(&s, op1 - op2); break;
			case '*': push_link(&s, op1 * op2); break;
			case '/': push_link(&s, op1 / op2); break;
			case '%': push_link(&s, op1 % op2); break;
			case '^': push_link(&s, op1 ^ op2); break;
			}
		}
	}

	return pop_link(&s);			//������ ���� ���� ����� ��ȯ


}

/*����ǥ���-> ����ǥ��Ŀ� ����ϴ� ������ ���� ���� �Լ�*/
void init(StackType* s) {							//���� �ʱ�ȭ �Լ�.
	s->stack[0] = '\0';
	s->top = -1;
}

int is_empty(StackType* s) {						//������ ������� Ȯ���ϴ� �Լ�
	return (s->top == -1);
}

int is_full(StackType* s) {							//������ �� á���� Ȯ���ϴ� �Լ�
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {				//���ÿ� ���� �߰��ϴ� �Լ�
	if (is_full(s)) {								//������ �� �� ���.
		printf("������ ��ȭ�����Դϴ�.");
		return;
	}
	else s->stack[++(s->top)] = item;				//���ÿ� ������ ���� ���. top���� ���� ������Ų �� ���� ����.
}

element pop(StackType* s) {							//���ÿ��� ���� ������ �Լ�
	if (is_empty(s)) {								//������ �� ���.
		printf("������ ��������Դϴ�.");
		exit(1);
	}
	else return s->stack[(s->top)--];				//���ÿ� ���Ұ� �ִ� ���. ���� ���� ���� �� top�� ���ҽ�Ŵ.
}

element peek(StackType* s) {						//������ �ֻ�� ���� Ȯ���ϴ� �Լ�
	if (is_empty(s)) {								//������ �� ���.
		printf("������ ��������Դϴ�.");
		exit(1);
	}
	else return s->stack[(s->top)];					//���ÿ� ���Ұ� �ִ� ���. ���� ������ ��ȯ.
}


int isp(char ch) {					//�������� ISP(���� ���� �켱����) ��ȯ�ϴ� �Լ�
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

	return -1;						//����
}

int icp(char ch) {					//�������� ICP(���� ���� �켱����) ��ȯ�ϴ� �Լ�
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

	return -1;						//����
}

void printArray(char exp[], int i) {			//���� ����ϴ� �Լ�
	if (i == 0)									//����ǥ����� ���
		printf("infix notation = ");

	else										//����ǥ����� ���
		printf("postfix notation = ");

	for (int j = 0; j < strlen(exp); j++) printf("%c ", exp[j]);		//������ ��� ���ҿ� ���� ���.
	printf("\n");
}


/*����ǥ����� �� ���ϴ� ���� ����ϴ� �ǿ����� ���� ���� �Լ�*/
void init_link(LinkedStackType* s) {						//���� �ʱ�ȭ�ϴ� �Լ�
	s->top = NULL;
}

int is_empty_link(LinkedStackType* s) {						//������ ������� Ȯ���ϴ� �Լ�
	return s->top == NULL;
}

void push_link(LinkedStackType* s, lelement item) {			//���ÿ� ���Ҹ� �����ϴ� �Լ�
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));		//�޸𸮸� ���Ӱ� �Ҵ� ����.
	if (temp == NULL) {										//�Ҵ���� �� �ִ� �޸𸮰� ���� ���.
		printf("�޸� �Ҵ� ����");
		return;
	}

	else {													//�޸𸮸� ���������� �Ҵ� ���� ���.
		temp->data = item;									//�����Ͱ��� ��ũ���� ���ο� ��忡 ���� �� top�� ���ο� ��带 ����Ű�� ��ȭ��Ŵ.
		temp->link = s->top;
		s->top = temp;
	}

}

lelement pop_link(LinkedStackType* s) {						//���ÿ��� ���Ҹ� ������ �Լ�
	if (is_empty_link(s)) {									//������ �� ���.
		printf("������ ��������Դϴ�.");
		exit(1);
	}

	else {													//���ÿ� ���Ұ� �ִ� ���
		StackNode* temp = s->top;							//���� �ֻ�� ����� ���� ��ȯ�ϰ� �ش� �޸𸮸� �ݳ���.
		int item = temp->data;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}