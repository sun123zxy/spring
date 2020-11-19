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

const ll MXN=1E6+5;
ll ref[MXN];
int main(){
	freopen("spring.in","w",stdout);
	srand(time(NULL));
	ll N=5E5,M=10E5;
	//ll N=5,M=6;
	printf("%lld %lld\n",N,M);
	for(ll i=1;i<=N;i++) printf("%lld ",Random()%ll(1E9));
	printf("\n");
	for(ll i=1;i<=N;i++) ref[i]=i;
	random_shuffle(ref+1,ref+min(10LL,N)+1);
	for(ll i=1;i<=M;i++){
		ll u=Random()%(N-1)+2,v=Random()%(u-1)+1,w=Random()%2;
		printf("%lld %lld %lld\n",ref[v],ref[u],w);
	}
	return 0;
}

