#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Node
{ // Node Class
private:
    bool isEnd;       // the boolean to know whether or not the prefix ends at the particular node
    vector<Node *> v; // the vector which holds the next letter of the prefixes if they exist

public:
    Node();                                              // the constructor for Node class
    bool returnisEnd() { return isEnd; }                 // the get function for 'isEnd' private variable
    void flipisEnd() { isEnd = !isEnd; }                 // the function to flip boolean parameter 'isEnd'
    Node *getNode(int i) { return v[i]; }                // the get function for the node of the subsequent character
    void setNode(int i, Node *ptr) { this->v[i] = ptr; } // adding a new node pointer for a particular character in vector
};

Node::Node()
{ // the constructor for Node class
    this->isEnd = false;
    this->v.resize(26);
    for (int i = 0; i < 26; i++)
        v[i] = NULL;
}

class TRIE
{ // the trie class
public:
    TRIE();                          // the constuctor for trie class
    void addPrefix(string str);      // the interface to add a prefix to the TRIE
    string returnPrefix(string str); // the interface to return the prefix of the string

private:
    Node *root; // the root of the TRIE class
};

TRIE::TRIE()
{ // the constuctor for trie class

    root = new Node();
}

void TRIE::addPrefix(string str)
{ // the interface to add a prefix to the TRIE

    int n = str.size();
    int i = 0;

    Node *ptr = root;

    while (i < n)
    {
        int offset = str[i] - 97; // the offset from 'a'

        if (ptr->getNode(offset) == NULL)
        {
            Node *newptr = new Node(); // creating a new node to add in trie
            ptr->setNode(offset, newptr);
        }
        ptr = ptr->getNode(offset);
        i++;
    }
    ptr->flipisEnd(); // flipping the isEnd variable as our prefix has ended

    return;
}

string TRIE::returnPrefix(string str)
{ // the interface to return the prefix of the string

    int n = str.size();
    int i = 0;

    Node *ptr = root;
    int offset;

    string buffer; // buffer string to store previously accepted prefixes
    int flag = 0;

    while (i < n)
    {
        offset = str[i] - 97;

        if (ptr->getNode(offset) == NULL)
            break;
        else
        {
            if (ptr->returnisEnd())
            {
                buffer = str.substr(0, i);
                flag = 1;
            }
            ptr = ptr->getNode(offset);
            i++;
        }
    }

    if (i > 0 && ptr->returnisEnd()) // returning the substr if the prefix has ended
        return str.substr(0, i);

    if (flag)
        return buffer; // returning the previously stored buffer if our string ends or prefix doesnt end

    return str;
}

int main()
{
    int p;
    cin >> p;

    vector<string> prefixes(p);
    for (int i = 0; i < p; i++)
        cin >> prefixes[i];

    int n;
    cin >> n;

    vector<string> strings(n);
    for (int i = 0; i < n; i++)
        cin >> strings[i];

    TRIE trie;

    for (int i = 0; i < p; i++)
        trie.addPrefix(prefixes[i]);

    for (int i = 0; i < n; i++)
        if (i != n - 1)
            cout << trie.returnPrefix(strings[i]) << " ";
        else
            cout << trie.returnPrefix(strings[i]);

    return 0;
}