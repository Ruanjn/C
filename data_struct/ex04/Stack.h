typedef BiTree* SElemType;

typedef struct StackNode{
    SElemType data;
    struct StackNode* next;
}StackNode,* Linktop;

typedef struct LinkStack{
    Linktop top;
    SElemType count;
}LinkStack;

SElemType InitStack(LinkStack* stack){
    if(!stack)return 0;
    stack->top = NULL;
    stack->count = 0;
    return 1;
}
SElemType GetTop(LinkStack* stack,StackNode** stackNode){
    if(!stack)return 0;
    *stackNode =stack->top;
    return 1;
    
}
SElemType pop(LinkStack* stack,SElemType &e){
    if(!stack && stack->count)return 0;
    StackNode* node = stack->top;
    e = node->data;
    stack->top=node->next;
    free(node);
    stack->count--;
    return 1;
}
SElemType Push(LinkStack* stack,SElemType e){
    if(!stack)return 0;
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->next = stack->top;
    node->data = e;
    stack->top = node;
    stack->count++;
    return 1;
}
SElemType ClearStack(LinkStack* stack){
    if(!stack||stack->count)return 0;
    while(stack->count){
        StackNode* node = stack->top;
        stack->top=node->next;
        free(node);
        stack->count--;
    }
    return 1;
}
SElemType destroyStack(LinkStack* stack){
    ClearStack(stack);
    free(stack->top);
    return 1;
}
SElemType StackEmpty(LinkStack* stack){
    if(!stack)return 0;
    return stack->count == 0?1:0;
}
