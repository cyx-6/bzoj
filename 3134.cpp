#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 20
#define M 10

ll f[N][M][M][2];
int a[N];
ll l,r;

ll solve(ll n){
	int i,j,k,m,u,v,w;
	ll ans;
	if(n<M)return n+1;
	m=0;
	while(n){
		m++;
		a[m]=n%M;
		n/=M;
	}
	memset(f,0,sizeof(f));
	for(i=0;i<M;i++)
		for(j=0;j<M;j++)
			f[2][i][j][i>a[2] || (i==a[2] && j>a[1])]=i!=j;
	ans=M;
	for(i=2;i<=m;i++){
		for(u=0;u<M;u++)
			for(v=0;v<M;v++)
				for(w=0;w<M;w++)
					for(k=0;k<2;k++)
						if(w!=u && w!=v)
							f[i+1][w][u][(k && w==a[i+1]) || w>a[i+1]]+=f[i][u][v][k];
		for(u=1;u<M;u++)
			for(v=0;v<M;v++)
				for(k=0;k<=(i!=m);k++)
					ans+=f[i][u][v][k];
	}
	return ans;
}

int main(){
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",solve(r)-solve(l-1));
	return 0;
}
