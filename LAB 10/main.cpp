#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

class Base
{ // Base class for the data variables
protected:
    int W;
    int n;
    int revenue[MAX_N];
    int weight[MAX_N];

public:
    virtual void knapsack() = 0;
};

class Derived : public Base
{ // Derived class for the virtual function implementation
public:
    Derived();
    virtual void knapsack();
};

Derived::Derived()
{ // Constructor for the derived class
    cin >> W;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> revenue[i];
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    return;
}

void Derived::knapsack()
{ // knapsack algorithm implementation
    int dp[W + 1];
    dp[0] = 0;
    for (int i = 1; i <= W; i++)
    {
        dp[i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i - weight[j] >= 0)                         // verify that it doesn't go out of bounds
                if (dp[i] < dp[i - weight[j]] + revenue[j]) // making dp[i] maximum
                    dp[i] = dp[i - weight[j]] + revenue[j];
        }
    }
    cout << dp[W] << endl;
    return;
}

int main()
{
    Derived d;    // declaring a derived class object which takes inputs and stores them
    d.knapsack(); // calling the knapsack function which calculates optimized value and prints it
    return 0;
}