#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<queue>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
const ll RDMX=0x7fff;
ll Random(){
	return 1LL*rand()*(RDMX+1)+rand();
}
ll Random(ll a,ll b){
	return Random()%(b-a+1)+a;
}

const ll PTN=1E6+5;
ll st[PTN],ed[PTN],cN;
bool col[PTN];
int main(){
	freopen("spring.in","w",stdout);
	srand(time(NULL));
	ll N=4E5,M=7E5;
	//ll N=5,M=7;
	printf("%lld %lld\n",N,M);
	for(ll i=1;i<=N;i++) printf("%lld ",Random()%ll(1E9));
	printf("\n");
	
	ll cN=0;ed[0]=0;
	while(1){
		bool bomb=0;
		cN++;st[cN]=ed[cN-1]+1; ed[cN]=st[cN]+Random()%50; 
		if(ed[cN]>=N) ed[cN]=N,bomb=1;
		
		ll len=ed[cN]-st[cN]+1; 
		
		ll cTyp=Random()%2;
		if(cTyp==0){
			for(ll i=st[cN];i<=ed[cN];i++){
				col[i]=Random()%2;
			}
		}
		
		ll en=Random(len,len*2);
		if(M>=en) M-=en;
		else en=M,M=0;
		while(en--){
			ll u=Random(st[cN],ed[cN]),v=Random(st[cN],ed[cN]);
			printf("%lld %lld %lld\n",u,v,cTyp?(col[u]^col[v]):Random()%2);
		}
		
		if(bomb) break;
	}
	//ll t=M;
	while(M--){
		ll u=Random(2,cN),v=Random(1,u-1);
		swap(u,v);
		printf("%lld %lld %lld\n",Random(st[u],ed[u]),Random(st[v],ed[v]),Random()%2);
	}
	//cout<<t<<"#";
	return 0;
}
