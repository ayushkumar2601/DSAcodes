#include <stdio.h>
#include <stdlib.h>

typedef struct Node{int data;struct Node*next;}Node;
Node*top=NULL;

void push(int x){Node*n=malloc(sizeof(Node));n->data=x;n->next=top;top=n;}
void pop(){if(top){Node*t=top;top=top->next;free(t);}else printf("Stack Empty\n");}
void peek(){if(top) printf("%d\n",top->data);else printf("Stack Empty\n");}
void isEmpty(){printf(top?"Not Empty\n":"Empty\n");}
void display(){for(Node*t=top;t;t=t->next) printf("%d ",t->data);printf("\n");}

int main(){
    int ch,x;
    do{
        printf("1.Push 2.Pop 3.Peek 4.isEmpty 5.Display 6.Exit\nChoice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1: scanf("%d",&x); push(x); break;
            case 2: pop(); break;
            case 3: peek(); break;
            case 4: isEmpty(); break;
            case 5: display(); break;
            case 6: return 0;
        }
    }while(1);
}
