#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin>>n;

    vector<int> a(n+2);
    for(int i=1; i<=n; i++)
        cin>>a[i];
    a[0] = a[n+1] = 1;
    
    int p;
    cin>>p;
    
    int mat[n+1][n+1];
    for(int i=0; i<=n; i++)
        for(int j = 0; j <= n; j++)
            mat[i][j] = 0;
    
    for(int b = 1; b<=n; b++)
    {
        for(int i = 0; i<=n-b; i++)
        {
            int j = i+b;
            mat[i][j] = 0;
            for(int k = i; k<j; k++)
            {
                int newval = mat[i][k] + mat[k+1][j] + a[i]*a[k+1]*a[j+1];
                mat[i][j] = (newval > mat[i][j]) ? newval : mat[i][j];
            }
        }
    }
    
    cout<<mat[0][n]<<endl;
    if(mat[0][n]<p) cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
}