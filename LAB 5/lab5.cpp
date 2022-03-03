/* C.Bersilin */

#include <iostream>
using namespace std;

/* Used Doubly_Linked_List template implemented in lab - 3 */

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

class Stack
{
public:
    Stack();            // constructor for stack
    void push(int val); // push 'val' into stack
    int pop();          // pop from stack and return it
    int top();          // take top element from stack and return it
    int isEmpty();      // returns 1 if empty else 0

private:
    Doubly_linked_list<int> dll; // using the doubly linked template as container
};

Stack::Stack()
{
    // constructor for stack
    dll = Doubly_linked_list<int>(); // declaring the private variable
}

void Stack::push(int val)
{
    // push 'val' into stack
    dll.push_front(val);
}

int Stack::pop()
{
    // pop from stack and return it
    int temp;

    if (dll.size() <= 0)
        temp = -1; // returns -1 if stack is empty
    else
        temp = dll.pop_front();

    return temp;
}

int Stack::top()
{
    // take top element from stack and return it
    int temp;

    if (dll.size() <= 0)
        temp = -1; // returns -1 if stack is empty
    else
    {
        temp = dll.pop_front();
        dll.push_front(temp);
    }

    return temp;
}

int Stack::isEmpty()
{
    // returns 1 if empty else 0
    if (dll.size() <= 0)
        return 1;
    else
        return 0;
}

class Graph
{
public:
    Graph(int n);                                                        // constructor for graph
    friend void operator+=(const Graph &graph, const pair<int, int> &p); // operator overloading for +=
    friend void operator-=(const Graph &graph, const pair<int, int> &p); // operator overloading for -=
    int detectCycle();                                                   // returns 1 if a cycle exists
    int explore(int i, int visited[], int par);                          // helper function for detectCycle()
    int reach(int u, int v);                                             // returns 1 if v is reachable from u
    friend ostream &operator<<(ostream &s, const Graph &graph);          // operator overloading for <<

private:
    int **arr; // the adjacency matrix
    int n;     // the number of vertices
};

Graph::Graph(int n)
{
    // constructor for graph
    this->n = n;

    arr = new int *[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 0;
        }
    }

    return;
}

void operator+=(const Graph &graph, const pair<int, int> &p)
{
    // operator overloading for +=
    graph.arr[p.first][p.second] = 1;
    graph.arr[p.second][p.first] = 1;
    return;
}

void operator-=(const Graph &graph, const pair<int, int> &p)
{
    // operator overloading for -=
    graph.arr[p.first][p.second] = 0;
    graph.arr[p.second][p.first] = 0;
    return;
}

int Graph::detectCycle()
{
    // returns 1 if a cycle exists
    int *visited = new int[n];

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        if (!visited[i])
            temp = explore(i, visited, -1);

        if (temp == 1)
            return 1;
    }

    free(visited);
    return 0;
}

int Graph::explore(int i, int visited[], int par)
{
    // helper function for detectCycle()
    visited[i] = 1;

    for (int j = 0; j < n; j++)
    {
        int temp = 0;

        if (arr[i][j] == 1 && visited[j] == 1 && j != par)
            return 1;
        else if (arr[i][j] == 1 && visited[j] == 0)
            temp = explore(j, visited, i);

        if (temp == 1)
            return 1;
    }

    return 0;
}

ostream &operator<<(ostream &s, const Graph &graph)
{
    // operator overloading for <<
    for (int i = 0; i < graph.n; i++)
    {
        for (int j = 0; j < graph.n; j++)
        {
            s << graph.arr[i][j] << " ";
        }
        s << endl;
    }

    return s;
}

int Graph::reach(int u, int v)
{
    // returns 1 if v is reachable from u
    if (u == v)
        return 1;

    bool *visited = new bool[n];

    for (int i = 0; i < n; i++)
        visited[i] = false;

    Stack st;

    st.push(u);
    visited[u] = true;

    while (!st.isEmpty())
    {
        int temp = st.pop();

        if (temp == v)
            return 1;

        for (int i = 0; i < n; i++)
        {
            if (arr[temp][i] == 1 && visited[i] == false)
            {
                st.push(i);
                visited[i] = true;
            }
        }
    }

    free(visited);
    return 0;
}

int main()
{ //driver code

    int sq;
    cin >> sq;

    Stack S;

    for (int i = 0; i < sq; i++)
    {
        string str;
        cin >> str;

        if (str == "push")
        {
            int val;
            cin >> val;

            S.push(val);
        }
        else if (str == "pop")
            cout << S.pop() << endl;
        else if (str == "top")
            cout << S.top() << endl;
        else if (str == "empty")
            cout << S.isEmpty() << endl;
    }

    int n, Q;
    cin >> n >> Q;

    Graph graph(n);

    while (Q--)
    {
        string str;
        cin >> str;

        if (str == "add")
        {
            int u, v;
            cin >> u >> v;

            graph += pair<int, int>(u, v);
        }
        else if (str == "del")
        {
            int u, v;
            cin >> u >> v;

            graph -= pair<int, int>(u, v);
        }
        else if (str == "cycle")
        {
            cout << graph.detectCycle() << endl;
        }
        else if (str == "print")
        {
            cout << graph;
        }
        else if (str == "reach")
        {
            int u, v;
            cin >> u >> v;

            if (u >= 0 && v >= 0 && u < n && v < n)
                cout << graph.reach(u, v) << endl;
        }
    }
    return 0;
}
