#ifndef STACK_H
#define STACK_H

struct Node {
    char value;
    Node *next;
    Node(char v, Node *n) : value(v), next(n) {};
};

class Stack {
    public:
        Stack() = default;
        ~Stack();
        void clear();
        char pop();
        void push(char input);
        bool empty();
        char getHead();
    private:
        Node *head, *bottom;
        int size = 0;
};

#endif