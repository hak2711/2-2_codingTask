#include <stdio.h>          // 입출력 헤더 파일
#define MAX_VERTICES 100    // 최대 정점 수
#define MAX_STACK_SIZE 100  // 최대 스택 사이즈
#define MAX_QUEUE_SIZE 100  // 최대 큐 사이즈

typedef int element;

typedef struct {            // 그래프 노드 정의
	element vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct {            // 전체 그래프 정의
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

typedef struct {			// 스택 리스트 구현
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

typedef struct {			// 환형 큐 리스트 구현
	element queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
}QueueType;

void topsort_stack(GraphType* g);  // 스택을 이용한 위상정렬함수
void topsort_queue(GraphType* g);  // 큐를 이용한 위상정렬함수

void init_stack(StackType* s);	   // 스택 기능 구현 함수			
int is_empty_stack(StackType* s);
int is_full_stack(StackType* s);
void push(StackType* s, element item);
element pop(StackType* s);

void init_queue(QueueType* q);     // 큐 기능 구현 함수
int is_empty_queue(QueueType* q);
int is_full_queue(QueueType* q);
void enqueue(QueueType* q, element item);
element dequeue(QueueType* q);

int main() {
	int nodeNum = 0, edgeNum = 0;     // 정점개수와 에지개수 저장할 변수
	GraphType graph = { 0, NULL };  // 그래프를 선언하면서 초기화

	FILE* fp = fopen("dag5.txt", "r");  // 파일을 읽기 모드로 오픈

	if (fp == NULL) {  // 파일 내용이 비어있는 경우
		printf("파일이 비어있음.");
		return 1;
	}

	fscanf(fp, "%d%d", &nodeNum, &edgeNum);  //정점개수와 에지개수 읽어서 저장
	graph.n = nodeNum; // 그래프의 정점 개수 저장

	//인접리스트에 에지 연결 정보를 저장
	for (int i = 0; i < edgeNum; i++) {
		int fromNode, toNode;
		fscanf(fp, "%d%d", &fromNode, &toNode);

		GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));  // 연결된 노드 정보를 저장할 새로운 노드 생성
		GraphNode* temp = graph.adj_list[fromNode];

		if (temp == NULL) { // 첫 번째 노드가 비어있는 경우, 아직 저장된 에지 정보가 없는 경우
			graph.adj_list[fromNode] = (GraphNode*)malloc(sizeof(GraphNode)); // 첫 번째 노드를 생성
			temp = graph.adj_list[fromNode];
			temp->link = newNode; // 첫 번째 노드가 새로운 노드를 가리키도록 함
		}
		else {
			while ((temp->link) != NULL) { //링크가 빈 노드가 나올 때까지 시행
				temp = temp->link;
			}
			temp->link = newNode; // 링크가 빈 노드가 새로운 노드를 가리키도록 함
		}

		newNode->vertex = toNode; // 새로운 노드의 vertex에 연결된 노드 정보를 저장
		newNode->link = NULL; // 새로운 노드의 링크를 초기화

	}

	printf("스택 사용 위상정렬 결과 = ");
	topsort_stack(&graph); // 스택으로 위상정렬하는 함수
	printf("\n큐 사용 위상정렬 결과 = ");
	topsort_queue(&graph); // 큐로 위상정렬하는 함수

	fclose(fp); // 파일 닫기
}

void topsort_stack(GraphType* g) { // 스택으로 위상정렬하는 함수
	int i;
	StackType s;
	GraphNode* node;
	int flag = 0;

	int* in_degree = (int*)malloc(g->n * sizeof(int)); // 진입차수를 저장할 리스트

	for (i = 0; i < g->n; i++) // 진입차수를 0으로 초기화
		in_degree[i] = 0;

	for (i = 0; i < g->n; i++) { // 그래프 연결 상태를 확인한 후 최초 진입차수를 계산해 저장
		GraphNode* node = g->adj_list[i];
		while ((node != NULL) && (node->link != NULL)) { // 첫 번째 노드가 비어있지 않고, 첫 번째 노드가 가리키고 있는 노드가 있는 경우
			node = node->link;
			in_degree[node->vertex]++; // 가리켜지고 있는 노드의 진입차수 증가시킴
		}
	}

	init_stack(&s); // 스택 초기화
	for (i = 0; i < g->n; i++) { // 진입차수가 0인 노드들을 스택에 저장하고 그 개수만큼 flag를 증가시킴
		if (in_degree[i] == 0) {
			push(&s, i);
			flag++;
		}
	}

	while (!is_empty_stack(&s)) { // 스택이 비기 전까지 시행
		element w;
		w = pop(&s); // 스택에서 노드 하나를 pop
		printf("%d ", w); // 해당 노드를 출력
		node = g->adj_list[w];

		while ((node != NULL) && (node->link != NULL)) { // 해당 노드에 연결되어 있는 노드가 있는 경우 
			node = node->link;
			element u = node->vertex;
			in_degree[u]--; // w에 연결되어 있는 노드의 진입차수를 감소시킴
			if (in_degree[u] == 0) { // 감소 후 0이 된 노드는 스택에 저장하고 그 개수만큼 flag 증가시킴
				push(&s, u);
				flag++;
			}
		}
	}

	if (flag < g->n) // 스택에 모든 노드가 저장되지 않았는데 while문을 탈출했다면(스택이 비었다면) 위상정렬 불가
		printf("Impossible");



	free(in_degree); // 진입차수를 저장한 메모리를 해제
	return;
}


void topsort_queue(GraphType* g) { //큐로 위상정렬하는 함수
	int i;
	QueueType q;
	GraphNode* node;
	int flag = 0;

	int* in_degree = (int*)malloc(g->n * sizeof(int)); // 진입차수 저장할 리스트

	for (i = 0; i < g->n; i++) // 진입차수를 0으로 초기화
		in_degree[i] = 0;

	for (i = 0; i < g->n; i++) { // 그래프 연결 상태를 확인한 후 최초 진입차수를 계산해 저장
		GraphNode* node = g->adj_list[i];
		while ((node != NULL) && (node->link != NULL)) { // 첫 번째 노드가 비어있지 않고, 첫 번째 노드가 가리키고 있는 노드가 있는 경우
			node = node->link;
			in_degree[node->vertex]++; // 가리켜지고 있는 노드의 진입차수 증가시킴
		}
	}

	init_queue(&q); // 큐 초기화
	for (i = 0; i < g->n; i++) { // 진입차수가 0인 노드들을 큐에 저장하고 그 개수만큼 flag를 증가시킴
		if (in_degree[i] == 0) {
			enqueue(&q, i);
			flag++;
		}
	}

	while (!is_empty_queue(&q)) { // 큐가 비기 전까지 시행
		element w;
		w = dequeue(&q); // 큐에서 원소 하나를 꺼낸 후 w에 저장하고 출력
		printf("%d ", w);
		node = g->adj_list[w];

		while ((node != NULL) && (node->link != NULL)) { // 해당 노드에 연결되어 있는 노드가 있는 경우
			node = node->link;
			element u = node->vertex;
			in_degree[u]--; // w에 연결되어 있는 노드의 진입차수를 감소시킴
			if (in_degree[u] == 0) { // 감소 후 0이 된 노드는 큐에 저장하고 그 개수만큼 flag 증가시킴
				enqueue(&q, u);
				flag++;
			}
		}
	}

	if (flag < g->n) // 큐에 모든 노드가 저장되지 않았는데 while문을 탈출했다면(큐가 비었다면) 위상정렬 불가
		printf("Impossible");



	free(in_degree); // 진입차수를 저장한 메모리를 해제
	return;
}

/*스택 기능 구현 함수*/
void init_stack(StackType* s) {			// 스택 초기화			
	s->stack[0] = '\0';
	s->top = -1;
}

int is_empty_stack(StackType* s) {			// 스택이 공백상태인지 확인	
	return (s->top == -1);
}

int is_full_stack(StackType* s) {			// 스택이 포화상태인지 확인
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {		// 스택에 원소 하나를 삽입
	if (is_full_stack(s)) {
		printf("스택이 포화상태입니다.");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {					// 스택 최상단에서 원소 하나를 추출
	if (is_empty_stack(s)) {
		printf("스택이 공백상태입니다.");
		return -1;
	}
	else return s->stack[(s->top)--];
}


/*큐 기능 구현 함수*/
void init_queue(QueueType* q) {			// 큐 초기화
	q->queue[0] = '\0';
	q->front = q->rear = 0;
}

int is_empty_queue(QueueType* q) {		// 큐가 공백상태인지 확인
	return (q->front == q->rear);
}

int is_full_queue(QueueType* q) {		// 큐가 포화상태인지 확인
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

void enqueue(QueueType* q, element item) {		// 큐에 원소 하나 삽입
	if (is_full_queue(q))
		printf("큐가 포화상태입니다.");

	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
	}
}

element dequeue(QueueType* q) {			// 큐의 맨 앞에 있는 원소 하나를 추출
	if (is_empty_queue(q)) {
		printf("큐가 공백상태입니다.");
		return;
	}
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->queue[q->front];
	}
}
