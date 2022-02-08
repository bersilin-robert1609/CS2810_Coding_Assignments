#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Node
{ // Node Class for Linked List elements
public:
    T value;
    Node();
    Node *prev;
    Node *next;
};

template <typename T>
Node<T>::Node()
{ // Node Class Constructor
    this->prev = NULL;
    this->next = NULL;
}

template <typename T>
class Doubly_linked_list
{ // templated Doubly Linked List class
public:
    Doubly_linked_list(); // Doubly_linked_list class constructor
    void push_front(T);   // Function to add element at the front
    void push_end(T);     // Function to add element at the back
    T pop_front();        // Function to delete element at the front
    T pop_end();          // Function to delete element at the back
    int size();           // Function to return size of the linked list

private: // Private members head, tail and count of the elements
    Node<T> *head;
    Node<T> *tail;
    int elementsCount;
};

template <typename T>
int Doubly_linked_list<T>::size()
{ // Function to return size of the linked list
    return elementsCount;
}

template <typename T>
Doubly_linked_list<T>::Doubly_linked_list()
{ // Doubly_linked_list class constructor
    elementsCount = 0;
    this->head = NULL;
    this->tail = NULL;
}

template <typename T>
void Doubly_linked_list<T>::push_front(T val)
{ // Function to add element at the front

    elementsCount++;

    Node<T> *newptr = new Node<T>();
    newptr->value = val;

    if (head == NULL)
    { // Incase empty
        head = newptr;
        tail = newptr;
        return;
    }

    head->prev = newptr; // general case
    newptr->next = head;
    head = newptr;
    return;
}

template <typename T>
void Doubly_linked_list<T>::push_end(T val)
{ // Function to add element at the back

    elementsCount++;

    Node<T> *newptr = new Node<T>();
    newptr->value = val;

    if (head == NULL)
    { // Incase empty
        head = newptr;
        tail = newptr;
        return;
    }

    tail->next = newptr; // general case
    newptr->prev = tail;
    tail = newptr;
    ;
    return;
}

template <typename T>
T Doubly_linked_list<T>::pop_front()
{ // Function to delete element at the front

    elementsCount--;

    Node<T> *newptr = head;
    T temp = newptr->value;

    head = head->next;
    if (head == NULL)
    { // Incase it becomes empty
        tail = NULL;
        // free newptr;
        return temp;
    }
    head->prev = NULL; // general case

    newptr->next = NULL;
    // free newptr;

    return temp;
}

template <typename T>
T Doubly_linked_list<T>::pop_end()
{ // Function to delete element at the back

    elementsCount--;

    Node<T> *newptr = tail;
    T temp = newptr->value;

    tail = tail->prev;
    if (tail == NULL)
    { // Incase it becomes empty
        head = NULL;
        // free newptr;
        return temp;
    }
    tail->next = NULL; // general case

    newptr->prev = NULL;
    // free newptr;

    return temp;
}

template <typename T>
class Template_stack
{ // Template_stack class
public:
    Template_stack(); // Template_stack constuctor
    void push(T);     // Function to push an element into the stack
    T pop();          // Function to delete an element and return it from the stack from the top
    T top();          // Function to return the top element from the stack
    int size();       // Function to return the size of the stack
    bool compare(T);  // Returns true if (arg > stackTop)

private:
    Doubly_linked_list<T> *dll; // just a doubly_linked_list
};

template <typename T>
Template_stack<T>::Template_stack()
{ // Template_stack constuctor

    dll = new Doubly_linked_list<T>();
}

template <typename T>
void Template_stack<T>::push(T val)
{ // Function to push an element into the stack

    dll->push_front(val);
}

template <typename T>
T Template_stack<T>::pop()
{ // Function to delete an element and return it from the stack from the top

    T temp = dll->pop_front();

    return temp;
}

template <typename T>
T Template_stack<T>::top()
{ // Function to return the top element from the stack

    T temp = dll->pop_front();
    dll->push_front(temp);

    return temp;
}

template <typename T>
int Template_stack<T>::size()
{ // Function to return the size of the stack

    return dll->size();
}

template <typename T>
bool Template_stack<T>::compare(T val)
{ // Returns true if (arg > stackTop)

    T temp = top();

    if (val > temp)
        return true;
    else
        return false;
}

template <typename T>
void encrypt_stack_input(Template_stack<T> *&S, int n)
{ // Encryption function as stated

    while (n--)
    {

        T temp;
        cin >> temp;

        if (S->size() == 0)
        {

            S->push(temp);
        }
        else if (temp > S->top())
        {

            S->push(temp);
        }
        else if (temp <= S->top())
        {

            while (S->size() > 0)
            {

                if (temp <= S->top())
                {

                    T pop_temp = S->pop();
                    cout << pop_temp;
                }
                else
                    break;
            }

            S->push(temp);
        }
    }

    while (S->size() > 0)
        cout << S->pop();
    cout << endl;

    return;
}

int main()
{ // The main function

    int n;
    cin >> n;

    char opcode;
    cin >> opcode;

    if (opcode == 'I')
    { // the integer entries

        Template_stack<int> *S = new Template_stack<int>();
        encrypt_stack_input<int>(S, n);
    }
    else if (opcode == 'C')
    { // the character entries

        Template_stack<char> *S = new Template_stack<char>();
        encrypt_stack_input<char>(S, n);
    }
    else if (opcode == 'F')
    { // the float entries

        Template_stack<float> *S = new Template_stack<float>();
        encrypt_stack_input<float>(S, n);
    }

    return 0;
}
