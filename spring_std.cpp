/*
°×ÒøÖ®´º (spring) std
by sun123zxy

PS: If you got a runtime error, "-Wl,--stack=123456789"
*/
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
	void AddUnEdge(ll u,ll v,bool w){
		AddBscEdge(v,u,w); 
	}
	ll ptW[PTN][2]; //value Youmu can get when reaching the vertex with state 0/1
}G1,G2;
ll Id(ll cId,bool col){
	return 2*cId-col;
}

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
		rps[++cN]=u;ll t;
		do{
			t=stk[tp--];
			isI[t]=0;bel[t]=cN;
		}while(t!=u);
	}
}
bool cTyp[PTN]; //component type (0: even; 1: odd)
ll col[PTN];
void ColDFS(ll u,bool color,ll curC){
	col[u]=color;
	G2.ptW[Id(curC,color)][1]+=G1.ptW[u][1]; //calculate values for each group (even component)
	for(ll i=G1.last[u];i!=0;i=G1.edge[i].nxt){
		ll v=G1.edge[i].v;bool w=G1.edge[i].w;
		if(bel[v]!=curC) continue;
		if(col[v]==-1) ColDFS(v,color^w,curC);
		else if((color^w)!=col[v]) cTyp[curC]=1; //odd component
	}
}
void BuildG2(){
	for(ll i=1;i<=G1.graM;i++){
		ll u=G1.edge[i].u,v=G1.edge[i].v;bool w=G1.edge[i].w;
		ll cU=bel[u],cV=bel[v];
		if(!cU||!cV) continue; //edges Youmu can never reach
		if(cU==cV) continue;   //edges inside the component
		ll myV=Id(cV,col[v]*(cTyp[cV]^1));
		if(cTyp[cU]==1){
			G2.AddUnEdge(Id(cU,0),myV,w);
			G2.AddUnEdge(Id(cU,0),myV,w^1);
		}else{
			G2.AddUnEdge(Id(cU,col[u]),myV,w);     //from this group
			G2.AddUnEdge(Id(cU,col[u]^1),myV,w^1); //from the other group
		}
	}
}
ll f[PTN][2];
ll F(ll u,bool typ){
	if(f[u][typ]!=-1) return f[u][typ];
	f[u][typ]=-INF; 
	for(ll i=G2.last[u];i!=0;i=G2.edge[i].nxt){
		ll v=G2.edge[i].v;bool w=G2.edge[i].w;
		f[u][typ]=max(f[u][typ],G2.ptW[u][typ]+F(v,typ^w));
	}
	return f[u][typ];
}
ll ST=1;
void Solve(){
	cN=0;dN=0;tp=0;for(ll i=1;i<=N;i++) dfn[i]=low[i]=0,bel[i]=0,isI[i]=0;
	Tarjan(ST); //Only need to get components Youmu can reach
	G2.GraphInit();
	for(ll i=1;i<=N;i++) col[i]=-1;
	for(ll i=1;i<=cN;i++) cTyp[i]=0,ColDFS(rps[i],0,i);
	for(ll i=1;i<=cN;i++){
		if(cTyp[i]==1){ //odd component
			G2.ptW[Id(i,0)][0]=G2.ptW[Id(i,0)][1]+=G2.ptW[Id(i,1)][1]; //an odd component enjoys all the values
			G2.ptW[Id(i,1)][0]=G2.ptW[Id(i,1)][1]=0; //abandon Id(i,1)
		}else{ //even component
			G2.ptW[Id(i,0)][0]=G2.ptW[Id(i,1)][1];
			G2.ptW[Id(i,1)][0]=G2.ptW[Id(i,0)][1];
		}
	}
	BuildG2();
	
	for(ll i=1;i<=2*N;i++) f[i][0]=f[i][1]=-1;
	ll myST=Id(bel[ST],col[ST]*(cTyp[bel[ST]]^1));
	f[myST][0]=G2.ptW[myST][0];
	ll ans=-INF;
	for(ll i=1;i<=2*N;i++)
		ans=max(ans,max(F(i,0),F(i,1)));
	printf("%lld",ans);
}
int main(){
	freopen("spring.in","r",stdin);
	freopen("spring_std.out","w",stdout);
	G1.GraphInit();
	N=Rd();ll m=Rd();
	for(ll u=1;u<=N;u++) G1.ptW[u][1]=Rd();
	while(m--){
		ll u=Rd(),v=Rd();bool w=Rd();
		G1.AddBscEdge(u,v,w); 
	}
	Solve();
	return 0;
}
