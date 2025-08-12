#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 100
char stack[MAX]; int top=-1;
void push(char c){stack[++top]=c;}
char pop(){return stack[top--];}
int prec(char c){return c=='+'||c=='-'?1:c=='*'||c=='/'?2:c=='^'?3:0;}

void reverse(char* s){
    int n=strlen(s);
    for(int i=0;i<n/2;i++){char t=s[i]; s[i]=s[n-i-1]; s[n-i-1]=t;}
}

void infixToPostfix(char* in,char* post){
    int k=0; char c;
    for(int i=0;(c=in[i]);i++){
        if(isalnum(c)) post[k++]=c;
        else if(c=='(') push(c);
        else if(c==')'){while(top!=-1&&stack[top]!='(') post[k++]=pop(); pop();}
        else{while(top!=-1 && prec(stack[top])>=prec(c)) post[k++]=pop(); push(c);}
    }
    while(top!=-1) post[k++]=pop();
    post[k]=0;
}

int evalPrefix(char* pre){
    int st[MAX],t=-1;
    for(int i=strlen(pre)-1;i>=0;i--){
        if(isdigit(pre[i])) st[++t]=pre[i]-'0';
        else {int a=st[t--],b=st[t--];
            st[++t]= pre[i]=='+'?a+b: pre[i]=='-'?a-b: pre[i]=='*'?a*b:
                     pre[i]=='/'?a/b: (int)pow(a,b);
        }
    }
    return st[t];
}

int main(){
    char infix[MAX],post[MAX],prefix[MAX];
    printf("Enter infix: "); scanf("%s",infix);
    reverse(infix);
    for(int i=0;i<strlen(infix);i++) if(infix[i]=='(') infix[i]=')'; else if(infix[i]==')') infix[i]='(';
    top=-1; infixToPostfix(infix,post);
    strcpy(prefix,post); reverse(prefix);
    printf("Prefix: %s\nValue: %d\n",prefix,evalPrefix(prefix));
}
