#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Vector
{
private:
    size_t currentCapacity;
    size_t currentSize;
    T* vec;
public:
    class EmptyVector{};
    Vector(size_t c)
    {
        currentCapacity = c;
        currentSize = 0;
        vec = new T[currentCapacity];
    }
    Vector(size_t c, T x)
    {
        currentCapacity = c;
        currentSize = c;
        vec = new T[currentCapacity];
        for(int i = 0; i<currentSize; i++) vec[i] = x;
    }
    Vector()
    {
        currentCapacity = 1;
        currentSize = 0;
        vec = new T[currentCapacity];
        return;
    }
    size_t capacity() {return currentCapacity;}
    size_t size() {return currentSize;}
    void push(T x)
    {
        if(currentSize == currentCapacity)
        {
            T* temp = new T[currentCapacity*2];
            for(size_t i = 0; i < currentSize; i++)
            {
                temp[i] = vec[i];
            }
            delete[] vec;
            vec = temp;
            currentCapacity *= 2;
        }
        vec[currentSize] = x;
        currentSize++;
        return;
    }
    void pop()
    {
        try{
            if(currentSize == 0) throw EmptyVector();
        }
        catch(EmptyVector) 
        {
            return;
        }

        if(currentSize*4 <= currentCapacity){
            T* temp = new T[currentCapacity/2];
            for(size_t i = 0; i < currentSize; i++)
            {
                temp[i] = vec[i];
            }
            delete[] vec;
            vec = temp;
            currentCapacity *= 2;
        }
        currentSize--;
        return;
    }
    T front()
    {
        if(currentSize >= 1) return vec[0];
        else return -1;
    }
    T back()
    {
        if(currentSize >= 1) return vec[currentSize-1];
        else return -1;
    }
    T& operator[](size_t i) {return vec[i];}

    int partition(int* a, int i, int j)
    {
        int pivot = a[i];
        int aux[j-i+1];
        int l = 0;
        int m = j-i;
        for(int k = i+1; k<=j; k++){
            if(a[k] <= pivot) aux[l++] = a[k];
            else aux[m--] = a[k];
        }
        aux[l] = pivot;
        for(int z=i; z<=j; z++){
            a[z] = aux[z-i];
        }
        return i+l;
    }

    void quicksort(int* a, int i, int j)
    {
        if(i < j)
        {
            int pi = partition(a, i, j);

            quicksort(a, i, pi-1);
            quicksort(a, pi+1, j);
        }
    }
    void sort(){
        int i = 0;
        int j = currentSize - 1;
        quicksort(vec, i, j);
    }

    void print()
    {
        for(size_t i = 0; i < currentSize; i++)
        {
            cout << vec[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    string str;
    getline(cin, str);
    int sp = 0;

    for(int i=0; i<str.length(); i++){
        if(str[i] == ' ' && str.length() > 7) sp++; 
    }

    Vector<int> v;

    if(sp == 0)
    {
        v = Vector<int>();
    }
    else if(sp == 1)
    {
        str = str.substr(7, str.length()-7);
        int x = stoi(str);
        v = Vector<int>(x);
    }
    else
    {
        str = str.substr(str.find(' ')+1, str.length()-str.find(' ')-1);
        string str1 = str.substr(0, str.find(' '));
        string str2 = str.substr(str.find(' ')+1, str.length()-str.find(' ')-1);
        int x = stoi(str1);
        int y = stoi(str2);
        v = Vector<int>(x, y);
    }

    int Q;
    cin>>Q;

    while(Q--)
    {
        string opcode;
        cin>>opcode;
        if(opcode == "front")
        {
            cout<<v.front()<<endl;
        }else if(opcode == "back")
        {
            cout<<v.back()<<endl;
        }else if(opcode == "push")
        {
            int x;
            cin>>x;
            v.push(x);
        }else if(opcode == "pop")
        {
            v.pop();
        }else if(opcode == "size")
        {
            cout<<v.size()<<endl;
        }else if(opcode == "capacity")
        {
            cout<<v.capacity()<<endl;
        }else if(opcode == "sort")
        {
            v.sort();
            v.print();
        }else if(opcode == "element")
        {
            int x;
            cin>>x;
            if(x >= v.size()) cout<<-1<<endl;
            else cout<<v[x]<<endl;
        }
    }
    
    return 0;
}