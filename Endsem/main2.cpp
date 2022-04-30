#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;

    char a[n];
    int type[n];
    int R_count = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i]=='R'){
            type[i]=1;
            R_count++;
        }
        else type[i]=0;
    }

    int k;
    cin>>k;

    for(int i=0; i<n; i++)
    {
        if(a[i] == 'E')
        {
            for(int x = -k; x <= k; x++)
            {
                if(i+x >= 0 && x != 0 && i+x < n)
                {
                    if(a[i+x] == 'R' && type[i+x] == 1)
                    {
                        a[i] = 'R';
                        R_count++;
                        type[i] = 2;
                        type[i+x] = 2;
                        break;
                    }
                }
            }
        }
    }

    cout<<R_count<<endl;

    return 0;
}