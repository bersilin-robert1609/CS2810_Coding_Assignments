#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class Node{
    public:
        T value;
        Node();
        Node* prev;
        Node* next;
};

template<typename T>
Node<T>::Node(){
    this->prev = NULL;
    this->next = NULL;
}

template<typename T>
class Doubly_linked_list{
    public:
        Doubly_linked_list();
        void push_front(T);
        void push_end(T);
        T pop_front();
        T pop_end();
        int size();

    private:
        Node<T>* head;
        Node<T>* tail;
        int elementsCount;
};

template<typename T>
int Doubly_linked_list<T>::size(){
    return elementsCount;
}

template<typename T>
Doubly_linked_list<T>::Doubly_linked_list(){
    elementsCount = 0;
    this->head = NULL;
    this->tail = NULL;
}

template<typename T>
void Doubly_linked_list<T>::push_front(T val){

    elementsCount++;

    Node<T>* newptr = new Node<T>();
    newptr->value = val;

    if(head == NULL){
        head = newptr;
        tail = newptr;
        return;
    }

    head->prev = newptr;
    newptr->next = head;
    head = newptr;
    return;
}

template<typename T>
void Doubly_linked_list<T>::push_end(T val){

    elementsCount++;

    Node<T>* newptr = new Node<T>();
    newptr->value = val;

    if(head == NULL){
        head = newptr;
        tail = newptr;
        return;
    }

    tail->next = newptr;
    newptr->prev = tail;
    tail = newptr;;
    return;
}

template<typename T>
T Doubly_linked_list<T>::pop_front(){

    elementsCount--;

    Node<T>* newptr = head;
    T temp = newptr->value;

    head = head->next;
    if(head == NULL){
        tail = NULL;
        //free newptr;
        return temp;
    }
    head->prev = NULL;

    newptr->next = NULL;
    //free newptr;

    return temp;
}

template<typename T>
T Doubly_linked_list<T>::pop_end(){

    elementsCount--;

    Node<T>* newptr = tail;
    T temp = newptr->value;

    tail = tail->prev;
    if(tail == NULL){
        head = NULL;
        //free newptr;
        return temp;
    }
    tail->next = NULL;

    newptr->prev = NULL;
    //free newptr;

    return temp;
}

template<typename T>
class Template_stack{
    public:
        Template_stack();
        void push(T);
        T pop();
        T top();
        int size();
        bool compare(T);

    private:
        Doubly_linked_list<T>* dll;
};

template<typename T>
Template_stack<T>::Template_stack(){
    dll = new Doubly_linked_list<T>();
}

template<typename T>
void Template_stack<T>::push(T val){
    dll->push_front(val);
}

template<typename T>
T Template_stack<T>::pop(){
    T temp = dll->pop_front();
    return temp;
}

template<typename T>
T Template_stack<T>::top(){
    T temp = dll->pop_front();
    dll->push_front(temp);
    return temp;
}

template<typename T>
int Template_stack<T>::size(){
    return dll->size();
}

template<typename T>
bool Template_stack<T>::compare(T val){
    T temp = top();
    if(val > temp) return true;
    else return false;
}

template<typename T>
void encrypt_stack_input(Template_stack<T>* &S, int n){
    while(n--){
        T temp;
        cin>>temp;

        if(S->size() == 0){
            S->push(temp);
        }else if(temp > S->top()){
            S->push(temp);
        }else if(temp <= S->top()){
            while(S->size() > 0){
                if(temp <= S->top()){
                    T pop_temp = S->pop();
                    cout<<pop_temp;
                }else{
                    break;
                }
            }
            S->push(temp);
        }
    }

    while(S->size() > 0) cout<<S->pop();
    cout<<endl;
    return;
}

int main() {

    int n;
    cin>>n;
    char opcode;
    cin>>opcode;

    if(opcode == 'I'){
        Template_stack<int>* S = new Template_stack<int>();
        encrypt_stack_input<int>(S, n);
    }else if(opcode == 'C'){
        Template_stack<char>* S = new Template_stack<char>();
        encrypt_stack_input<char>(S, n);
    }else if(opcode == 'F'){
        Template_stack<float>* S = new Template_stack<float>();
        encrypt_stack_input<float>(S, n);
    }
     
    return 0;
}
