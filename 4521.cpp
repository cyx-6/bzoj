#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 13
#define M 10

ll f[N][M][M][2][2][2][2];
int a[N];
int n,m,i,j,k;
ll l,r;

ll solve(ll x){
	int n,m,i,j,k,u,v,w,p,q,t;
	ll ans;
	n=0;
	while(x){
		n++;
		a[n]=x%M;
		x/=M;
	}
	if(n<11)return 0;
	memset(f,0,sizeof(f));
	for(i=0;i<M;i++)
		for(j=0;j<M;j++)
			f[2][i][j][0][i==4 || j==4][i==8 || j==8][i>a[2] || (i==a[2] && j>a[1])]=1;
	for(i=3;i<=n;i++)
		for(u=(i==n);u<M;u++)
			for(v=0;v<M;v++)
				for(w=0;w<M;w++)
					for(t=0;t<=1;t++)
						for(p=0;p<=1;p++)
							for(q=0;q<=1;q++)
								for(k=0;k<=1;k++){
									if((v==4 || w==4) && !p)continue;
									if((v==8 || w==8) && !q)continue;
									f[i][u][v][t || (u==v && v==w)][u==4 || p][u==8 || q][(k && a[i]==u) || u>a[i]]+=f[i-1][v][w][t][p][q][k];
								}
	ans=0;
	for(i=1;i<M;i++)
		for(j=0;j<M;j++){
			if(i==4 && j==8)continue;
			if(i==8 && j==4)continue;
			ans+=f[n][i][j][1][0][1][0]+f[n][i][j][1][1][0][0]+f[n][i][j][1][0][0][0];
		}
	return ans;
}

int main(){
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",solve(r)-solve(l-1));
	return 0;
}
