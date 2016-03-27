#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=32;
const int M=64;

struct edge{
	int t,next;
};

edge e[M];
bool c[N][N];
long long f[N][N];
int h[N],a[N],p[N];
int n,m,i,j,k,u,v,w;
long long ans,sum;

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void dfs(int cur,int pre){
	int i,tar,u,v;
	long long sum;
	for(i=1;i<=m;i++)f[cur][i]=1;
	for(i=h[cur];i!=-1;i=e[i].next){
		tar=e[i].t;
		if(tar!=pre){
			dfs(tar,cur);
			for(u=1;u<=m;u++){
				sum=0;
				for(v=1;v<=m;v++)
					if(c[a[u]][a[v]])sum+=f[tar][v]; 
				f[cur][u]*=sum;
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		c[u][v]=c[v][u]=true;
	}
	memset(h,-1,sizeof(h));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	for(i=1;i<=n+1;i++)p[i]=1<<(i-1);
	for(i=1;i<p[n+1];i++){
		sum=m=0;
		for(j=1;j<=n;j++)
			if(i&p[j]){
				m++;
				a[m]=j;
			}
		dfs(1,0);
		for(j=1;j<=m;j++)sum+=f[1][j];
		ans+=sum*((n-m)&1?-1:1);
	}
	printf("%lld\n",ans);
	return 0;
}
