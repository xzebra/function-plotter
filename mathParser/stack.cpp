#include "stack.h"

template <class a_type>
a_type Stack<a_type>::pop() {
    a_type output = head->value;
    head = head->next;
    return output;
}

template <class a_type>
void Stack<a_type>::push(a_type input) {
    bottom->next = Node(input, nullptr);
    bottom = bottom->next;
}

/*
A - B + C
-----
A   -
B   +
C
-----
AB-C+


A * B ^ C + D
-----
A   *
B   ^
C   +
D
-----
ABC^*D+

A * (B + C * D) + E
-----
A   *
B   (
C   +
D   *
E   )
    +
-----
ABCD*+*E+
*/