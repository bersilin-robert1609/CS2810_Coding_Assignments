#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;

#define minStr "_"
#define maxStr "("

template<typename T>
class Node
{
public:
    Node(T key, T value);
    T key;
    T value;
    Node<T>* after;
    Node<T>* before;
    Node<T>* above;
    Node<T>* below;
};

template<typename T>
Node<T>::Node(T key, T value)
{
    this->key = key;
    this->value = value;
    after = NULL;
    before = NULL;
    above = NULL;
    below = NULL;
}

int randomise() {return rand()%100;}

template<typename T>
class SkipList
{
public:
    //SkipList<T>(int max_levels);
    Node<T>* insertB(T key, T value);
    void eraseB(T key);
    Node<T>* searchB(T key);
    Node<T>* createNewLevel();
protected:
    int MAX_LEVELS;
    int element_count;
    int top_level;
    Node<T>* header;
};

// template<typename T>
// SkipList<T>::SkipList(int max_levels)
// {
//     MAX_LEVELS = max_levels;
//     element_count = 0;
//     top_level = 0;
//     if(typeid(T) == typeid(string)) header = new Node<T>(minStr, minStr);   //string
//     else header = new Node<T>(-1, -1);                                      //int

//     Node<T>* newptr;
//     if(typeid(T) == typeid(string)) newptr = new Node<T>(maxStr, maxStr);   //string
//     else newptr = new Node<T>(INT_MAX, -1);                                 //int

//     header->after = newptr;
//     newptr->before = header;
// }

template<typename T>
Node<T>* SkipList<T>::searchB(T key)
{
    Node<T>* ptr = header;

    while(ptr->below != NULL)
    {
        ptr = ptr->below;
        while(key >= (ptr->after)->key)
        {
            ptr = ptr->after;
        }
    }
    return ptr;
}

template<typename T>
Node<T>* SkipList<T>::createNewLevel()
{
    Node<T>* ptr = header;
    Node<T>* nptr;
    if(typeid(T) == typeid(string)) nptr = new Node<T>(minStr, minStr);
    else nptr = new Node<T>(-1, -1);

    Node<T>* newptr;
    if(typeid(T) == typeid(string)) newptr = new Node<T>(maxStr, maxStr);
    else newptr = new Node<T>(INT_MAX, -1);

    header->above = nptr;
    nptr->below = header;
    header->after->above = newptr;
    newptr->below = header->after;
    nptr->after = newptr;
    newptr->before = nptr;

    return nptr;
} 

template<typename T>
Node<T>* SkipList<T>::insertB(T key, T value){

    Node<T>* p = searchB(key);
    if(p->key == key)
    {
        while(p->above != NULL)
            p = p->above;

        return p;
    }
    Node<T>* q = NULL;
    int i = -1;
    int flag = 0;

    do
    {
        i++;
        if(i>=top_level && top_level < MAX_LEVELS)
        {
            top_level++;
            header = createNewLevel();
        }
        
        if(top_level == MAX_LEVELS){flag = 1;}

        Node<T>* newptr = new Node<T>(key, value);
        Node<T>* holder = p->after;

        p->after = newptr;
        newptr->before = p;
        holder->before = newptr;
        newptr->after =  holder;
        q = newptr;

        while(p->above == NULL)
        {
            p = p->before;
        }
        p = p->above;
    }
    while(randomise()%2 == 0 && flag == 0);

    element_count++;
    return q;
}

template<typename T>
void SkipList<T>::eraseB(T key)
{
    Node<T>* p = searchB(key);
    if(p->key == key)
    {
        while(p->above != NULL)
        {
            p = p->above;
        }
        p->before->after = p->after;
        p->after->before = p->before;
        element_count--;
    }
}

template<typename T>
class Dictionary: public SkipList<T>
{   
public:
    Dictionary(int max_levels);
    void empty();
    void size();  
    void print();
    void insert(T key, T value);
    void erase(T key);
    void search(T key); 
};

template<typename T>
Dictionary<T>::Dictionary(int max_levels)
{
    this->MAX_LEVELS = max_levels;
    this->element_count = 0;
    this->top_level = 0;
    if(typeid(T) == typeid(string)) this->header = new Node<T>(minStr, minStr);   //string
    else this->header = new Node<T>(-1, -1);                                      //int

    Node<T>* newptr;
    if(typeid(T) == typeid(string)) newptr = new Node<T>(maxStr, maxStr);   //string
    else newptr = new Node<T>(INT_MAX, -1);                                 //int

    this->header->after = newptr;
    newptr->before = this->header;
}

template<typename T>
void Dictionary<T>::empty()
{
    if(this->element_count == 0)
        cout<<"True"<<endl;
    else
        cout<<"False"<<endl;
}

template<typename T>
void Dictionary<T>::size()
{
    cout<<this->element_count<<endl;
}

template<typename T>
void Dictionary<T>::insert(T key, T value)
{
    Node<T>* ptr = this->insertB(key, value);
    return;
}

template<typename T>
void Dictionary<T>::erase(T key)
{
    this->eraseB(key);
    return;
}

template<typename T>
void Dictionary<T>::search(T key)
{
    Node<T>* ptr = this->searchB(key);
    if(ptr->key == key)
        cout<<ptr->value<<endl;
    else
        cout<<"NOT FOUND"<<endl;
}

int main() {  
    srand(time(NULL));
    string str;
    cin>>str;

    if(str == "STRINGDICT"){
        Dictionary<string> Dict = Dictionary<string>(10);

        int Q; cin>>Q;
        while(Q--)
        {
            string str; cin>>str;
            if(str == "INSERT")
            {
                string key, value; cin>>key>>value;
                Dict.insert(key, value);
            }
            else if(str == "DELETE")
            {
                string key; cin>>key;
                Dict.erase(key);
            }
            else if(str == "FIND")
            {
                string key; cin>>key;
                Dict.search(key);
            }
            else if(str == "SIZE")
            {
                Dict.size();
            }
            else if(str == "ISEMPTY")
            {
                Dict.empty();
            }
            else if(str == "PRINT")
            {
                Dict.print();
            }
        }
    }
    else
    {
        Dictionary<int> Dict = Dictionary<int>(10);

        int Q; cin>>Q;
        while(Q--)
        {
            string str; cin>>str;
            if(str == "INSERT")
            {
                int key, value; cin>>key>>value;
                Dict.insert(key, value);
            }
            else if(str == "DELETE")
            {
                int key; cin>>key;
                Dict.erase(key);
            }
            else if(str == "FIND")
            {
                int key; cin>>key;
                Dict.search(key);
            }
            else if(str == "SIZE")
            {
                Dict.size();
            }
            else if(str == "ISEMPTY")
            {
                Dict.empty();
            }
            else if(str == "PRINT")
            {
                Dict.print();
            }
        }
    }
    return 0;
}