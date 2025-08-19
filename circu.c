#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;
Node *head = NULL;

int len() {
    if (!head) return 0;
    int c = 1; Node *t = head;
    while (t->next != head) { c++; t = t->next; }
    return c;
}

void insert(int pos, int val) {
    Node *n = malloc(sizeof(Node)); n->data = val;
    if (!head) { head = n; head->next = head; return; }
    if (pos <= 1) { n->next = head; Node *t = head; while (t->next != head) t = t->next; t->next = n; head = n; return; }
    Node *t = head; for (int i=1;i<pos-1 && t->next!=head;i++) t = t->next;
    n->next = t->next; t->next = n;
}

void delete(int pos) {
    if (!head) return;
    if (pos <= 1) {
        if (head->next == head) { free(head); head = NULL; return; }
        Node *t = head; while (t->next != head) t = t->next;
        Node *d = head; head = head->next; t->next = head; free(d); return;
    }
    Node *t = head; for (int i=1;i<pos-1 && t->next->next!=head;i++) t = t->next;
    Node *d = t->next; t->next = d->next; free(d);
}

void display() {
    if (!head) { printf("Empty\n"); return; }
    Node *t = head; do { printf("%d ",t->data); t = t->next; } while(t!=head); printf("\n");
}

void search(int val) {
    if (!head) { printf("Not found\n"); return; }
    Node *t = head; int pos=1; do {
        if (t->data==val){ printf("Found at %d\n",pos); return; }
        t=t->next; pos++;
    } while(t!=head); printf("Not found\n");
}

void reverse() {
    if (!head || head->next==head) return;
    Node *prev=head, *cur=head->next, *next;
    while(cur!=head){ next=cur->next; cur->next=prev; prev=cur; cur=next; }
    cur=head->next; head->next=prev; head=prev;
}

int main() {
    int ch,x,pos;
    while(1){
        printf("\n1.Insert 2.Delete 3.Display 4.Search 5.Reverse 6.Exit\nChoice: ");
        scanf("%d",&ch);
        if(ch==6) break;
        if(ch==1){ printf("Val Pos: "); scanf("%d%d",&x,&pos); insert(pos,x); }
        else if(ch==2){ printf("Pos: "); scanf("%d",&pos); delete(pos); }
        else if(ch==3) display();
        else if(ch==4){ printf("Val: "); scanf("%d",&x); search(x); }
        else if(ch==5) reverse();
    }
}
