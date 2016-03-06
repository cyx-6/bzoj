#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

const int N=3030;
const int K=15;
const double P=M_PI;

struct C{
	double x,y,r;
};

struct E{
	int t,next;
};

C a[N];
E e[N];
int f[N][K];
int d[N],h[N];
double s[N][N][2];
double g[N],t[N];
int n,m,i,j,k,u,v,w;
double x,y,p,q,ans,l,r,b,c;

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(E){v,h[u]};
	h[u]=h[0];
}

double len(double x,double y,int k,double r){
	if(k){
		if(x<y)return (2-(y-x)/P)*r;
		else return (x-y)/P*r;
	}else{
		if(x<y)return (y-x)/P*r;
		else return (2-(x-y)/P)*r;
	}
}

void dfs(int u,int v){
	int i,w;
	double l,r,x,y;
	d[u]=d[v]+1;
	for(i=1;i<K;i++)f[u][i]=f[f[u][i-1]][i-1];
	if(v)t[u]=atan2(a[u].y-a[v].y,a[u].x-a[v].x);
	w=f[v][0];
	if(w){
		x=atan2(a[u].y-a[v].y,a[u].x-a[v].x);
		y=atan2(a[w].y-a[v].y,a[w].x-a[v].x);
		l=len(x,y,1,a[v].r);
		r=len(x,y,0,a[v].r);
		for(i=1;i<=n;i++)
			if(i!=u && i!=v){
				s[u][i][1]=s[v][i][0]+l;
				s[u][i][0]=s[v][i][1]+r;
			}
	}
	for(i=h[u];i!=-1;i=e[i].next)
		dfs(e[i].t,u);
}

int jump(int u,int del){
	int i;
	for(i=0;i<K;i++)
		if(del&(1<<i))u=f[u][i];
	return u;
}

int lca(int u,int v){
	int i;
	if(d[u]>d[v])swap(u,v);
	v=jump(v,d[v]-d[u]);
	for(i=K-1;~i;i--)
		if(f[u][i]!=f[v][i]){
			u=f[u][i];
			v=f[v][i];
		}
	return u==v?u:f[u][0];
}

double solve(int t1,int t2){
	double ans;
	w=lca(u,v);
	ans=0;
	if(u==w)b=x;		
	else{
		ans+=len(x,atan2(a[f[u][0]].y-a[u].y,a[f[u][0]].x-a[u].x),t1,a[u].r)+s[u][w][t1^1];
		b=t[jump(u,d[u]-d[w]-1)];
	}
	if(v==w)c=y;		
	else{
		ans+=len(y,atan2(a[f[v][0]].y-a[v].y,a[f[v][0]].x-a[v].x),t2,a[v].r)+s[v][w][t2^1];
		c=t[jump(v,d[v]-d[w]-1)];
	}
	ans+=len(b,c,t1^((d[u]-d[w])&1),a[w].r);
	return ans;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++)scanf("%lf",&g[i]);
	g[0]=1e5;
	memset(h,-1,sizeof(h));
	for(i=1;i<=m;i++){
		scanf("%lf%lf%d%d",&a[i].x,&a[i].y,&j,&f[i][0]);
		a[i].r=g[j];
		if(f[i][0])addedge(f[i][0],i);
	}
	n=m;
	m=k;
	dfs(1,0);
	for(i=1;i<=m;i++){
		scanf("%d%lf%d%lf",&u,&x,&v,&y);
		if(x>=P)x-=P*2;
		if(y>=P)y-=P*2;
		w=lca(u,v);
		ans=1e10;
		if((d[u]&1)^(d[v]&1)){
			ans=min(ans,solve(1,1));
			ans=min(ans,solve(0,0));
		}else{
			ans=min(ans,solve(1,0));
			ans=min(ans,solve(0,1));
		}
		printf("%.0lf\n",ans);
	}
	return 0;
}
