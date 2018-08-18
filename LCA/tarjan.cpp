#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,x,y) for(decay<decltype(y)>::type i=(x),_##i=(y);i<=_##i;++i)
#define FORD(i,x,y) for(decay<decltype(x)>::type i=(x),_##i=(y);i>=_##i;--i)
#define mem(f,x) memset(f,x,sizeof(f))
//=======================================================
struct node_map{
    long t;
    node_map *next;
};
struct node_ls{
    long t;
    node_ls *next;
    long link;
};
node_map* head[500005];
node_ls* qhead[500005];
bool st[500005];
long fa[500005];
long n,m,root;
long ans[500005];
void hin(long &res){
    char ch;
    bool flag=false;
    while (!isdigit(ch=getchar()))
        if (ch=='-') flag=true;
    for (res=ch-'0';isdigit(ch=getchar());res=res*10+ch-'0');
    if (flag) res=-res;
}
void hout(long x){
    if (x<0){
        putchar('-');
        x=-x;
    }
    if (x>9) hout(x/10);
    putchar(x%10+'0');
}
void add_map(long a,long b){
    node_map *p;
    p=new node_map;
    p->t=b;
    p->next=head[a];
    head[a]=p;
    p=new node_map;
    p->t=a;
    p->next=head[b];
    head[b]=p;
}
void add_ls(long a,long b){
    node_ls *p;
    p=new node_ls;
    p->t=b;
    p->next=qhead[a];
    qhead[a]=p;
    p=new node_ls;
    p->t=a;
    p->next=qhead[b];
    qhead[b]=p;
}
long findfa(long u){
    if (u==fa[u]) return u;
    else {
        fa[u]=findfa(fa[u]);
        return fa[u];
    }
}
void dfs(long u){
    st[u]=true;
    fa[u]=u;
    for (auto p=head[u];p;p=p->next){
        if (!st[p->t]){
            dfs(p->t);
            fa[p->t]=u;
        }
    }
    for (auto p=qhead[u];p;p=p->next){
        if (st[p->t]){
            ans[p->link]=findfa(p->t);
        }
    }
}
int main(){
    mem(head,0);mem(qhead,0);
    hin(n);hin(m);hin(root);
    long a,b;
    FOR(i,1,n-1){
        hin(a);hin(b);
        add_map(a,b);
    }
    FOR(i,1,m){
        hin(a);hin(b);
        add_ls(a,b);
        qhead[a]->link=i;
        qhead[b]->link=i;
    }
    mem(st,false);
    fa[root]=root;
    dfs(root);
    FOR(i,1,m) {
        hout(ans[i]);
        printf("\n");
    }
    return 0;
}
