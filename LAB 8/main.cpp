#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
#include <climits>
using namespace std;

#define minStr " "
#define maxStr "zzzzzzzz"

template <typename T>
class Node // Node class for SkipList
{
public:
    Node(T key, T value); // Constructor
    T key;                // Key
    T value;              // Value
    Node<T> *after;       // Pointer to next node
    Node<T> *before;      // Pointer to previous node
    Node<T> *above;       // Pointer to next level
    Node<T> *below;       // Pointer to previous level
};

template <typename T>
Node<T>::Node(T key, T value) // constructor
{
    this->key = key;
    this->value = value;
    after = NULL;
    before = NULL;
    above = NULL;
    below = NULL;
}

int randomise() { return rand() % 100; } // Function to generate random number

template <typename T>
class SkipList // SkipList class
{
public:
    Node<T> *insertB(T key, T value);                           // Insertion function
    void eraseB(T key);                                         // Deletion function
    Node<T> *searchB(T key);                                    // Search function
    Node<T> *createNewLevel();                                  // Function to create new level
    void setCreateInitValues(Node<T> *&nptr, Node<T> *&newptr); // Function to set initial values
    void setMinMax(T min, T max)
    {
        this->min = min;
        this->max = max;
    } // Function to set min and max
protected:
    int MAX_LEVELS;
    int element_count;
    int top_level;
    Node<T> *header;
    T min, max;
};

template <typename T>
Node<T> *SkipList<T>::searchB(T key) // Search Function
{
    Node<T> *ptr = header;

    while (ptr->below != NULL) // Traverse to bottom level
    {
        ptr = ptr->below;
        while (key >= (ptr->after)->key) // Traverse to correct node
        {
            ptr = ptr->after;
        }
    }
    return ptr;
}

template <typename T>
void SkipList<T>::setCreateInitValues(Node<T> *&nptr, Node<T> *&newptr)
{
    nptr = new Node<T>(min, min);
    newptr = new Node<T>(max, max);
}

template <typename T>
Node<T> *SkipList<T>::createNewLevel()
{
    Node<T> *ptr = header;
    Node<T> *nptr;
    Node<T> *newptr;
    setCreateInitValues(nptr, newptr);

    header->above = nptr;
    nptr->below = header;
    header->after->above = newptr;
    newptr->below = header->after;
    nptr->after = newptr;
    newptr->before = nptr;

    return nptr;
}

template <typename T>
Node<T> *SkipList<T>::insertB(T key, T value)
{

    Node<T> *p = searchB(key);
    if (p->key == key)
    {
        while (p->above != NULL)
            p = p->above;

        return p;
    }
    Node<T> *q = NULL;
    int i = -1;
    int flag = 0;

    do
    {
        i++;
        if (i >= top_level && top_level < MAX_LEVELS) // If top level is reached, create new level
        {
            top_level++;
            header = createNewLevel();
        }

        if (top_level == MAX_LEVELS)
        {
            flag = 1;
        } // But only till 10

        Node<T> *newptr = new Node<T>(key, value);
        Node<T> *holder = p->after;

        p->after = newptr;
        newptr->before = p;
        holder->before = newptr;
        newptr->after = holder;
        newptr->below = q;
        if (q != NULL)
            q->above = newptr;
        q = newptr;

        while (p->above == NULL)
        {
            p = p->before;
        }
        p = p->above;
    } while (randomise() % 2 == 0 && flag == 0);

    element_count++;
    return q;
}

template <typename T>
void SkipList<T>::eraseB(T key)
{
    // print();
    Node<T> *p = searchB(key);
    if (p->key == key)
    {
        while (p)
        {
            p->before->after = p->after;
            p->after->before = p->before;
            p = p->above;
        }
        element_count--;
    }
}

template <typename T>
class Dictionary : public SkipList<T>
{
public:
    Dictionary(int max_levels);          // Constructor
    void empty();                        // Function to check if dictionary is empty
    void size();                         // Function to check size of dictionary
    void insert(T key, T value);         // Function to insert key and value
    void erase(T key);                   // Function to delete key
    void search(T key);                  // Function to search key
    void setInitialValues(T min, T max); // Function to set initial values
};

template <typename T>
Dictionary<T>::Dictionary(int max_levels)
{
    this->MAX_LEVELS = max_levels;
    this->element_count = 0;
    this->top_level = 0;
    this->header = NULL;
}

template <typename T>
void Dictionary<T>::setInitialValues(T min, T max)
{
    this->header = new Node<T>(min, min);
    Node<T> *newptr = new Node<T>(max, max);

    this->header->after = newptr;
    newptr->before = this->header;
}

template <typename T>
void Dictionary<T>::empty()
{
    if (this->element_count == 0)
        cout << "True" << endl;
    else
        cout << "False" << endl;
}

template <typename T>
void Dictionary<T>::size()
{
    cout << this->element_count << endl;
}

template <typename T>
void Dictionary<T>::insert(T key, T value)
{
    Node<T> *ptr = this->insertB(key, value);
    return;
}

template <typename T>
void Dictionary<T>::erase(T key)
{
    this->eraseB(key);
    return;
}

template <typename T>
void Dictionary<T>::search(T key)
{
    Node<T> *ptr = this->searchB(key);
    if (ptr->key == key)
        cout << ptr->value << endl;
    else
        cout << "NOT FOUND" << endl;
}

int main()
{
    srand(time(NULL));
    string str;
    cin >> str;

    if (str == "STRINGDICT")
    {
        Dictionary<string> Dict(10);
        Dict.setMinMax(minStr, maxStr);
        Dict.setInitialValues(minStr, maxStr);

        int Q;
        cin >> Q;
        while (Q--)
        {
            string str;
            cin >> str;
            if (str == "INSERT")
            {
                string key, value;
                cin >> key >> value;
                Dict.insert(key, value);
            }
            else if (str == "DELETE")
            {
                string key;
                cin >> key;
                Dict.erase(key);
            }
            else if (str == "FIND")
            {
                string key;
                cin >> key;
                Dict.search(key);
            }
            else if (str == "SIZE")
            {
                Dict.size();
            }
            else if (str == "ISEMPTY")
            {
                Dict.empty();
            }
        }
    }
    else if (str == "INTEGERDICT")
    {
        Dictionary<int> Dict(10);
        Dict.setMinMax(INT_MIN, INT_MAX);
        Dict.setInitialValues(INT_MIN, INT_MAX);

        int Q;
        cin >> Q;
        while (Q--)
        {
            string str;
            cin >> str;
            if (str == "INSERT")
            {
                int key, value;
                cin >> key >> value;
                Dict.insert(key, value);
            }
            else if (str == "DELETE")
            {
                int key;
                cin >> key;
                Dict.erase(key);
            }
            else if (str == "FIND")
            {
                int key;
                cin >> key;
                Dict.search(key);
            }
            else if (str == "SIZE")
            {
                Dict.size();
            }
            else if (str == "ISEMPTY")
            {
                Dict.empty();
            }
        }
    }
    return 0;
}