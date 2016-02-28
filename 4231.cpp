#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=100100;
const int M=700700;
const int C=26;
const int T=2002000;
const int B=29;

struct A{
	int t[C];
	int f;
};

struct D{
	int l,r,s;
};

struct E{
	int t,c,next;
};

struct Q{
	int u,v,k1,k2,ans,t;
};

int h1[N],h2[M];
E e1[M],e2[M];
int f[N][C];
char s[M],t[M];
A a[M];
D d[T];
Q q[N];
int p[N],root[M],deep[N],h[M],ch[N],l[M],r[M];
int n,m,i,j,k,u,v,w,g;

void addedge(int *h,E *e,int u,int v,int w=0){
	h[0]++;
	e[h[0]]=(E){v,w,h[u]};
	h[u]=h[0];
}

void dfs(int cur,int pre,int tar){
	int i;
	p[cur]=tar;
	deep[cur]=deep[pre]+1;
	f[cur][0]=pre;
	for(i=1;i<C;i++)f[cur][i]=f[f[cur][i-1]][i-1];
	for(i=h1[cur];i!=-1;i=e1[i].next)
		if(e1[i].t!=pre){
			if(!a[tar].t[e1[i].c]){
				k++;
				a[tar].t[e1[i].c]=k;
			}
			ch[e1[i].t]=e1[i].c;
			dfs(e1[i].t,cur,a[tar].t[e1[i].c]);
		}
}

int jump(int cur,int del){
	int i;
	for(i=0;i<C;i++)if(del&(1<<i))cur=f[cur][i];
	return cur;
}

int lca(int u,int v){
	int i,del;
	if(deep[u]>deep[v])swap(u,v);
	v=jump(v,deep[v]-deep[u]);
	for(i=C-1;i>=0;i--)
		if(f[u][i]!=f[v][i]){
			u=f[u][i];
			v=f[v][i];
		}
	return u==v?u:f[u][0];
}

void insert(int cur){
	int i,n,m,p,u,v,c,d1,d2,w,d;
	scanf("%d%d",&q[cur].u,&q[cur].v);
	scanf("%s",s+1);
	q[cur].t=n=strlen(s+1);
	reverse(s+1,s+n+1);
	p=1;
	for(i=1;i<=n;i++){
		if(!a[p].t[s[i]-'a']){
			k++;
			a[p].t[s[i]-'a']=k;
		}
		p=a[p].t[s[i]-'a'];
	}
	q[cur].k1=p;
	reverse(s+1,s+n+1);
	d=p=1;
	w=0;
	for(i=1;i<=n;i++){
		w=w*B+s[i]-'a';
		d*=B;
		if(!a[p].t[s[i]-'a']){
			k++;
			a[p].t[s[i]-'a']=k;
		}
		p=a[p].t[s[i]-'a'];
	}
	q[cur].k2=p;
	u=q[cur].u;
	v=q[cur].v;
	c=lca(u,v);
	d1=max(deep[u]-deep[c]-n,0);
	d2=max(deep[v]-deep[c]-n,0);	
	u=jump(u,d1);
	v=jump(v,d2);
	d1=deep[u]-deep[c];
	d2=deep[v]-deep[c];
	for(i=1;i<=d1;i++){
		t[i]=ch[u];
		u=f[u][0];
	}
	for(i=1;i<=d2;i++){
		t[d1+d2-i+1]=ch[v];
		v=f[v][0];
	}
	m=d1+d2;
	for(i=1;i<=m;i++){
		h[i]=h[i-1]*B+t[i];
		if(i>=n && h[i]-h[i-n]*d==w)q[cur].ans++;
	}
}

void build(){
	int l,r,i,p,k;
	a[1].f=h[1]=l=r=1;
	while(l<=r){
		k=h[l];
		for(i=0;i<C;i++)
			if(a[k].t[i]){
				p=a[k].f;
				while(p!=1 && !a[p].t[i])p=a[p].f;
				a[a[k].t[i]].f=a[p].t[i] && a[p].t[i]!=a[k].t[i]?a[p].t[i]:1;
				addedge(h2,e2,a[a[k].t[i]].f,a[k].t[i]);
				r++;
				h[r]=a[k].t[i];
			}
		l++;
	}
}

void update(int &cur,int pre,int l,int r,int tar){
	int mid;
	g++;
	cur=g;
	d[cur].s=d[pre].s+1;
	if(l==r)return;
	mid=(l+r)>>1;
	if(tar<=mid){
		d[cur].r=d[pre].r;
		update(d[cur].l,d[pre].l,l,mid,tar);
	}else{
		d[cur].l=d[pre].l;
		update(d[cur].r,d[pre].r,mid+1,r,tar);
	}
}

void pre(int cur){
	int i;
	g++;
	l[cur]=g;
	for(i=h2[cur];i!=-1;i=e2[i].next)
		pre(e2[i].t);
	r[cur]=g;
}

void add(int cur,int pre){
	int i;
	update(root[cur],root[pre],1,k,l[p[cur]]);
	for(i=h1[cur];i!=-1;i=e1[i].next)
		if(e1[i].t!=pre)add(e1[i].t,cur);
}

int ask(int cur,int l,int r,int u,int v){
	int mid,s;
	if(l>=u && r<=v)return d[cur].s;
	mid=(l+r)>>1;
	s=0;
	if(u<=mid)s+=ask(d[cur].l,l,mid,u,v);
	if(mid<v)s+=ask(d[cur].r,mid+1,r,u,v);
	return s;
}

void solve(int cur){
	int i,n,m,u,v,c,d1,d2,w,d;
	u=q[cur].u;
	v=q[cur].v;
	c=lca(u,v);
	d1=max(deep[u]-deep[c]-q[cur].t,0);
	d2=max(deep[v]-deep[c]-q[cur].t,0);	
	u=jump(u,d1);
	v=jump(v,d2);
	q[cur].ans+=ask(root[q[cur].u],1,k,l[q[cur].k1],r[q[cur].k1]);
	q[cur].ans-=ask(root[u],1,k,l[q[cur].k1],r[q[cur].k1]);
	q[cur].ans+=ask(root[q[cur].v],1,k,l[q[cur].k2],r[q[cur].k2]);
	q[cur].ans-=ask(root[v],1,k,l[q[cur].k2],r[q[cur].k2]);	
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h1,-1,sizeof(h1));
	for(i=1;i<n;i++){
		scanf("%d%d%s",&u,&v,s+1);
		w=s[1]-'a';
		addedge(h1,e1,u,v,w);
		addedge(h1,e1,v,u,w);		
	}
	k=p[1]=1;
	dfs(1,0,1);
	for(i=1;i<=m;i++)insert(i);
	memset(h2,-1,sizeof(h2));
	build();
	pre(1);
	g=0;
	add(1,0);
	for(i=1;i<=m;i++){
		solve(i);
		printf("%d\n",q[i].ans);
	}
	return 0;
}
