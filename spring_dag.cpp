#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
ll Rd(){
	ll ans=0;bool fh=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') fh=1; c=getchar();}
	while(c>='0'&&c<='9') ans=ans*10+c-'0',c=getchar();
	if(fh) ans=-ans;
	return ans;
}

const ll INF=1E18;
const ll PTN=1E6+5,EDN=2E6+5;
struct Edge{
	ll u,v;bool w;ll nxt;
}edge[EDN];
ll N,graM,last[PTN]; 
void GraphInit(){graM=0;for(ll i=0;i<PTN;i++) last[i]=0;}
void AddBscEdge(ll u,ll v,bool w){
	edge[++graM]=(Edge){u,v,w,last[u]};
	last[u]=graM;
}
void AddUnEdge(ll u,ll v,bool w){
	AddBscEdge(v,u,w); 
}
ll ptW[PTN];
ll f[PTN][2];
ll F(ll u,bool typ){
	if(f[u][typ]!=-1) return f[u][typ];
	f[u][typ]=-INF;
	for(ll i=last[u];i!=0;i=edge[i].nxt){
		ll v=edge[i].v;bool w=edge[i].w;
		f[u][typ]=max(f[u][typ],typ*ptW[u]+F(v,typ^w));
	}
	return f[u][typ];
}
ll ST=1;
void Solve(){
	for(ll u=1;u<=N;u++) f[u][0]=f[u][1]=-1;
	f[ST][0]=0;
	ll ans=-INF;
	for(ll u=1;u<=N;u++)
		ans=max(ans,max(F(u,0),F(u,1)));
	printf("%lld",ans);
}
int main(){
	freopen("spring.in","r",stdin);
	freopen("spring_dag.out","w",stdout);
	GraphInit();
	N=Rd();ll m=Rd();
	for(ll u=1;u<=N;u++) ptW[u]=Rd();
	while(m--){
		ll u=Rd(),v=Rd();bool w=Rd();
		AddUnEdge(u,v,w); 
	}
	Solve();
	return 0;
}

