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

int main(){
	freopen("spring.in","w",stdout);
	srand(time(NULL));
	ll N=4E5,M=7E5;
	//ll N=5,M=7;
	printf("%lld %lld\n",N,M);
	for(ll i=1;i<=N;i++) printf("%lld ",Random()%ll(1E9));
	printf("\n");
	for(ll i=1;i<=M;i++){
		ll u=Random()%N+1,v=Random()%N+1,w=Random()%2;
		printf("%lld %lld %lld\n",u,v,w);
	}
	return 0;
}

