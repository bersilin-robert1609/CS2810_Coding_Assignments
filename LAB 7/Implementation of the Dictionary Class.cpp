#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

class Dictionary
{ //Dictionary Class
public:
    void buildDict(vector<string> words);                   //initializing a map to hold the strings passed as an array
    void addWordToDict(string word);                        //adding a word or string to a dictionary
    bool search(string target);                             //searching for a particular word in the dictionary
    set<string> getWordsAfterReplace(string target);        //storing the words which differ in atmost 1 letter to the passed argument string
    set<string> getWordsAfterSwap(string target);           //storing the words which are similar when 1 letter is swapped in the string
    int maxChangeableWord();                                //the maximum number of words which differ by 1 letter
    int maxSwappableWord();                                 //the maximum number of words which are similar by swapping

private:
    map<int, set<string>> wordMap;                          //the map that stores the key value pair where key is the length of the strings stored as a set in its value
};

void Dictionary::buildDict(vector<string> words)
{ //initializing a map to hold the strings passed as an array
    for(long unsigned int i = 0; i < words.size(); i++)  
        wordMap[words[i].length()].insert(words[i]);
    return;
}

void Dictionary::addWordToDict(string word)
{ //adding a word or string to a dictionary
    wordMap[word.length()].insert(word);
    return;
}

bool Dictionary::search(string target)
{ //searching for a particular word in the dictionary
    auto position = wordMap[target.length()].find(target);
    if(position != wordMap[target.length()].end()) return true;
    return false;
}

set<string> Dictionary::getWordsAfterReplace(string target)
{ //storing the words which differ in atmost 1 letter to the passed argument string
    set<string> oneLetterDiff;

    for(auto itr : wordMap[target.length()])
    {   
        int diffs = 0;
        for(long unsigned int i=0; i<target.length(); i++)     
            if(itr[i] != target[i])
                diffs++;

        if(diffs < 2)   
            oneLetterDiff.insert(itr); 
    }

    return oneLetterDiff;
}

set<string> Dictionary::getWordsAfterSwap(string target)
{ //storing the words which are similar when 1 letter is swapped in the string
    set<string> oneSwapDiff;
    int strlen = target.length();

    for(int i=0; i<strlen-1; i++){
        string str = target;
        char ch = str[i];
        str[i] = str[i+1];
        str[i+1] = ch;

        if(this->search(str)) oneSwapDiff.insert(str);
    } 

    return oneSwapDiff;
}

int Dictionary::maxChangeableWord()
{ //the maximum number of words which differ by 1 letter
    long unsigned int maxSize = 0;
    for(int i=1; i<10; i++)
        if(wordMap[i].size() > 0)
            for(auto itr : wordMap[i])
                if(getWordsAfterReplace(itr).size() > maxSize) maxSize = getWordsAfterReplace(itr).size();
    return maxSize-1;
}

int Dictionary::maxSwappableWord()
{ //the maximum number of words which are similar by swapping
    long unsigned int maxSize = 0;
    for(int i=1; i<10; i++)
        if(wordMap[i].size() > 0)
            for(auto itr : wordMap[i])
                if(getWordsAfterSwap(itr).size() > maxSize) maxSize = getWordsAfterSwap(itr).size();
    return maxSize;
}

int main() {
    int n;
    cin>>n;
    vector<string> a(n);
    for(auto &i : a) cin >> i;

    Dictionary Dict;
    Dict.buildDict(a);

    int q;
    cin>>q;

    while(q--)
    {
        int opcode;
        cin>>opcode;

        switch(opcode)
        {
            case 1:
            {
                string tempstr;
                cin>>tempstr;

                Dict.addWordToDict(tempstr);
                break;
            }
            case 2:
            {
                string tempstr;
                cin>>tempstr;

                if(Dict.search(tempstr)) cout<<"true"<<endl;
                else cout<<"false"<<endl;
                
                break;
            }
            case 3:
            {
                string tempstr;
                cin>>tempstr;

                if(Dict.getWordsAfterReplace(tempstr).size() > 0)
                    for(auto itr: Dict.getWordsAfterReplace(tempstr))
                        cout<<itr<<" ";
                else 
                    cout<<-1;
                cout<<endl;
                break;
            }
            case 4:
            {
                string tempstr;
                cin>>tempstr;

                if(Dict.getWordsAfterSwap(tempstr).size() > 0)
                    for(auto itr: Dict.getWordsAfterSwap(tempstr))
                        cout<<itr<<" ";
                else 
                    cout<<-1;
                cout<<endl;
                break;
            }
            case 5:
            {
                cout<<Dict.maxChangeableWord()<<endl;
                break;
            }
            case 6:
            {
                cout<<Dict.maxSwappableWord()<<endl;
                break;
            }
        }
    }
    return 0;
}