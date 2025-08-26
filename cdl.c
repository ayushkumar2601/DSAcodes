#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data; struct Node *prev,*next;
}Node;
Node *head=NULL;

Node* newNode(int x){
    Node*n=malloc(sizeof(Node)); n->data=x;
    n->prev=n->next=n; return n;
}

void insert(int pos,int x){
    Node*n=newNode(x);
    if(!head){ head=n; return;}
    Node*t=head; int i=1;
    if(pos==1){ n->next=head; n->prev=head->prev;
        head->prev->next=n; head->prev=n; head=n; return;}
    while(i++<pos-1 && t->next!=head) t=t->next;
    n->next=t->next; n->prev=t;
    t->next->prev=n; t->next=n;
}

void delete(int pos){
    if(!head) return; Node*t=head; int i=1;
    if(pos==1){ if(head->next==head){ free(head); head=NULL; return;}
        head->prev->next=head->next; head->next->prev=head->prev;
        t=head; head=head->next; free(t); return;}
    while(i++<pos && t->next!=head) t=t->next;
    if(t==head) return;
    t->prev->next=t->next; t->next->prev=t->prev; free(t);
}

void display(){
    if(!head) return; Node*t=head;
    do{ printf("%d ",t->data); t=t->next;}while(t!=head);
    printf("\n");
}

void search(int x){
    if(!head) return; int i=1; Node*t=head;
    do{ if(t->data==x){ printf("Found at %d\n",i); return;}
        t=t->next; i++; }while(t!=head);
    printf("Not found\n");
}

void reverse(){
    if(!head) return; Node*t=head,*p=NULL;
    do{ p=t->prev; t->prev=t->next; t->next=p; t=t->prev;}while(t!=head);
    head=head->next;
}

int main(){
    int c,x,p;
    for(;;){
        scanf("%d",&c); if(c==6) break;
        if(c==1){ scanf("%d%d",&x,&p); insert(p,x);}
        else if(c==2){ scanf("%d",&p); delete(p);}
        else if(c==3) display();
        else if(c==4){ scanf("%d",&x); search(x);}
        else if(c==5) reverse();
    }
}
