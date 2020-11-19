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
ll N;
struct Edge{ll u,v;bool w;ll nxt;};
struct Graph{
	Edge edge[EDN];
	ll graM,last[PTN];
	void GraphInit(){graM=0;for(ll i=0;i<PTN;i++) last[i]=0;}
	void AddBscEdge(ll u,ll v,bool w){
		edge[++graM]=(Edge){u,v,w,last[u]};
		last[u]=graM;
	}
}G1;

ll cSize[PTN];
ll bel[PTN],cN,rps[PTN]; //belong, number of components, representative vertax of the component
ll dfn[PTN],low[PTN],dN;
ll stk[PTN],tp;bool isI[PTN];
void Tarjan(ll u){
	dfn[u]=low[u]=++dN;
	stk[++tp]=u;isI[u]=1;
	for(ll i=G1.last[u];i!=0;i=G1.edge[i].nxt){
		ll v=G1.edge[i].v;
		if(isI[v]){
			low[u]=min(low[u],dfn[v]);
		}else if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
	}
	if(dfn[u]==low[u]){
		rps[++cN]=u;cSize[cN]=0;ll t;
		do{
			t=stk[tp--];
			isI[t]=0;bel[t]=cN;
			cSize[cN]++;
		}while(t!=u);
	}
}

bool cTyp[PTN]; //component type (0: even; 1: odd)
ll col[PTN];
void ColDFS(ll u,bool color,ll curC){
	col[u]=color;
	for(ll i=G1.last[u];i!=0;i=G1.edge[i].nxt){
		ll v=G1.edge[i].v;bool w=G1.edge[i].w;
		if(bel[v]!=curC) continue;
		if(col[v]==-1) ColDFS(v,color^w,curC);
		else if((color^w)!=col[v]) cTyp[curC]=1; //odd component
	}
}

ll ST=1;
void Solve(){
	cN=0;dN=0;tp=0;for(ll i=1;i<=N;i++) dfn[i]=low[i]=0,bel[i]=0,isI[i]=0;
	Tarjan(ST);
	
	ll tcnt=0;
	for(ll i=1;i<=N;i++) if(bel[i]) tcnt++;
	cout<<"number of vertex: "<<tcnt<<endl; 
	cout<<"number of components: "<<cN<<endl; 
	
	for(ll i=1;i<=N;i++) col[i]=-1;
	for(ll i=1;i<=cN;i++) cTyp[i]=0,ColDFS(rps[i],0,i);
	ll cnt[2]={0,0},mx[2]={0,0};
	for(ll i=1;i<=cN;i++){
		cnt[cTyp[i]]++;
		mx[cTyp[i]]=max(mx[cTyp[i]],cSize[i]);
	} 
	cout<<"number of odd components:  "<<cnt[1]<<" , max size: "<<mx[1]<<endl;
	cout<<"number of even components: "<<cnt[0]<<" , max size: "<<mx[0]<<endl;
}
int main(){
	freopen("spring.in","r",stdin);
	G1.GraphInit();
	N=Rd();ll m=Rd();
	for(ll u=1;u<=N;u++) Rd();
	while(m--){
		ll u=Rd(),v=Rd();bool w=Rd();
		G1.AddBscEdge(u,v,w); 
	}
	Solve();
	return 0;
}
