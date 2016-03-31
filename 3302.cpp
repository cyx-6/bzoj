#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 50500
#define M 101000
#define D 202000

struct edge{
	int t,next;
};

struct data{
	int l,r;
	ll s,d;
};

data a[D];
edge e[M];
int h[N],f[N],d[N],p[N],b[N],g[N],l[N],r[N];
ll s[N],t[N],c[N];
ll ans,sum;
int n,m,i,j,k,u,v,w,tar;

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void add(int cur,ll del){
	a[cur].s+=del;
	a[cur].d+=del;
}

void up(int cur){
	a[cur].s=max(a[cur<<1].s,a[cur<<1|1].s);
}

void down(int cur){
	if(a[cur].d){
		add(cur<<1,a[cur].d);
		add(cur<<1|1,a[cur].d);
		a[cur].d=0;
	}
}

void build(int cur,int l,int r){
	int mid;
	a[cur].l=l;
	a[cur].r=r;
	if(l==r){
		a[cur].s=s[p[l]];
		return;
	}
	mid=(l+r)>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	up(cur);
}

void dfs1(int cur){
	int i;
	g[cur]=1;
	for(i=h[cur];i!=-1;i=e[i].next){
		tar=e[i].t;
		if(tar!=f[cur]){
			f[tar]=cur;
			d[tar]=d[cur]+1;
			dfs1(tar);
			tar=e[i].t;
			t[cur]+=t[tar]+s[tar];
			s[cur]+=s[tar];
			g[cur]+=g[tar];
		}
	}
}

void dfs2(int cur){
	int i;
	k++;
	l[cur]=k;
	p[k]=cur;
	if(f[cur])c[cur]=c[f[cur]]+sum-(s[cur]<<1);
	tar=0;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=f[cur] && g[e[i].t]>g[tar])tar=e[i].t;
	if(tar){
		b[tar]=b[cur];
		dfs2(tar);
	}
	for(i=h[cur];i!=-1;i=e[i].next){
		tar=e[i].t;
		if(!b[tar]){
			b[tar]=tar;
			dfs2(tar);			
		}
	}
	r[cur]=k;
}

void add(int cur,int l,int r,ll del){
	int mid;
	if(l<=a[cur].l && r>=a[cur].r){
		add(cur,del);
		return;
	}
	down(cur);
	mid=(a[cur].l+a[cur].r)>>1;
	if(l<=mid)add(cur<<1,l,r,del);
	if(mid<r)add(cur<<1|1,l,r,del);
	up(cur);
}

int ask(int cur,int l,int r,ll sum){
	int mid,k;
	if(a[cur].s<<1<sum || l>r)return 0;
	if(a[cur].l==a[cur].r)return p[a[cur].l];
	down(cur);
	mid=(a[cur].l+a[cur].r)>>1;
	k=0;
	if(mid<r)k=ask(cur<<1|1,l,r,sum);
	if(k)return k;
	if(l<=mid)k=ask(cur<<1,l,r,sum);
	return k;
}

int lca(int u,int v){
	while(b[u]!=b[v]){
		if(d[b[u]]>d[b[v]])swap(u,v);
		v=f[b[v]];
	}
	return d[u]<d[v]?u:v;
}

int len(int u,int v){
	return d[u]+d[v]-(d[lca(u,v)]<<1);
}

void solve(int u,int v){
	ll dis;
	int root,i;
	for(i=u;i;i=f[b[i]])add(1,l[b[i]],l[i],-s[v]);
	root=ask(1,r[v]+1,n,sum-s[v]);
	if(!root)root=ask(1,1,l[v]-1,sum-s[v]);
	dis=c[root]-t[v]-s[v]*len(v,root);
	root=ask(1,l[v],r[v],s[v]);
	dis+=c[root]-c[u]+t[v]+s[v]-(sum-s[v])*len(root,u);
	ans=min(ans,dis);
	for(i=u;i;i=f[b[i]])add(1,l[b[i]],l[i],s[v]);
}

void dfs(int cur,int pre){
	int i;
	if(pre)solve(pre,cur);
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=pre)dfs(e[i].t,cur);
}

int main(){
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	for(i=1;i<=n;i++)scanf("%lld",&s[i]);
	m=n>>1;
	dfs1(m);
	sum=s[m];
	c[m]=t[m];
	b[m]=m;
	dfs2(m);
	build(1,1,n);
	ans=1e15;
	dfs(m,0);
	printf("%lld\n",ans);
	return 0;
}
