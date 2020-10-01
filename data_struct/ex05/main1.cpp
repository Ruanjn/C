#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<windows.h>
#include<queue>
using namespace std;
// 邻接表
#define MAX_VERTEX_NUM 20       //最大顶点数
boolean visted[MAX_VERTEX_NUM]; //访问判断数组
queue <int> q;
typedef int VertexType;         //顶点存储的数据类型

typedef struct ArcNode {        //边结点
    int adjvex;                 //该边所指向的顶点的位置
    struct ArcNode *nextarc;    //指向下一条边的指针
    int power;                  //边的权
}ArcNode,*acNode;

typedef struct VNode {          
    VertexType data;            //顶点信息
    ArcNode *firstarc;          //指向第一条衣服该顶点的边的指针
}VNode,AdjList[MAX_VERTEX_NUM]; //AdjList表示邻接表类型

typedef struct ALGraph{
    AdjList vertices;            //邻接表(包含了各个顶点)
    int vexnum,arcnum;          //图的当前顶点数和边数
    int kind;                   //图的种类
}ALGraph,* agNode;

int LocateVex(agNode G,int v){
    return v;
}
/**
 * 建立新的有向图
 * <p><br>
 * @return 建立好的有向图G
 */
agNode CreateGraph(){
    // 采用邻接表表示法，创建有向图G
    agNode G = (agNode)malloc(sizeof(ALGraph));
    scanf("%d %d",&G->vexnum,&G->arcnum);  //输入总顶点数，总边数
    for(int i=0;i<G->vexnum;++i){             //初始化各点，构造表头节点表
        G->vertices[i].data=i;            //初始化顶点信息为0
        G->vertices[i].firstarc=NULL;     //初始化表头结点的指针域为NULL
    }

    for(int k=0;k<G->arcnum;++k){
        int v1,v2;
        scanf("%d %d",&v1,&v2);           //输入一条边关联的两个顶点    
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        acNode an = (acNode)malloc(sizeof(ArcNode));
        an->adjvex = j;
        scanf("%d",&an->power);
        an->nextarc = G->vertices[i].firstarc;//继承邻接表顶点已有的弧结点
        G->vertices[i].firstarc=an;//an插入v1边表头部
    }
    return G;
}
void DFSofAL(agNode G,int v){           //深度遍历方法
    acNode p;
    p=G->vertices[v].firstarc;          //获取关于顶点v的后继
    visted[v] = true;
    printf("V%d ",G->vertices[v].data);
    while(p){
        if(!visted[p->adjvex])
            DFSofAL(G,p->adjvex);
        p = p->nextarc;                 //p指向的下一条边
    }
}
void DFSTraverseofAL(agNode G,int v){   //深度遍历函数，针对邻接表
    for(int i=0;i<G->vexnum;i++)
        visted[i]=false;                //初始化访问顶点情况
    printf("(Adjacency List)DFS From V%d: ",v);
    DFSofAL(G,v);                   //从输入的顶点开始访问
    for(int i=0;i<G->vexnum;i++){
        if(!visted[i])DFSofAL(G,i);     //访问不在前一通路的顶点
    }
    printf("\n");
}

void BFS(agNode G,int v){
    ArcNode *p;
    if(!visted[v]){
            printf("V%d ",v);
			visted[v] = true;
			q.push(v);
		}
		while(!q.empty()){
			v = q.front();
			q.pop();
			p = G->vertices[v].firstarc;
			while(p){
				if(!visted[p->adjvex]){
					visted[p->adjvex] = true;
                    printf("V%d ",p->adjvex);
					q.push(p->adjvex);
				}
				p = p->nextarc;
			}
		}
}
void BFSTraverse(agNode G,int v){             //广度遍历邻接表
	for(int i = 0; i < G->vexnum; i++)
		visted[i] = false;
    printf("(Adjacency List)BFS From V%d: ",v);
	BFS(G,v);
    for(int i = 0; i < G->vexnum; i++){
		BFS(G,i);
	}
    printf("\n");
}



#define MAXINT 3000

typedef int VerTexType;
typedef int ArcType;
typedef struct AMGraph{
    VerTexType vexs[MAX_VERTEX_NUM];
    ArcType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum,arcnum;    
}AMGraph,*amNode;
//使用邻接矩阵的方法
amNode CreateUDN(){         
    amNode G = (amNode)malloc(sizeof(AMGraph));
    int a,b;
    // fscanf(ip,"%d %d",&a,&b);

    scanf("%d %d",&G->vexnum,&G->arcnum);       //输入总顶点数，总边数
    for(int i=0;i<G->vexnum;i++){               //依次输入顶点的信息
        G->vexs[i]=i;
    }
    for(int i=0;i<G->vexnum;i++)
        for(int j=0;j<G->vexnum;j++)
            G->arcs[i][j] = MAXINT;             //初始化邻接矩阵，边的权值均设置为最大
    for(int k=0;k<G->arcnum;k++){
        int v1,v2;
        scanf("%d %d",&v1,&v2);                 //输入一条边的关联两个顶点    
        int i=v1;
        int j=v2;
        scanf("%d",&G->arcs[i][j]);             
    }
    return G;
}



void DFSofUDN(amNode G,int v){          //深度遍历方法
    visted[v] = true;
    printf("V%d ",v);
    for(int j=0;j<G->vexnum;j++){
        if(G->arcs[v][j]&&!visted[j])
            DFSofUDN(G,j);
    }
}
void DFSTraverseofUDN(amNode G,int v){  //深度遍历方法函数，针对邻接矩阵
    for(int i=0;i<G->vexnum;i++)
        visted[i]=false;                //初始化访问顶点情况
    printf("(Adjacency matrix)DFS From V%d: ",v);
    DFSofUDN(G,v);
    for(int i=0;i<G->vexnum;i++){       //从输入的顶点开始遍历
        if(!visted[i])DFSofUDN(G,i);    //遍历不在通路里的顶点
    }
    printf("\n");
}

void BFSofAL(amNode G,int v){
    if(!visted[v]){
            printf("V%d ",v);
            visted[v]=true;
            q.push(v);
        }
        while(!q.empty()){
            v=q.front();
            q.pop();
            for(int j=0;j<G->vexnum;j++){
                if(G->arcs[v][j]!=MAXINT&&!visted[j]){
                    visted[j] = true;
                    printf("V%d ",j);
                    q.push(j);
                }
            }
        }
}
void BFSTraverseofAL(amNode G,int v){                   //广度遍历邻接矩阵
    for(int i=0;i<G->vexnum;i++)
        visted[i] = false;
    printf("(Adjacency matrix)BFS From V%d: ",v);
    BFSofAL(G,v);
    for(int i=0;i<G->vexnum;i++){
        BFSofAL(G,i);
    }
    printf("\n");
}




int main(){
    int TraV=0;
    printf("Enter the Graph in Adjacency List\n");
    agNode G1=CreateGraph();
    printf("Enter the initial vertex of DFS traversal: ");
    scanf("%d",&TraV);
    DFSTraverseofAL(G1,TraV);
    printf("Enter the initial vertex of BFS traversal: ");
    scanf("%d",&TraV);
    BFSTraverse(G1,TraV);

    printf("Enter the Graph in Adjacency matrix\n");
    amNode G2=CreateUDN();
    printf("Enter the initial vertex of DFS traversal: ");
    scanf("%d",&TraV);
    DFSTraverseofUDN(G2,TraV);
    printf("Enter the initial vertex of BFS traversal: ");
    scanf("%d",&TraV);
    BFSTraverseofAL(G2,TraV);
    system("pause");
    return 0;
}

