#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#define MAX_QUEUE_SIZE 10

typedef struct {
	int n;			// number of nodes
	int *visited;	// visit check array
	int **adj_mat;	// adjaceny magrix
} GraphType;

typedef struct {
	int top;
	int st_size;		// stack size
	int *stack;		// stack array
} StackType;

typedef struct{
	int queue[MAX_QUEUE_SIZE];
	int front,rear;
} QueueType;

void makeGraph(GraphType *gr, int no)
{
	gr->n = no;
	gr->visited = (int *)malloc(sizeof(int) * (no + 1));
	gr->adj_mat = (int **)malloc((sizeof(int *) * (no+1)));
	for (int i = 1; i <= no; i++) {
		gr->adj_mat[i] = (int *)malloc(sizeof(int) * (no+1));
		gr->visited[i] = 0;
	}
	for (int i = 1; i <= no; i++) {
		gr->visited[i] = 0;
		for (int j = 1; j <= no; j++)
			gr->adj_mat[i][j] = 0;
	}
}

void DFS(GraphType *gr, int v)
{
	int w;
	gr->visited[v] = 1;		
	//printf("%d ", v);	
	for (w = 1; w <= gr->n; w++) 	
		if (gr->adj_mat[v][w] && !gr->visited[w])
			DFS(gr, w);	
}

void st_push(StackType *st, int n)
{
	if (st->top == st->st_size - 1)
		return;		// full
	st->stack[++(st->top)] = n;
}

int st_pop(StackType *st)
{
	if (st->top == - 1)
		return 0;		// empty
	return st->stack[(st->top)--];
}

void DFS_stack(GraphType *gr, int v)
{
	StackType st;
	int w;

	st.top = -1;
	st.st_size = gr->n + 1;
	st.stack = (int *)malloc(sizeof(int) * st.st_size);
	st_push(&st, v);
	gr->visited[v] = 1;		
	while (st.top != -1) {
		v = st_pop(&st);
		printf("%d ", v);	
		//		for (w = 1; w <= gr->n; w++) 	
		for (w = gr->n; w >= 1; w--) 		
			if (gr->adj_mat[v][w] && !gr->visited[w]) {
				st_push(&st, w);
				gr->visited[w] = 1;		
			}
	}
}

void addGraphEdge(GraphType *gr, int a, int b)
{
	gr->adj_mat[a][b] = 1;
}

void queue_init(QueueType *q){
    q->front=q->rear=0;
}

int is_empty(QueueType *q){
    return (q->front==q->rear);
}

int is_full(QueueType *q){
    return ((q->rear+1)%MAX_QUEUE_SIZE==q->front);
}

void enqueue(QueueType *q, int item){
    if(is_full(q))
       printf("overflow");
    q->rear=(q->rear+1)%MAX_QUEUE_SIZE;
    q->queue[q->rear]=item;
}

int dequeue(QueueType *q){
    if(is_empty(q))
        printf("underflow");
    q->front=(q->front+1)%MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

void bfs_mat(GraphType* gr, int v){
    int w;
    QueueType q;

    queue_init(&q);
    gr->visited[v] = 1;
    printf("%d ",v);
    enqueue(&q,v);
    while(!is_empty(&q)){
        v=dequeue(&q);
        for (w = 1; w < gr->n + 1; w++)
            if(gr->adj_mat[v][w] && !gr->visited[w]){
                gr->visited[w] = 1;
                printf("%d ",w);
                enqueue(&q,w);
            }
    }
}

int main()
{
	GraphType gr1;
	GraphType gr2;
	int no, v;

	printf("탐색할 방법을 선택하세요 : 1.DFS  2.BFS  3.둘다 실행 >> ");
	scanf("%d", &no);
	if (no == 1){
		no = 7;
		makeGraph(&gr1, no);
		addGraphEdge(&gr1, 1, 2);
		addGraphEdge(&gr1, 1, 7);
		addGraphEdge(&gr1, 2, 3);
		addGraphEdge(&gr1, 2, 6);
		addGraphEdge(&gr1, 3, 1);
		addGraphEdge(&gr1, 3, 4);
		addGraphEdge(&gr1, 4, 5);

		printf("Type the number of start node in Graph1 for DFS(1~%d): ", no);
		scanf("%d", &v);
		DFS(&gr1, v);
		for (int i = 0; i <= no; i++)
			gr1.visited[i] = 0;
		printf("DFS : ");
		DFS_stack(&gr1, v);
	}
	else if (no == 2){
		no = 7;
	   	makeGraph(&gr2, no);
	   	
		addGraphEdge(&gr2, 1, 2);
		addGraphEdge(&gr2, 1, 7);
		addGraphEdge(&gr2, 2, 3);
		addGraphEdge(&gr2, 2, 6);
		addGraphEdge(&gr2, 3, 1);
		addGraphEdge(&gr2, 3, 4);
		addGraphEdge(&gr2, 4, 5);

		printf("Type the number of start node in Graph1 for DFS(1~%d): ", no);
		scanf("%d", &v);
		printf("BFS : ");
	    bfs_mat(&gr2, v);
	    printf("\n");
	}
	else if (no == 3)
	{
		no = 7;
		makeGraph(&gr1, no);
		addGraphEdge(&gr1, 1, 2);
		addGraphEdge(&gr1, 1, 7);
		addGraphEdge(&gr1, 2, 3);
		addGraphEdge(&gr1, 2, 6);
		addGraphEdge(&gr1, 3, 1);
		addGraphEdge(&gr1, 3, 4);
		addGraphEdge(&gr1, 4, 5);

		printf("Type the number of start node in Graph1 for DFS(1~%d): ", no);
		scanf("%d", &v);
		DFS(&gr1, v);
		for (int i = 0; i <= no; i++)
			gr1.visited[i] = 0;
		printf("DFS : ");
		DFS_stack(&gr1, v);
		printf("\n");

		no = 7;
	   	makeGraph(&gr2, no);
	   	
		addGraphEdge(&gr2, 1, 2);
		addGraphEdge(&gr2, 1, 7);
		addGraphEdge(&gr2, 2, 3);
		addGraphEdge(&gr2, 2, 6);
		addGraphEdge(&gr2, 3, 1);
		addGraphEdge(&gr2, 3, 4);
		addGraphEdge(&gr2, 4, 5);

		printf("BFS : ");
	    bfs_mat(&gr2, v);
	    printf("\n");

	}
}
