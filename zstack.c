/**
 * file: zstack.c
 * author: fyzbc
 * date: 2017年5月2日
 *
 */

#include "zstack.h"

// 初始化栈
Stack* init(int maxsize){
    Stack* s=(Stack*)malloc(sizeof(Stack));
    if(s==NULL)return false;
    s->data = (DataType*)malloc(maxsize*sizeof(DataType));
    s->maxsize = maxsize;
    s->top=-1;
    return s;
}


// 判断栈是否为空
bool Empty(Stack* s)
{
    if(s->top==-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 判断栈是否已满了
bool full(Stack* s)
{
    if(s->top==s->maxsize-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 入栈
void Push(Stack* s,DataType element)
{
    if(!full(s))
    {
        s->data[++s->top]=element;
    }
    else
    {
        printf("栈满\n");
    }
}

// 出栈
DataType Pop(Stack* s)
{
    if(!Empty(s))
    {
        DataType d = s->data[s->top];
        s->top--;
        return d;
    }
    else
    {
        printf("栈空\n");
        return NULL;
    }
}

// 专门为数据栈开启的pop后门
DataType Hook(Stack* s,int order){
    if(order<0||order>s->maxsize-1){
        printf("[runtime.readValueFromDataStack]please check your data!");
        exit(-1);
    }
    s->top = order;
    //printf("s->top:%d\n",s->top-1);
    return s->data[s->top];
}

// 专门为数据栈开启的push后门
void Stick(Stack* s, int order, DataType element){
    if(order<0||order>s->maxsize-1){
        printf("[runtime.readValueFromDataStack]please check your data!");
        exit(-1);
    }
    s->top = order;
    s->data[s->top] = element;
    //printf("s->top:%d\n",s->top);
}

// 取栈顶元素
DataType Top(Stack* s)
{
    if(!Empty(s))
    {
        return s->data[s->top];
    }
    else
    {
        printf("栈空\n");
        return NULL;
    }
}

// 销毁栈
void Destroy(Stack* s)
{
    if(s!=NULL){
        if(s->data!=NULL){
            free(s->data);
            s->data=NULL;
        }
        s->top=-1;
    }
}


void travelStack(Stack* stack){
    while(!Empty(stack))
    {
        DataType dt = Pop(stack);
        switch(dt->type)
        {
        case TYPE_OP:
            showOpData(stack,dt);
            break;
        case TYPE_TP:
            showTpData(stack,dt);
            break;
        case TYPE_VL:
            showVlData(stack,dt);
            break;
        }
    }
}




///*----------下面运行的都是测试函数--------------*/
//void testCharpStack(){
//    char* buf=NULL;
//    Stack* s = init(10);
//	int len = readFile("data.txt",&buf);
//    int i=0;
//    char* p1 = "12342";
//    char* p2 = "234234";
//
//
//    printf("%s\n",buf);
//    Push(s,buf);
//    Push(s,buf);
//    Push(s,p2);
//    Push(s,p2);
//    Push(s,p2);
//    Push(s,p2);
//    Push(s,p2);
//    Push(s,p2);
//
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//    printf("%s\n",Pop(s));
//
//    int is = MOV;
//    printf("%d",is);
//
//
//    return 0;
//
//}
//
//
//void* testFun(void* obj,const void* dt){
//    DataElem* data=(DataElem*)dt;
//    printf("%s\n",data->msg);
//    printf("%d\n",data->value);
//    printf("%d\n",data->type);
//}
//
//void testDataType(){
//
//    Stack* s = init(STACK_LENGTH);
//    DataType dt = (DataType)malloc(sizeof(DataElem));
//    dt->msg="1234";
//    dt->value = 1;
//    dt->type = 1;
//    dt->readFun = testFun;  //赋值函数
//    Push(s,dt);
//    dt = Pop(s);
//    dt->readFun(NULL,dt);
//    Destroy(s);
//
//}



//
//int main(){
//
//    testDataType();
//    //testCharpStack();
//    return 0;
//}
