#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,x,y) for(decay<decltype(y)>::type i=(x),_##i=(y);i<=_##i;++i)
#define FORD(i,x,y) for(decay<decltype(x)>::type i=(x),_##i=(y);i>=_##i;--i)
#define mem(f,x) memset(f,x,sizeof(f))
//=======================================================
long r[10005];
int fa[10005],low[10005],dnf[10005];
bool st[10005],hst[10005];
vector<vector<int>> mp(10005);
vector<vector<int>> rmp(10005);
vector<int> hstack;
long n,m;
long tim;
long dp[10005];
long ans;
long dfs(int u){
    st[u]=true;
    long tmp=0;
    int i;
    for (auto &j:rmp[u]){
        i=fa[j];
        if (!st[i]) tmp=max(tmp,dfs(i));
        else tmp=max(tmp,dp[i]);
    }
    dp[u]=r[u]+tmp;
    return dp[u];
}
void merg(int x,int y){
    if (x==y) return;
    r[x]+=r[y];
    fa[y]=x;
    mp[x].insert(mp[x].end(),mp[y].begin(),mp[y].end());
}
void tarjan(int u){
    int t;
    st[u]=true;
    hstack.push_back(u);
    hst[u]=true;
    tim++;
    dnf[u]=low[u]=tim;
    for (auto &t:mp[u]){
        if (!st[t]){
            tarjan(t);
            low[u]=min(low[u],low[t]);
        }
        else if (hst[t])
            low[u]=min(low[u],dnf[t]);
            //个人认为low[u]=min(low[u],low[t])也可以（？？？
    }
    if (dnf[u]==low[u]){
        fa[u]=u;
        do{
            t=hstack.back();
            hst[t]=false;
            //cout<<u<<":"<<t<<endl;
            merg(u,t);
            hstack.pop_back();
        }while(t!=u);
    }
}
int main(){
    cin>>n>>m;
    FOR(i,1,n) cin>>r[i];
    int a,b;
    FOR(i,1,m){
        cin>>a>>b;
        mp[a].push_back(b);
    }
    mem(st,false);mem(hst,false);
    hstack.clear();
    int t=1;
    tim=0;
    while (t<=n){
        if (!st[t]) tarjan(t);
        t++;
    }
    /*FOR(i,1,n){
        cout<<i<<":";
        for (auto &t:mp[fa[i]]) cout<<t<<" ";
        cout<<endl;
    }*/
    //inverse map
    FOR(i,1,n){
        if (fa[i]!=i) continue;
        for (auto &j:mp[i]){
            if (fa[j]==i) continue;
            rmp[fa[j]].push_back(i);
        }
    }
    /*FOR(i,1,n)
        if (fa[i]==i){
            cout<<i<<":";
            for (auto &j:rmp[i]) cout<<j<<" ";
            cout<<endl;
        }*/
    //dp
    mem(st,false);
    ans=0;
    FOR(i,1,n){
        if (st[fa[i]]) continue;
        ans=max(ans,dfs(fa[i]));
    }
    cout<<ans<<endl;
}
