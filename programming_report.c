#include <stdio.h>          // ����� ��� ����
#define MAX_VERTICES 100    // �ִ� ���� ��
#define MAX_STACK_SIZE 100  // �ִ� ���� ������
#define MAX_QUEUE_SIZE 100  // �ִ� ť ������

typedef int element;

typedef struct {            // �׷��� ��� ����
	element vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct {            // ��ü �׷��� ����
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

typedef struct {			// ���� ����Ʈ ����
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

typedef struct {			// ȯ�� ť ����Ʈ ����
	element queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
}QueueType;

void topsort_stack(GraphType* g);  // ������ �̿��� ���������Լ�
void topsort_queue(GraphType* g);  // ť�� �̿��� ���������Լ�

void init_stack(StackType* s);	   // ���� ��� ���� �Լ�			
int is_empty_stack(StackType* s);
int is_full_stack(StackType* s);
void push(StackType* s, element item);
element pop(StackType* s);

void init_queue(QueueType* q);     // ť ��� ���� �Լ�
int is_empty_queue(QueueType* q);
int is_full_queue(QueueType* q);
void enqueue(QueueType* q, element item);
element dequeue(QueueType* q);

int main() {
	int nodeNum = 0, edgeNum = 0;     // ���������� �������� ������ ����
	GraphType graph = { 0, NULL };  // �׷����� �����ϸ鼭 �ʱ�ȭ

	FILE* fp = fopen("dag5.txt", "r");  // ������ �б� ���� ����

	if (fp == NULL) {  // ���� ������ ����ִ� ���
		printf("������ �������.");
		return 1;
	}

	fscanf(fp, "%d%d", &nodeNum, &edgeNum);  //���������� �������� �о ����
	graph.n = nodeNum; // �׷����� ���� ���� ����

	//��������Ʈ�� ���� ���� ������ ����
	for (int i = 0; i < edgeNum; i++) {
		int fromNode, toNode;
		fscanf(fp, "%d%d", &fromNode, &toNode);

		GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));  // ����� ��� ������ ������ ���ο� ��� ����
		GraphNode* temp = graph.adj_list[fromNode];

		if (temp == NULL) { // ù ��° ��尡 ����ִ� ���, ���� ����� ���� ������ ���� ���
			graph.adj_list[fromNode] = (GraphNode*)malloc(sizeof(GraphNode)); // ù ��° ��带 ����
			temp = graph.adj_list[fromNode];
			temp->link = newNode; // ù ��° ��尡 ���ο� ��带 ����Ű���� ��
		}
		else {
			while ((temp->link) != NULL) { //��ũ�� �� ��尡 ���� ������ ����
				temp = temp->link;
			}
			temp->link = newNode; // ��ũ�� �� ��尡 ���ο� ��带 ����Ű���� ��
		}

		newNode->vertex = toNode; // ���ο� ����� vertex�� ����� ��� ������ ����
		newNode->link = NULL; // ���ο� ����� ��ũ�� �ʱ�ȭ

	}

	printf("���� ��� �������� ��� = ");
	topsort_stack(&graph); // �������� ���������ϴ� �Լ�
	printf("\nť ��� �������� ��� = ");
	topsort_queue(&graph); // ť�� ���������ϴ� �Լ�

	fclose(fp); // ���� �ݱ�
}

void topsort_stack(GraphType* g) { // �������� ���������ϴ� �Լ�
	int i;
	StackType s;
	GraphNode* node;
	int flag = 0;

	int* in_degree = (int*)malloc(g->n * sizeof(int)); // ���������� ������ ����Ʈ

	for (i = 0; i < g->n; i++) // ���������� 0���� �ʱ�ȭ
		in_degree[i] = 0;

	for (i = 0; i < g->n; i++) { // �׷��� ���� ���¸� Ȯ���� �� ���� ���������� ����� ����
		GraphNode* node = g->adj_list[i];
		while ((node != NULL) && (node->link != NULL)) { // ù ��° ��尡 ������� �ʰ�, ù ��° ��尡 ����Ű�� �ִ� ��尡 �ִ� ���
			node = node->link;
			in_degree[node->vertex]++; // ���������� �ִ� ����� �������� ������Ŵ
		}
	}

	init_stack(&s); // ���� �ʱ�ȭ
	for (i = 0; i < g->n; i++) { // ���������� 0�� ������ ���ÿ� �����ϰ� �� ������ŭ flag�� ������Ŵ
		if (in_degree[i] == 0) {
			push(&s, i);
			flag++;
		}
	}

	while (!is_empty_stack(&s)) { // ������ ��� ������ ����
		element w;
		w = pop(&s); // ���ÿ��� ��� �ϳ��� pop
		printf("%d ", w); // �ش� ��带 ���
		node = g->adj_list[w];

		while ((node != NULL) && (node->link != NULL)) { // �ش� ��忡 ����Ǿ� �ִ� ��尡 �ִ� ��� 
			node = node->link;
			element u = node->vertex;
			in_degree[u]--; // w�� ����Ǿ� �ִ� ����� ���������� ���ҽ�Ŵ
			if (in_degree[u] == 0) { // ���� �� 0�� �� ���� ���ÿ� �����ϰ� �� ������ŭ flag ������Ŵ
				push(&s, u);
				flag++;
			}
		}
	}

	if (flag < g->n) // ���ÿ� ��� ��尡 ������� �ʾҴµ� while���� Ż���ߴٸ�(������ ����ٸ�) �������� �Ұ�
		printf("Impossible");



	free(in_degree); // ���������� ������ �޸𸮸� ����
	return;
}


void topsort_queue(GraphType* g) { //ť�� ���������ϴ� �Լ�
	int i;
	QueueType q;
	GraphNode* node;
	int flag = 0;

	int* in_degree = (int*)malloc(g->n * sizeof(int)); // �������� ������ ����Ʈ

	for (i = 0; i < g->n; i++) // ���������� 0���� �ʱ�ȭ
		in_degree[i] = 0;

	for (i = 0; i < g->n; i++) { // �׷��� ���� ���¸� Ȯ���� �� ���� ���������� ����� ����
		GraphNode* node = g->adj_list[i];
		while ((node != NULL) && (node->link != NULL)) { // ù ��° ��尡 ������� �ʰ�, ù ��° ��尡 ����Ű�� �ִ� ��尡 �ִ� ���
			node = node->link;
			in_degree[node->vertex]++; // ���������� �ִ� ����� �������� ������Ŵ
		}
	}

	init_queue(&q); // ť �ʱ�ȭ
	for (i = 0; i < g->n; i++) { // ���������� 0�� ������ ť�� �����ϰ� �� ������ŭ flag�� ������Ŵ
		if (in_degree[i] == 0) {
			enqueue(&q, i);
			flag++;
		}
	}

	while (!is_empty_queue(&q)) { // ť�� ��� ������ ����
		element w;
		w = dequeue(&q); // ť���� ���� �ϳ��� ���� �� w�� �����ϰ� ���
		printf("%d ", w);
		node = g->adj_list[w];

		while ((node != NULL) && (node->link != NULL)) { // �ش� ��忡 ����Ǿ� �ִ� ��尡 �ִ� ���
			node = node->link;
			element u = node->vertex;
			in_degree[u]--; // w�� ����Ǿ� �ִ� ����� ���������� ���ҽ�Ŵ
			if (in_degree[u] == 0) { // ���� �� 0�� �� ���� ť�� �����ϰ� �� ������ŭ flag ������Ŵ
				enqueue(&q, u);
				flag++;
			}
		}
	}

	if (flag < g->n) // ť�� ��� ��尡 ������� �ʾҴµ� while���� Ż���ߴٸ�(ť�� ����ٸ�) �������� �Ұ�
		printf("Impossible");



	free(in_degree); // ���������� ������ �޸𸮸� ����
	return;
}

/*���� ��� ���� �Լ�*/
void init_stack(StackType* s) {			// ���� �ʱ�ȭ			
	s->stack[0] = '\0';
	s->top = -1;
}

int is_empty_stack(StackType* s) {			// ������ ����������� Ȯ��	
	return (s->top == -1);
}

int is_full_stack(StackType* s) {			// ������ ��ȭ�������� Ȯ��
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {		// ���ÿ� ���� �ϳ��� ����
	if (is_full_stack(s)) {
		printf("������ ��ȭ�����Դϴ�.");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {					// ���� �ֻ�ܿ��� ���� �ϳ��� ����
	if (is_empty_stack(s)) {
		printf("������ ��������Դϴ�.");
		return -1;
	}
	else return s->stack[(s->top)--];
}


/*ť ��� ���� �Լ�*/
void init_queue(QueueType* q) {			// ť �ʱ�ȭ
	q->queue[0] = '\0';
	q->front = q->rear = 0;
}

int is_empty_queue(QueueType* q) {		// ť�� ����������� Ȯ��
	return (q->front == q->rear);
}

int is_full_queue(QueueType* q) {		// ť�� ��ȭ�������� Ȯ��
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

void enqueue(QueueType* q, element item) {		// ť�� ���� �ϳ� ����
	if (is_full_queue(q))
		printf("ť�� ��ȭ�����Դϴ�.");

	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
	}
}

element dequeue(QueueType* q) {			// ť�� �� �տ� �ִ� ���� �ϳ��� ����
	if (is_empty_queue(q)) {
		printf("ť�� ��������Դϴ�.");
		return;
	}
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->queue[q->front];
	}
}
