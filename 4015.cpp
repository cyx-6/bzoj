#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=256;
const int M=512;
const int P=10007;

int a[N],b[M],next[M];
int f[N][N];
int s[N],g[N],h[N];
int n,m,i,j,k,t,u,v,w,ans;

void addedge(int u,int v){
	a[0]++;
	b[a[0]]=v;
	next[a[0]]=a[u];
	a[u]=a[0];
}

void dfs(int cur,int pre){
	int i;
	s[cur]=1;
	g[cur]=0;
	for(i=a[cur];i!=-1;i=next[i])
		if(b[i]!=pre){
			dfs(b[i],cur);
			s[cur]+=s[b[i]];
			g[cur]=max(g[cur],s[b[i]]);
		}
	g[cur]=max(g[cur],n-s[cur]);
	m=min(m,g[cur]);
}

void calc(int cur,int pre){
	int i,j,k;
	for(i=1;i<=n;i++)f[cur][i]=0;
	f[cur][1]=1;
	s[cur]=1;
	for(i=a[cur];i!=-1;i=next[i])
		if(b[i]!=pre){
			calc(b[i],cur);
			s[cur]+=s[b[i]];
			for(j=s[cur];j;j--)
				for(k=1;k<j;k++){
					f[cur][j]+=f[b[i]][k]*f[cur][j-k]%P;
					f[cur][j]%=P;
				}
		}
}

void solve(int p){
	int i,j,k,u,v;
	calc(p,0);
	ans=0;
	for(i=1;i<=n;i++){
		ans+=f[p][i];
		ans%=P;
	}
	for(i=a[p];i!=-1;i=next[i]){
		for(j=0;j<=n;j++)h[j]=0;
		h[1]=1;
		for(j=a[p];j!=-1;j=next[j])
			if(i!=j)
				for(u=s[p]-s[b[i]];u;u--)
					for(v=1;v<u;v++){
						h[u]+=f[b[j]][v]*h[u-v]%P;
						h[u]%=P;
					}
		for(j=1;j<=n;j++){
			h[j]+=h[j-1];
			h[j]%=P;
		}
		for(j=1;j<=s[b[i]];j++){
			ans+=P-f[b[i]][j]*h[j]%P;
			ans%=P;
		}
	}
}

void solve(int p,int q){
	int i;
	calc(p,q);
	calc(q,p);
	ans=0;
	for(i=1;i<=n;i++){
		ans+=f[p][i]*f[q][i]%P;
		ans%=P;
	}
}

int main(){
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		scanf("%d",&n);
		memset(a,-1,sizeof(a));
		for(j=1;j<n;j++){
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		m=n;
		dfs(1,0);
		u=v=0;
		for(j=1;j<=n;j++)
			if(g[j]==m){
				if(!u)u=j;
				else v=j;
			}
		if(!v)solve(u);
		else solve(u,v);
		printf("Case %d: %d\n",i,ans);
	}
	return 0;
}
