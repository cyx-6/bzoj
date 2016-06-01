#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 5050
#define M 10100

struct edge{
	int t,next;
};

edge e[M];
int h[N],p[N],q[N],d[N],c[N];
ll f[N],g[M];
int n,m,i,j,k,x,y,u,v,w;
ll ans;

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void dfs(int cur,int pre){
	int i;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=pre){
			dfs(e[i].t,cur);
			if(d[e[i].t]+1>d[cur]){
				c[cur]=e[i].t;
				d[cur]=d[e[i].t]+1;
			}
		}
}

void dp(int cur,int pre){
	int i,j,tar;
	x++;
	p[cur]=x;
	y+=2;
	if(c[cur]){
		dp(c[cur],cur);
		q[cur]=q[c[cur]]-1;
	}else q[cur]=y;
	ans+=g[q[cur]];
	f[p[cur]]=1;
	for(i=h[cur];i!=-1;i=e[i].next){
		tar=e[i].t;
		if(tar!=pre && tar!=c[cur]){
			dp(tar,cur);
			for(j=0;j<=d[tar];j++){
				if(j)ans+=g[q[tar]-j]*f[p[cur]+j-1];
				ans+=f[p[tar]+j]*g[q[cur]-j-1];
			}
			for(j=0;j<=d[tar];j++){
				g[q[cur]-j-1]+=f[p[cur]+j+1]*f[p[tar]+j];
				if(j<d[tar])g[q[cur]-j]+=g[q[tar]-j-1];
				f[p[cur]+j+1]+=f[p[tar]+j];
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs(1,0);
	dp(1,0);
	printf("%lld\n",ans);
	return 0;
}
