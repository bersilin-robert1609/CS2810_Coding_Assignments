#include <bits/stdc++.h>
using namespace std;

/* Used Doubly_Linked_List template implemented in last lab */

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
        delete newptr;
        return temp;
    }
    head->prev = NULL; // general case

    newptr->next = NULL;
    delete newptr;

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
        delete newptr;
        return temp;
    }
    tail->next = NULL; // general case

    newptr->prev = NULL;
    delete newptr;

    return temp;
}

/* Doubly_Linked_List ends*/

template <typename T>
class Template_Queue
{
    // Template_Queue to be implemented
public:
    Template_Queue(); // general constructor
    void enqueue(T);  // function to add an element to the queue follows FIFO
    T dequeue();      // deletes the first item and returns it
    int size();       // returns size of the queue
    bool isEmpty();   // checks of the queue is empty or not, returns TRUE if empty

private:
    Doubly_linked_list<T> *dll; // just a doubly_Linked_List
};

template <typename T>
Template_Queue<T>::Template_Queue()
{
    // Just initializing an empty Doubly_Linked_List, invokes the custom constructor

    dll = new Doubly_linked_list<T>();
}

template <typename T>
void Template_Queue<T>::enqueue(T val)
{
    // adding an element to the queue

    dll->push_end(val);
}

template <typename T>
T Template_Queue<T>::dequeue()
{
    // deletes an element from the queue and returns it

    T temp = dll->pop_front();
    return temp;
}

template <typename T>
int Template_Queue<T>::size()
{
    // returns size of the queue

    return dll->size();
}

template <typename T>
bool Template_Queue<T>::isEmpty()
{
    // checks of the queue is empty or not, returns TRUE if empty

    if (dll->size() <= 0)
        return true;
    else
        return false;
}

template <typename T>
class Printer
{
    // printer class implementation using Template_queue

public:
    Printer(int capacity, int ink); // custom constructor
    void addDocument(T document);   // adding an document to the printer queue
    T printDocument();              // printing the first document in the queue
    void fillInk(int ink);          // replaces ink quantity in the printer
    class InsufficientInk
    {
        // Exception class for Insufficient Ink

    public:
        string String;
        InsufficientInk(string String)
        {
            this->String = String;
        };
    };
    class PrinterBusy
    {
        // Exception class for Printer Busy

    public:
        string String;
        PrinterBusy(string String)
        {
            this->String = String;
        }
    };
    class NoDocument
    {
        // Exception class for Empty Queue or No Document

    public:
        string String;
        NoDocument(string String)
        {
            this->String = String;
        }
    };

private:
    Template_Queue<T> *queue; // Template Queue element
    int capacity;             // max capacity of the printer queue
    int ink;                  // remaining ink left to print documents
};

template <typename T>
Printer<T>::Printer(int capacity, int ink)
{
    // Custom constuructor for adding capcity and ink

    this->capacity = capacity;
    this->ink = ink;
    queue = new Template_Queue<T>();
}

template <typename T>
void Printer<T>::addDocument(T document)
{
    // adding an document to the printer queue

    if (queue->size() >= capacity)
    {
        throw PrinterBusy("PRINTER_BUSY"); // throws PrinterBusy element if document is added when queue is full
    }

    queue->enqueue(document); // if the queue is not full
    return;
}

template <typename T>
T Printer<T>::printDocument()
{
    // printing the first document in the queue

    if (queue->size() <= 0)
    {
        throw NoDocument("NO_DOCUMENT"); // throws Nodocument element if document is tried to br printed out of empty queue
    }

    if (ink <= 0)
    {
        throw InsufficientInk("INSUFFICIENT_INK"); // throws InsufficientInk element if document is tried to be print when there is no ink
    }

    T document = queue->dequeue();
    ink--;

    return document;
}

template <typename T>
void Printer<T>::fillInk(int ink)
{
    // replaces ink quantity in the printer

    this->ink = ink;
    return;
}

template <typename T>
void query_function(Printer<T> *&ourPrinter)
{
    // function to take care of queries

    int Q;
    cin >> Q;

    while (Q--)
    {
        int opcode;
        cin >> opcode;

        switch (opcode)
        {
        case 1:
        {
            // Opcode 1 for adding a document to the printer queue

            T document;
            cin >> document;

            try
            {
                // trying to add document

                ourPrinter->addDocument(document);
            }
            catch (typename Printer<T>::PrinterBusy pb)
            {
                // if the add function sends the PrinterBusy error

                cout << pb.String << endl;
            }
            break;
        }
        case 2:
        {
            // Opcode 2 for printing a document from the printer queue

            try
            {
                // trying to print a document from the printer queue

                T document = ourPrinter->printDocument();
                cout << document << endl;
            }
            catch (typename Printer<T>::InsufficientInk ii)
            {
                // if the print function sends the InsufficientInk error

                cout << ii.String << endl;
            }
            catch (typename Printer<T>::NoDocument nd)
            {
                // if the print function sends the NoDocument error

                cout << nd.String << endl;
            }
            break;
        }
        case 3:
        {
            // Opcode 3 for changing ink quantity

            int ink;
            cin >> ink;

            ourPrinter->fillInk(ink);
            break;
        }
        }
    }

    return;
}

int main()
{
    // driver code

    int capacity, ink;
    char opcode;
    cin >> capacity >> ink >> opcode;

    switch (opcode)
    {
        // I for Integers, C for Characters, F for Floats

    case 'I':
    {
        Printer<int> *ourPrinter = new Printer<int>(capacity, ink);
        query_function(ourPrinter);
        //delete ourPrinter;
        break;
    }
    case 'C':
    {
        Printer<char> *ourPrinter = new Printer<char>(capacity, ink);
        query_function(ourPrinter);
        //delete ourPrinter;
        break;
    }
    case 'F':
    {
        Printer<float> *ourPrinter = new Printer<float>(capacity, ink);
        query_function(ourPrinter);
        //delete ourPrinter;
        break;
    }
    }

    return 0;
}