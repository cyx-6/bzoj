#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 200200
#define M 800800
#define K 20

struct P{
	ll x,y;
};

typedef P V;

V operator - (P u,P v){
	return (V){u.x-v.x,u.y-v.y};
}

double slope(V v){
	return (double)v.y/v.x;
}

struct D{
	int l,r,t;
	P *s;
};

struct E{
	int t,next;
	ll d;
};

struct C{
	ll p,q,d;
};

D a[M];
E e[N];
C c[N];
int h[N],t[N],s[N],p[N],b[N];
int f[N][K];
ll d[N],g[N];
int n,m,i,j,k,u,v,w;
ll dis;

void addedge(int u,int v,ll w){
	h[0]++;
	e[h[0]]=(E){v,h[u],w};
	h[u]=h[0];
}

void dfs(int cur){
	int i;
	for(i=1;i<K;i++)f[cur][i]=f[f[cur][i-1]][i-1];
	s[cur]=1;
	for(i=h[cur];i!=-1;i=e[i].next){
		d[e[i].t]=d[cur]+e[i].d;
		b[e[i].t]=b[cur]+1;
		dfs(e[i].t);
		s[cur]+=s[e[i].t];
	}
}

void dfs(int cur,int top){
	int i,k;
	m++;
	p[cur]=m;
	t[cur]=top;
	k=0;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(s[e[i].t]>s[k])k=e[i].t;
	if(k)dfs(k,top);
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=k)dfs(e[i].t,e[i].t);
}

void build(int cur,int l,int r){
	int mid;
	a[cur].l=l;
	a[cur].r=r;
	a[cur].t=0;
	a[cur].s=(P *)malloc(sizeof(P)*(r-l+3));
	if(l==r)return;
	mid=(l+r)>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
}

int jump(int cur,int del){
	int i;
	for(i=0;i<K;i++)
		if(del&(1<<i))cur=f[cur][i];
	return cur;
}

void add(int cur,P p){
	int t;
	t=a[cur].t;
	while((t && p.x<=a[cur].s[t].x) || (t>1 && slope(a[cur].s[t]-a[cur].s[t-1])>=slope(p-a[cur].s[t])))t--;
	t++;
	a[cur].s[t]=p;
	a[cur].t=t;
}

P ask(int cur,ll k){
	int l,r,mid;
	if(a[cur].t==1)return a[cur].s[a[cur].t];
	l=1;
	r=a[cur].t-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(slope(a[cur].s[mid+1]-a[cur].s[mid])>=k)r=mid-1;
		else l=mid+1;
	}
	return a[cur].s[l];
}

void ask(int cur,int l,int r,int i){
	int mid;
	P p;
	if(l<=a[cur].l && r>=a[cur].r){
		p=ask(cur,c[i].p);
		g[i]=min(g[i],p.y-p.x*c[i].p);
		return;
	}
	mid=(a[cur].l+a[cur].r)>>1;
	if(l<=mid)ask(cur<<1,l,r,i);
	if(mid<r)ask(cur<<1|1,l,r,i);
}

void add(int cur,int tar,int i){
	int mid;
	add(cur,(P){d[i],g[i]});
	if(a[cur].l==a[cur].r)return;
	mid=(a[cur].l+a[cur].r)>>1;
	if(tar<=mid)add(cur<<1,tar,i);
	else add(cur<<1|1,tar,i);
}

void ask(int i){
	int cur,l,r,mid,k;
	for(cur=f[i][0];cur && d[i]-d[t[cur]]<=c[i].d;cur=f[t[cur]][0])
		ask(1,p[t[cur]],p[cur],i);
	if(cur){
		l=1;
		r=b[cur]-b[t[cur]]+1;
		while(l<=r){
			mid=(l+r)>>1;
			k=jump(cur,mid-1);
			if(d[i]-d[k]<=c[i].d)l=mid+1;
			else r=mid-1;
		}
		k=jump(cur,r-1);
		if(d[i]-d[k]<=c[i].d)ask(1,p[k],p[cur],i);
	}
	g[i]+=d[i]*c[i].p+c[i].q;
}

void solve(int cur){
	int i;
	ask(cur);
	add(1,p[cur],cur);
	for(i=h[cur];i!=-1;i=e[i].next)
		solve(e[i].t);
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(i=2;i<=n;i++){
		scanf("%d%lld%lld%lld%lld",&f[i][0],&dis,&c[i].p,&c[i].q,&c[i].d);
		addedge(f[i][0],i,dis);
		g[i]=1e18;
	}
	dfs(1);
	m=0;
	dfs(1,1);
	build(1,1,n);
	solve(1);
	for(i=2;i<=n;i++)printf("%lld\n",g[i]);
	return 0;
}
