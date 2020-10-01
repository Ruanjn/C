typedef char TElemType;

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,* BiTree;



void InitBiTree(BiTree &T){
    T=NULL;
}

void CreatBiTree(BiTree &T){
    char c;
    c=getchar();
    if(c=='#'||c==' ') T=NULL;
    else{
        T=new BiTNode;  T->data=c;
        CreatBiTree(T->lchild);
        CreatBiTree(T->rchild);
    }
};
 /**function：PreOrderTraverse
  * 前序遍历二叉树
  * 参数：BiTree类型 二叉树；
  */
void PreOrderTraverse(BiTree &T){
    if(T){
        printf("%c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
/**
 *function：InOrderTraverse
 * 后序遍历二叉树
 * 参数：BiTree类型 二叉树；
 */
void InOrderTraverse(BiTree &T){
    if(T){
        InOrderTraverse(T->lchild);
        printf("%c",T->data);
        InOrderTraverse(T->rchild);
    }
}
/**
 * function：PostOrderTraverse
 * 后序遍历二叉树
 * 参数：BITree 二叉树；
 */
void PostOrderTraverse(BiTree &T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
}
/**
 * 层次遍历二叉树
 * 参数
 */
void LevelOrderTraverse(){
    
}

void iterInorder(){

}

void leaf(){

}

void height(){

}