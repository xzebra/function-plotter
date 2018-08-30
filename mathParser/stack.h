#ifndef STACK_H
#define STACK_H

template <class a_type> struct Node {
    a_type value;
    Node *next;
    Node(a_type v, Node *n) : value(v), next(n) {};
};

template <class a_type> class Stack {
    public:
        Stack() = default;
        ~Stack() = default;
        a_type pop();
        void push(a_type input);
    private:
        Node<a_type> *head, *bottom;
};

#endif