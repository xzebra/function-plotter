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
        ~Stack() { this->clear(); }

        void clear() {
            Node<a_type> *ptr = head;
            while(ptr != nullptr) {
                Node<a_type> *temp = ptr->next;
                delete[] ptr;
                ptr = temp;
            }
            size = 0;
        }

        a_type pop() {
            a_type output = head->value;
            head = head->next;
            size--;
            return output;
        }

        void push(a_type input) {
            if(head == nullptr) {
                head = new Node<a_type>(input, nullptr);
                bottom = head;
            } else {
                head = new Node<a_type>(input, head);
            }  
            size++;
        }

        bool empty() {
            return this->size == 0;
        }

        a_type getHead() {
            return head->value;
        }
    private:
        Node<a_type> *head, *bottom;
        int size = 0;
};


#endif