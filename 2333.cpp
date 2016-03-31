#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=300300;
const int M=1201200;

struct edge{
	int t,next;
};

struct data{
	int l,r,s,d;
};

struct query{
	int u,v,w;
};

edge e[N];
data a[M];
query q[N];
int h[N],f[N],s[N],t[N],c[N],l[N],r[N],p[N];
int n,m,i,j,k,u,v,w;
char ch[4];

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

int get(int x){
	if(!f[x])return x;
	else{
		f[x]=get(f[x]);
		return f[x];
	}
}

void dfs(int cur,int pre){
	int i;
	k++;
	l[cur]=r[cur]=k;
	p[k]=cur;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=pre)dfs(e[i].t,cur);
}

void add(int cur,int del){
	a[cur].s+=del;
	a[cur].d+=del;
}

void down(int cur){
	if(a[cur].d){
		add(cur<<1,a[cur].d);
		add(cur<<1|1,a[cur].d);
		a[cur].d=0;
	}
}

void up(int cur){
	a[cur].s=max(a[cur<<1].s,a[cur<<1|1].s);
}

void build(int cur,int l,int r){
	int mid;
	a[cur].l=l;
	a[cur].r=r;
	if(l==r){
		a[cur].s=c[p[l]];
		return;
	}
	mid=(l+r)>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	up(cur);
}

void add(int cur,int l,int r,int del){
	int mid;
	if(a[cur].l>=l && a[cur].r<=r){
		add(cur,del);
		return;
	}
	down(cur);
	mid=(a[cur].l+a[cur].r)>>1;
	if(l<=mid)add(cur<<1,l,r,del);
	if(mid<r)add(cur<<1|1,l,r,del);
	up(cur);
}

int ask(int cur,int l,int r){
	int mid,t;
	if(a[cur].l>=l && a[cur].r<=r)return a[cur].s;
	down(cur);
	mid=(a[cur].l+a[cur].r)>>1;
	t=-1e9;
	if(l<=mid)t=max(t,ask(cur<<1,l,r));
	if(mid<r)t=max(t,ask(cur<<1|1,l,r));
	return t;
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&c[i]);
		s[i]=1;
	}
	scanf("%d",&m);
	memset(h,-1,sizeof(h));
	for(i=1;i<=m;i++){
		scanf("%s",ch);
		if(ch[0]=='U'){
			q[i].w=1;
			scanf("%d%d",&q[i].u,&q[i].v);
			u=get(q[i].u);
			v=get(q[i].v);
			if(u!=v){
				if(s[u]<s[v])swap(u,v);
				addedge(u,v);
				f[v]=u;
				s[u]+=s[v];
			}
		}else if(ch[0]=='A'){
			q[i].w=ch[1]-'0'+1;
			if(q[i].w!=4)scanf("%d%d",&q[i].u,&q[i].v);
			else scanf("%d",&q[i].u);
		}else if(ch[0]=='F'){
			q[i].w=ch[1]-'0'+4;
			if(q[i].w!=7)scanf("%d",&q[i].u);
		}
	}
	for(i=1;i<=n;i++){
		u=-1;
		for(j=h[i];j!=-1;j=v){
			v=e[j].next;
			e[j].next=u;
			u=j;
		}
		h[i]=u;
	}
	for(i=1;i<=n;i++)
		if(get(i)==i)dfs(i,0);
	build(1,1,n);
	memset(f,0,sizeof(f));
	for(i=1;i<=n;i++)s[i]=1;
	for(i=1;i<=m;i++){
		if(q[i].w==1){
			u=get(q[i].u);
			v=get(q[i].v);
			if(u!=v){
				if(s[u]<s[v])swap(u,v);
				f[v]=u;
				s[u]+=s[v];
				r[u]=r[v];
			}
		}else if(q[i].w==2){
			k=q[i].u;
			add(1,l[k],l[k],q[i].v);
		}else if(q[i].w==3){
			k=get(q[i].u);
			add(1,l[k],r[k],q[i].v);
		}else if(q[i].w==4)add(1,1,n,q[i].u);
		else if(q[i].w==5){
			k=q[i].u;
			printf("%d\n",ask(1,l[k],l[k]));
		}else if(q[i].w==6){
			k=get(q[i].u);
			printf("%d\n",ask(1,l[k],r[k]));
		}else printf("%d\n",a[1].s);
	}
	return 0;
}
