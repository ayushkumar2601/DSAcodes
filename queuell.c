#include <stdio.h>
#include <stdlib.h>

typedef struct Node{int data;struct Node*next;}Node;
Node*front=NULL,*rear=NULL;

void enqueue(int x){
    Node*n=malloc(sizeof(Node));n->data=x;n->next=NULL;
    if(!rear) front=rear=n; else rear->next=n,rear=n;
}
void dequeue(){
    if(!front) printf("Queue Empty\n");
    else{Node*t=front;front=front->next;if(!front)rear=NULL;free(t);}
}
void isEmpty(){printf(front?"Not Empty\n":"Empty\n");}
void display(){for(Node*t=front;t;t=t->next) printf("%d ",t->data);printf("\n");}

int main(){
    int ch,x;
    do{
        printf("1.Enqueue 2.Dequeue 3.isEmpty 4.Display 5.Exit\nChoice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1: scanf("%d",&x); enqueue(x); break;
            case 2: dequeue(); break;
            case 3: isEmpty(); break;
            case 4: display(); break;
            case 5: return 0;
        }
    }while(1);
}
