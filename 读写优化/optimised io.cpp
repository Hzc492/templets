#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,x,y) for(decay<decltype(y)>::type i=(x),_##i=(y);i<=_##i;++i)
#define FORD(i,x,y) for(decay<decltype(x)>::type i=(x),_##i=(y);i>=_##i;--i)
#define mem(f,x) memset(f,x,sizeof(f))
//=======================================================
void hin(int &res){
    char ch;
    bool flag=false;
    while (!isdigit(ch=getchar()))
        if (ch=='-') flag=true;
    for (res=ch-'0';isdigit(ch=getchar());res=res*10+ch-'0');
    if (flag) res=-res;
}
void hout(int x){
    if (x<0){
        putchar('-');
        x=-x;
    }
    if (x>9) hout(x/10);
    putchar(x%10+'0');
}
int main(){
    int n;
    hin(n);
    hout(n);
}
