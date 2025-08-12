#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAX 100
char stack[MAX]; int top=-1;
void push(char c){stack[++top]=c;}
char pop(){return stack[top--];}
int prec(char c){return c=='+'||c=='-'?1:c=='*'||c=='/'?2:c=='^'?3:0;}

void infixToPostfix(char* infix,char* post){
    int k=0; char c;
    for(int i=0;(c=infix[i]);i++){
        if(isalnum(c)) post[k++]=c;
        else if(c=='(') push(c);
        else if(c==')'){while(top!=-1 && stack[top]!='(') post[k++]=pop(); pop();}
        else {while(top!=-1 && prec(stack[top])>=prec(c)) post[k++]=pop(); push(c);}
    }
    while(top!=-1) post[k++]=pop();
    post[k]=0;
}

int evalPostfix(char* post){
    int st[MAX],t=-1;
    for(int i=0;post[i];i++){
        if(isdigit(post[i])) st[++t]=post[i]-'0';
        else {int b=st[t--],a=st[t--];
            st[++t]= post[i]=='+'?a+b: post[i]=='-'?a-b: post[i]=='*'?a*b:
                     post[i]=='/'?a/b: (int)pow(a,b);
        }
    }
    return st[t];
}

int main(){
    char infix[MAX],post[MAX];
    printf("Enter infix: "); scanf("%s",infix);
    infixToPostfix(infix,post);
    printf("Postfix: %s\nValue: %d\n",post,evalPostfix(post));
}
