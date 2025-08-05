#include <stdio.h>
#define MAX 100

int stack[MAX], top = -1;

int isFull() {
    return top == MAX - 1;
}

int isEmpty() {
    return top == -1;
}

void push(int val) {
    if (isFull())
        printf("Stack Overflow\n");
    else
        stack[++top] = val;
}

void pop() {
    if (isEmpty())
        printf("Stack Underflow\n");
    else
        printf("Popped: %d\n", stack[top--]);
}

void peek() {
    if (isEmpty())
        printf("Stack is empty\n");
    else
        printf("Top element: %d\n", stack[top]);
}

void stackMenu() {
    int choice, val;
    do {
        printf("\n--- STACK MENU ---\n");
        printf("1. Push\n2. Pop\n3. isFull\n4. isEmpty\n5. Peek\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value to push: "); scanf("%d", &val); push(val); break;
            case 2: pop(); break;
            case 3: printf(isFull() ? "Stack is Full\n" : "Stack is Not Full\n"); break;
            case 4: printf(isEmpty() ? "Stack is Empty\n" : "Stack is Not Empty\n"); break;
            case 5: peek(); break;
            case 6: return;
            default: printf("Invalid choice\n");
        }
    } while (1);
}
