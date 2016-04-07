#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 300300

struct edge{
	int t,next;
};

edge e[N];
int h[N],s[N],f[N],g[N],l[N],r[N];
ll a[N],b[N],c[N],t[N],q[N],d[N],p[N];
char ch[2];
int n,m,i,j,k,u,v,w;

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void add(ll *a,int x,ll y){
	for(;x<=n;x+=x&(-x))a[x]+=y;
}

ll sum(ll *a,int x){
	ll y;
	y=0;
	for(;x;x-=x&(-x))y+=a[x];
	return y;
}

void dfs1(int cur,int pre){
	int i;
	f[cur]=pre;
	s[cur]=1;
	c[cur]=p[cur];
	for(i=h[cur];i!=-1;i=e[i].next){
		dfs1(e[i].t,cur);
		s[cur]+=s[e[i].t];
		c[cur]+=c[e[i].t];
		q[cur]-=(ll)s[e[i].t]*(s[e[i].t]-1)>>1;
	}
	q[cur]+=(ll)s[cur]*(s[cur]-1)>>1;
}

void dfs2(int cur,int top){
	int i;
	t[cur]=top;
	k++;
	l[cur]=k;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(s[e[i].t]>s[g[cur]])g[cur]=e[i].t;
	if(g[cur])dfs2(g[cur],top);
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=g[cur]){
			dfs2(e[i].t,e[i].t);
			d[cur]-=c[e[i].t]*s[e[i].t];
		}
	r[cur]=k+1;
	add(a,l[cur],c[cur]);
	add(a,l[cur]+1,-c[cur]);
}

void add(int cur,ll del){
	int top;
	for(;cur;cur=f[top]){
		top=t[cur];
		add(a,l[top],del);
		add(a,l[cur]+1,-del);
		if(f[top])d[f[top]]-=del*s[top];
	}
}

double ask(int cur){
	ll ans;
	ans=sum(a,l[cur])*s[cur]+d[cur]-sum(a,l[g[cur]])*s[g[cur]]-p[cur];
	return (double)ans/q[cur]+sum(b,l[cur]);
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(i=2;i<=n;i++){
		scanf("%d",&k);
		addedge(k,i);
	}
	for(i=1;i<=n;i++)scanf("%lld",&p[i]);
	dfs1(1,0);
	k=0;
	dfs2(1,1);
	for(i=1;i<=m;i++){
		scanf("%s",ch);
		if(ch[0]=='S'){
			scanf("%d%d",&u,&v);
			add(u,v);
			p[u]+=v;
		}else if(ch[0]=='M'){
			scanf("%d%d",&u,&v);
			add(b,l[u],v<<1);
			add(b,r[u],-(v<<1));
			d[f[u]]-=(ll)v*s[u]*s[u];
			add(f[u],(ll)v*s[u]);
		}else{
			scanf("%d",&u);
			printf("%.6lf\n",ask(u));
		}
	}
	return 0;
}
