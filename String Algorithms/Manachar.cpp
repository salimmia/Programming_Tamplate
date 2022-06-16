#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long
#define mod 1000000007

int ar[mx];
char ch[mx];
int n,m,k,ii;
int oddPlen[mx],evenPlen[mx];

void Manachers()
{
   int l=0,r=-1;
   for(int i=0;i<n;i++)
   {
     int k=(i>r)?1:min(oddPlen[l+r-i],r-i+1);
     while(k<=i && i+k<n && ch[i-k]==ch[i+k])
     {
       k++;
     }
     oddPlen[i]=k--;
     if(i+k>r){
      l=i-k;
      r=i+k;
     }
   }

   l=0,r=-1;
   for(int i=0;i<n;i++)
   {
     int k=(i>r)?0:min(evenPlen[l+r-i+1],r-i+1);
     while(k+1<=i && i+k<n && ch[i-k-1]==ch[i+k])
     {
       k++;
     }
     evenPlen[i]=k--;
     if(i+k>r){
      l=i-k-1;
      r=i+k;
     }
   }


}

void solve()
{
   scanf("%s",ch);
   n=strlen(ch);
   Manachers();
   for(int i=0;i<n;i++)printf("%d %d\n",oddPlen[i]*2-1,evenPlen[i]*2);

    
}

int main()
{
  int t=1;
 // scanf("%d",&t);
  while(t--)
  {
    solve();
  }

  return 0;
}
