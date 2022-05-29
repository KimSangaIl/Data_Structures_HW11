#include <stdio.h>
#include <stdlib.h>
#define VERTEX 10   //최대 정점 개수를 10으로 지정

typedef struct graphNode {
    int vertex;                 //정점
    struct graphNode* link;     //다음 인접 정점을 연결하는 링크
} graphNode;

typedef struct graphType {
    int n;                          //그래프의 정점 수
    graphNode* adjList_H[VERTEX];   //그래프 정점에 대한 헤드 노드 배열
    int visited[VERTEX];            //정점 방문 표시 배열
} graphType;

typedef struct stackNode {  //스택 노드
    int data;
    struct stackNode* link;
} stackNode;

stackNode* top; //스택 탑 포인터 선언

int isEmptyS();
void push(int item);
int pop();

void InitializeGraph(graphType* g);
void InsertVertex(graphType* g, int v);
void InsertEdge(graphType* g, int u, int v);
void PrintGraph(graphType* g);
void DepthFirstSearch(graphType* g);
void BreathFirstSearch(graphType* g);

int main() {

    printf("[----- [Kim Sangil] [2019038041] -----]");

    char command;
    int v, u;
    graphType *g = (graphType*)malloc(sizeof(graphType));

   
	do {
		printf("\n\n");
		printf("---------------------------------------------------------\n");
		printf("                       Graph Search                      \n");
		printf("---------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                \n");
		printf(" Insert Vertex        = i      Insert Edge           = e \n");
		printf(" Depth First Search   = d      Breath First Search   = b \n");
		printf(" Print Graph          = p      Quit                  = q \n");
		printf("---------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			InitializeGraph(g);
			break;
		case 'q': case 'Q':
			free(g);
			break;

		case 'i': case 'I':
            printf("Input number of vertex: ");
            scanf("%d", &v);                    	//정점 개수를 입력 받음
			for (int i = 0; i < v; i++) {	//입력 받은 수 만큼 반복
                InsertVertex(g, i);             	//그래프에 정점 추가
            }
			break;
		case 'e': case 'E':
            printf("Input vertex u and v: ");
            scanf("%d %d", &u, &v);             //삽입할 간선을 입력 받음
			InsertEdge(g, u, v);	//입력 받은 간선 추가
			break;

		case 'd': case 'D':
			DepthFirstSearch(g);
			break;
		case 'b': case 'B':
			BreathFirstSearch(g);
			break;

		case 'p': case 'P':
			PrintGraph(g);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void InitializeGraph(graphType* g) {    //그래프 초기화 함수
    g->n = 0;                           //정점 개수를 0으로 초기화
    for (int i = 0; i < VERTEX; i++) {  //최대 정점 개수만큼 반복
        g->visited[i] = 0;              //방문 표시 배열을 0으로 초기화
        g->adjList_H[i] = NULL;         //헤드 노드 배열을 NULL로 초기화
    }
}

void InsertVertex(graphType* g, int v) {    //정점 삽입 함수
    if (((g->n) + 1) > VERTEX) {            //정점의 개수가 최대 개수보다 많은 경우
        printf("over\n");                   //오류 메시지 출력
        return;                             //비정상 함수 종료
    }
    g->n++;                                 //정점 개수 1 증가
}

void InsertEdge(graphType* g, int u, int v) {       //간선 (u, v) 삽입 함수
    if ((u >= g->n) || (v >= g->n)) {               //정점 u와 v가 그래프에 존재하지 않는 경우
        printf("vertex does not exit on graph\n");  //오류 메시지 출력
        return;                                     //비정상 함수 종료
    }
    graphNode* node = (graphNode*)malloc(sizeof(graphNode));    //리스트에 추가할 노드의 메모리를 동적으로 할당
    node->vertex = v;               //추가 노드의 정점을 v로 초기화
    node->link = g->adjList_H[u];   //추가 노드를 정점 u의 인접 리스트에 연결
    g->adjList_H[u] = node;         //정점 u의 인접 리스트를 추가 노드로 초기화
}

void PrintGraph(graphType* g) {             //그래프의 인접 리스트 출력 함수
    graphNode* temp;                        //임시 노드 선언
    for (int i = 0; i < g->n; i++) {        //그래프의 정점 개수 만큼 반복
        printf("\nvertex #%d list: ", i);
        temp = g->adjList_H[i];             //임시 노드를 정점 i의 인접 리스트로 초기화
        while (temp) {                      //인접한 정점이 없을때 까지 반복
            printf(" -> %d", temp->vertex);
            temp = temp->link;              //임시 노드를 다음 노드로 이동하면서 출력
        }
    }
}

int isEmptyS() {                //스택의 공백 여부 확인 함수
    if (top == NULL) return 1;  //스택 탑이 공백인 경우 스택이 공백
    else return 0;              //스택 탑이 공백이 아닌 경우 스택이 공백이 아님
}

void push(int item) {   //스택에 원소를 추가하는 함수
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));    //노드 선언 및 동적으로 메모리 할당
    temp->data = item;  //추가할 노드의 데이터 값을 item으로 초기화
    temp->link = top;   //추가할 노드를 스택 탑위에 연결
    top = temp;         //스택 탑을 추가한 노드로 초기화
}

int pop() {     //스택에 원소를 삭제하는 함수
    int item;   //정수 값을 저장할 변수 선언
    stackNode* temp = top;  //노드 선언 및 스택 탑으로 초기화
    if (isEmptyS()) {       //스택이 공백인 경우
        printf("\nStack is empty!\n");	//공백이라는 메시지 출력
        return 0;                       //함수 종료
    }

    else {  //스택이 공백이 아닌 경우
        item = temp->data;  //item을 삭제할 노드의 데이터 값으로 초기화
        top = temp->link;   //스택 탑을 삭제할 노드 아래 노드로 초기화
        free(temp);         //메모리를 반환하여 노드 삭제
        return item;        //삭제한 노드의 데이터 값을 반환
    }
}

void DepthFirstSearch(graphType* g) {   //DFS 탐색 함수
    int v = 0;          //탐색을 시작할 정점 선언 및 0으로 초기화
    graphNode* temp;    //임시 노드 선언
    top = NULL;         //스택 탑을 NULL로 초기화
    push(v);            //시작 정점을 스택에 push
    g->visited[v] = 1;  //정점 v를 방문했으므로 값을 1로 초기화
    printf(" %d", v);   //정점 v 출력

    while (!isEmptyS()) {                       //스택이 공백이 될때까지 반복
        v = pop();                              //정점 v를 스택에서 pop한 값으로 초기화
        temp = g->adjList_H[v];                 //임시 노드를 정점 v의 인접 리스트로 초기화
        while (temp) {                          //인접한 정점이 없을때 까지 반복
            if (!g->visited[temp->vertex]) {    //현재 정점을 방문하지 않은 경우
                if (isEmptyS()) push(v);        //정점 v로 다시 돌아오기 위해서 정점 v를 스택에 push
                push(temp->vertex);             //현재 정점을 스택에 push
                g->visited[temp->vertex] = 1;   //현재 정점을 방문했으므로 값을 1로 초기화
                printf(" %d", temp->vertex);    //현재 정점을 출력
                v = temp->vertex;               //정점 v를 현재 정점으로 초기화
                temp = g->adjList_H[v];         //임시 노드를 정점 v의 인접 리스트로 초기화
            }
            else temp = temp->link;             //현재 정점을 방문한적이 있는 경우 다음 노드로 이동
        }
    }
    for (int i = 0; i < g->n; i++) {
        g->visited[i] = 0;  //그래프의 모든 방문 확인 값을 0으로 초기화
    }
}

void BreathFirstSearch(graphType* g) {  //BFS 탐색 함수
    
}
