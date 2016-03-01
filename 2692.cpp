#include<cstdio>
#include<cstdlib>
#include<algorithm>

using namespace std;

#define ll long long
#define N 2048
#define M 1000000007

int f[N],g[N],h[N],x[N],y[N],z[N];
int c[N][N];
int n,i,j,t,u,v,ans;

int sum(int u,int v){
	int w;
	w=u+v;
	if(w>=M)w-=M;
	if(w<0)w+=M;
	return w;
}

int main(){
	c[0][0]=1;
	n=2000;
	for(i=1;i<=n;i++){
		c[i][0]=1;
		for(j=1;j<=i;j++)
			c[i][j]=sum(c[i-1][j],c[i-1][j-1]);
	}
	f[0]=g[0]=h[0]=x[0]=y[0]=z[0]=1;
	f[1]=g[1]=h[1]=x[1]=y[1]=z[1]=1;	
	for(i=2;i<=n;i++){
		for(j=1;j<i;j++){
			u=g[i-j];
			v=y[i-j];
			if(i-j==1)u=v=0;
			f[i]=sum(f[i],(ll)(f[i-j]+u)*g[j]%M*2%M*c[i-1][j-1]%M);
			x[i]=sum(x[i],(ll)(x[i-j]+v)*y[j]%M*c[i-1][j-1]%M);			
		}
		for(j=1;j<=i;j++){
			h[i]=sum(h[i],(ll)h[i-j]*f[j]%M*c[i-1][j-1]%M);
			z[i]=sum(z[i],(ll)z[i-j]*x[j]%M*c[i-1][j-1]%M);			
		}
		for(j=1;j<i;j++){
			g[i]=sum(g[i],(ll)h[j]*h[i-j]%M*c[i][j]%M);
			y[i]=sum(y[i],(ll)z[j]*z[i-j]%M*c[i][j]%M);			
		}
		g[i]=sum(g[i],(ll)(h[i]-f[i])*c[i][j]%M);
		y[i]=sum(y[i],(ll)(z[i]-x[i])*c[i][j]%M);		
	}
	scanf("%d",&t);
	for(;t;t--){
		scanf("%d",&n);
		if(n==1)printf("1\n");
		else{
			ans=sum(f[n],g[n]);
			ans=sum(ans,ans);
			ans=sum(ans,-x[n]);
			ans=sum(ans,-y[n]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
