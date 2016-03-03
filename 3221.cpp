#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 100100
#define M 200200
#define T 8008000

struct edge{
	int t,next;
};

struct data{
	int l,r;
	ll s,p,q;
};

struct seg{
	int l,r;
};

edge e[M];
data a[T];
int h[N],d[N],p[N],t[N],f[N],s[N],c[N];
int n,m,i,j,k,u,v,w,b,g;
ll ans,x,y;
char ch[2];

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void dfs1(int cur){
	int i;
	s[cur]=1;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=f[cur]){
			f[e[i].t]=cur;
			d[e[i].t]=d[cur]+1;
			dfs1(e[i].t);
			s[cur]+=s[e[i].t];
		}
}

void dfs2(int cur,int root){
	int i,c;
	k++;
	p[cur]=k;
	t[cur]=root;
	c=0;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=f[cur] && s[e[i].t]>s[c])c=e[i].t;
	if(c)dfs2(c,root);
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=f[cur] && e[i].t!=c)dfs2(e[i].t,e[i].t);
}

ll calc(ll u,ll v,int w){
	return u+v*(w-1);
}

ll sum(ll u,ll v,int l,int r){
	return (calc(u,v,l)+calc(u,v,r))*(r-l+1)>>1;
}

int lca(int u,int v){
	while(t[u]!=t[v]){
		if(d[t[u]]>d[t[v]])u=f[t[u]];
		else v=f[t[v]];
	}
	return d[u]<d[v]?u:v;
}

void modify(int &cur,int pre,int l,int r,int u,int v,ll p,ll q){
	int mid;
	k++;
	cur=k;
	a[cur]=a[pre];
	if(l==u && r==v){
		a[cur].p+=p;
		a[cur].q+=q;
		return;
	}
	a[cur].s+=sum(p,q,1,v-u+1);
	mid=(l+r)>>1;
	if(v<=mid)modify(a[cur].l,a[pre].l,l,mid,u,v,p,q);
	else if(u>mid)modify(a[cur].r,a[pre].r,mid+1,r,u,v,p,q);
	else{
		modify(a[cur].l,a[pre].l,l,mid,u,mid,p,q);
		modify(a[cur].r,a[pre].r,mid+1,r,mid+1,v,calc(p,q,mid+2-u),q);
	}
}

ll ask(int cur,int l,int r,int u,int v){
	int mid;
	ll s;
	if(!cur)return 0;
	s=sum(a[cur].p,a[cur].q,u-l+1,v-l+1);
	if(l==u && r==v)return s+a[cur].s;
	mid=(l+r)>>1;
	if(v<=mid)s+=ask(a[cur].l,l,mid,u,v);
	else if(u>mid)s+=ask(a[cur].r,mid+1,r,u,v);
	else{
		s+=ask(a[cur].l,l,mid,u,mid);
		s+=ask(a[cur].r,mid+1,r,mid+1,v);
	}
	return s;
}

void add(int x,int y,int k,ll u,ll v){
	int z,l,r,g;
	z=lca(x,y);
	l=1;
	r=d[x]+d[y]-(d[z]<<1)+1;
	while(t[x]!=t[y]){
		if(d[t[x]]>d[t[y]]){
			g=d[x]-d[t[x]]+l;
			modify(c[k],c[k],1,n,p[t[x]],p[x],calc(u,v,g),-v);
			l=g+1;
			x=f[t[x]];
		}else{
			g=r-d[y]+d[t[y]];
			modify(c[k],c[k],1,n,p[t[y]],p[y],calc(u,v,g),v);
			r=g-1;
			y=f[t[y]];
		}
	}
	if(d[x]<d[y])modify(c[k],c[k],1,n,p[x],p[y],calc(u,v,l),v);
	else modify(c[k],c[k],1,n,p[y],p[x],calc(u,v,r),-v);
}

ll query(int x,int y,int k){
	ll s;
	s=0;
	while(t[x]!=t[y]){
		if(d[t[x]]>d[t[y]]){
			s+=ask(c[k],1,n,p[t[x]],p[x]);
			x=f[t[x]];
		}else{
			s+=ask(c[k],1,n,p[t[y]],p[y]);
			y=f[t[y]];
		}
	}
	if(d[x]<d[y])s+=ask(c[k],1,n,p[x],p[y]);
	else s+=ask(c[k],1,n,p[y],p[x]);
	return s;
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1);
	dfs2(1,1);
	g=b=k=0;
	for(i=1;i<=m;i++){
		scanf("%s",ch);
		if(ch[0]=='c'){
			scanf("%lld%lld%d%d",&x,&y,&u,&v);
			x^=ans;
			y^=ans;
			g++;
			c[g]=c[b];
			b=g;
			add(x,y,b,u,v);
		}
		if(ch[0]=='q'){
			scanf("%lld%lld",&x,&y);
			x^=ans;
			y^=ans;
			ans=query(x,y,b);
			printf("%lld\n",ans);
		}
		if(ch[0]=='l'){
			scanf("%lld",&x);
			b=x^ans;
		}
	}
}
