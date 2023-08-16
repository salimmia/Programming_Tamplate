//sieve 
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007
#define mx 100000005

int a[mx+10];
char ch[mx+10];
int n;
bitset<mx>is_composite;
vector<int>prime;
int phi[mx];


void seive(int n)
{
    phi[1]=1;

    for(int i=2;i<=n;i++)
    {
        if(!is_composite[i])
        {
            prime.push_back(i);
            phi[i]=i-1;              ///i is prime
        }

        for(int j=0;j<prime.size() && i*prime[j]<=n;j++)
        {
            is_composite[i*prime[j]]=true;

            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];   ///prime[j] divides i
                break;
            }
            else
            {
                phi[i*prime[j]]=phi[i]*phi[prime[j]];  ///prime[j] do not divide i
            }
        }
    }
}

void solve(int ii)
{
    scanf("%d",&n);
    sieve(n);

    cout<<prime.size()<<endl;

    for(auto it:prime)cout<<it<<" ";

   return;
}


int main()
{
    int t=1;

    for(int i=1;i<=t;i++)solve(i);

    return 0;
}
