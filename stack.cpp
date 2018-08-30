#include "stack.h"

char Stack::pop() {
    char output = head->value;
    head = head->next;
    size--;
    return output;
}

void Stack::push(const char input) {
    if(head == nullptr) {
        head = new Node(input, nullptr);
        bottom = head;
    } else {
        head = new Node(input, head);
    }  
    size++;
}

void Stack::clear() {
    Node *ptr = head;
    while(ptr != nullptr) {
        Node *temp = ptr->next;
        delete[] ptr;
        ptr = temp;
    }
    size = 0;
}

Stack::~Stack() {
    this->clear();
}

bool Stack::empty() {
    return size == 0;
}

char Stack::getHead() {
    return head->value;
}