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

void DepthFirstSearch(graphType* g) {   //DFS 탐색 함수
    
}

void BreathFirstSearch(graphType* g) {  //BFS 탐색 함수
    
}
