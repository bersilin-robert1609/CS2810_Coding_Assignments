#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100

vector<vector<string>> closest_word(MAX_N);     //the adjacency list type of structure to hold the closest words 
vector<int> edit_distances(MAX_N);              //the minimum edit distances of the words in the sentence 

int edit_distance(string word, string dict_word)
{
    int m = word.length();
    int n = dict_word.length();
    int e[m+1][n+1];

    for(int i=0; i<=m; i++)
        e[i][0] = i;
    for(int j=0; j<=n; j++)
        e[0][j] = j;
    for(int i=1; i<=m; i++)
    {    
        for(int j=1; j<=n; j++)
        {
            int diff = ((word[i-1] == dict_word[j-1]) ? 0 : 1);
            e[i][j] = min(e[i][j-1]+1, min(e[i-1][j]+1, e[i-1][j-1] + diff));
        }
    }
    return e[m][n];       
}

string LCS(string word, string dict_word)
{
    int m = word.length();
    int n = dict_word.length();  
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (word[i - 1] == dict_word[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    string lcs_word = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (word[i - 1] == dict_word[j - 1]) {
            lcs_word = word[i - 1] + lcs_word;
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    return lcs_word;    
}

void populate_closest_words_distances(vector<string> dict, vector<string> sent)
{
    int N = sent.size();
    int D = dict.size();

    for(int i=0; i<N; i++)
    {
        int min_dist = INT_MAX;
        for(int j=0; j<D; j++)
        {
            int dist = edit_distance(sent[i], dict[j]);
            if(dist < min_dist)
            {
                min_dist = dist;
                closest_word[i].clear();
                closest_word[i].push_back(dict[j]);
            }
            else if(dist == min_dist)
            {
                string lcs1 = LCS(sent[i], dict[j]);
                string lcs2 = LCS(sent[i], closest_word[i][0]);

                if(lcs1.length() > lcs2.length())
                {
                    closest_word[i].clear();
                    closest_word[i].push_back(dict[j]);
                }
                else if(lcs1.length() == lcs2.length())
                {
                    closest_word[i].push_back(dict[j]);
                }
            }
        }
        edit_distances[i] = min_dist;
    }
}

int main(){
    int N;
    cin>>N;

    vector<string> sent(N);
    for(int i=0; i<N; i++)
        cin>>sent[i];

    int D;
    cin>>D;

    vector<string> dict(D);
    for(int i=0; i<D; i++)
        cin>>dict[i];


    populate_closest_words_distances(dict, sent);

    for(int i = 0; i < N; i++)
    {   
        for(int j=0; j<(int)closest_word[i].size(); j++)
        {
            cout<<sent[i]<<endl;
            cout<<closest_word[i][j]<<endl;
            string str = LCS(sent[i], closest_word[i][j]);
            if(str.length()<=0) cout<<"EMPTY"<<endl;
            else cout<<str<<endl; 
            cout<<edit_distances[i]<<endl;     
        }
        
    }

}