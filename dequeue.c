#include <stdio.h>
#define SIZE 5

int deque[SIZE], front = -1, rear = -1;

int dq_isFull() {
    return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
}

int dq_isEmpty() {
    return front == -1;
}

void enqueueFront(int val) {
    if (dq_isFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if (dq_isEmpty())
        front = rear = 0;
    else if (front == 0)
        front = SIZE - 1;
    else
        front--;
    deque[front] = val;
}

void enqueueRear(int val) {
    if (dq_isFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if (dq_isEmpty())
        front = rear = 0;
    else if (rear == SIZE - 1)
        rear = 0;
    else
        rear++;
    deque[rear] = val;
}

void dequeueFront() {
    if (dq_isEmpty()) {
        printf("Deque Underflow\n");
        return;
    }
    printf("Dequeued from Front: %d\n", deque[front]);
    if (front == rear)
        front = rear = -1;
    else if (front == SIZE - 1)
        front = 0;
    else
        front++;
}

void dequeueRear() {
    if (dq_isEmpty()) {
        printf("Deque Underflow\n");
        return;
    }
    printf("Dequeued from Rear: %d\n", deque[rear]);
    if (front == rear)
        front = rear = -1;
    else if (rear == 0)
        rear = SIZE - 1;
    else
        rear--;
}

void dequeMenu() {
    int choice, val;
    do {
        printf("\n--- DEQUE MENU ---\n");
        printf("1. Enqueue Rear\n2. Enqueue Front\n3. Dequeue Rear\n4. Dequeue Front\n5. isEmpty\n6. isFull\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &val); enqueueRear(val); break;
            case 2: printf("Enter value: "); scanf("%d", &val); enqueueFront(val); break;
            case 3: dequeueRear(); break;
            case 4: dequeueFront(); break;
            case 5: printf(dq_isEmpty() ? "Deque is Empty\n" : "Deque is Not Empty\n"); break;
            case 6: printf(dq_isFull() ? "Deque is Full\n" : "Deque is Not Full\n"); break;
            case 7: return;
            default: printf("Invalid choice\n");
        }
    } while (1);
}
