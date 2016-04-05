#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=200200;
const int M=9009000;
const int K=20;

struct data{
	int l,r,s;
};

struct edge{
	int t,next;
};

struct work{
	int u,v,w;
};

data a[M];
edge e[N];
work q[N];
int h[N],t[N],l[N],r[N],c[N],d[N];
int s[4][N];
int g[4];
int f[N][K];
int n,m,i,j,k,u,v,w,p,x,y;

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void dfs(int cur,int pre){
	int i;
	k++;
	l[cur]=k;
	d[cur]=d[pre]+1;
	f[cur][0]=pre;
	for(i=1;i<K;i++)f[cur][i]=f[f[cur][i-1]][i-1];
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=pre)dfs(e[i].t,cur);
	r[cur]=k+1;
}

void add(int &cur,int pre,int l,int r,int tar,int del){
	int mid;
	if(!cur){
		k++;
		cur=k;
	}
	a[cur].s=a[pre].s+del;
	if(l==r)return;
	mid=(l+r)>>1;
	if(tar<=mid){
		a[cur].r=a[pre].r;
		add(a[cur].l,a[pre].l,l,mid,tar,del);
	}else{
		a[cur].l=a[pre].l;
		add(a[cur].r,a[pre].r,mid+1,r,tar,del);
	}
}

void add(int x,int y,int del){
	int i,k;
	k=lower_bound(t+1,t+p+1,y)-t;
	for(i=l[x];i<=n;i+=i&(-i))
		add(h[i],h[i],1,p,k,del);
	del*=-1;
	for(i=r[x];i<=n;i+=i&(-i))
		add(h[i],h[i],1,p,k,del);
}

int lca(int u,int v){
	int del,i;
	if(d[u]>d[v])swap(u,v);
	del=d[v]-d[u];
	for(i=0;i<K;i++)
		if(del&(1<<i))v=f[v][i];
	for(i=K-1;~i;i--)
		if(f[u][i]!=f[v][i]){
			u=f[u][i];
			v=f[v][i];
		}
	return u==v?u:f[u][0];
}

int ask(int l,int r,int k){
	int i,j,mid,sum;
	if(l==r)return l;
	mid=(l+r)>>1;
	sum=0;
	for(i=0;i<2;i++)
		for(j=1;j<=s[i][0];j++)sum+=a[a[s[i][j]].r].s;
	for(i=2;i<4;i++)
		for(j=1;j<=s[i][0];j++)sum-=a[a[s[i][j]].r].s;
	if(sum>=k){
		for(i=0;i<4;i++)
			for(j=1;j<=s[i][0];j++)s[i][j]=a[s[i][j]].r;
		return ask(mid+1,r,k);
	}else{
		for(i=0;i<4;i++)
			for(j=1;j<=s[i][0];j++)s[i][j]=a[s[i][j]].l;
		return ask(l,mid,k-sum);
	}
}

void ask(int u,int v,int x,int y,int k){
	int i,j,sum;
	g[0]=u;
	g[1]=v;
	g[2]=x;
	g[3]=y;
	sum=0;
	for(i=0;i<2;i++){
		s[i][0]=0;
		for(j=l[g[i]];j;j-=j&(-j)){
			s[i][0]++;
			s[i][s[i][0]]=h[j];
			sum+=a[h[j]].s;
		}
	}
	for(i=2;i<4;i++){
		s[i][0]=0;
		for(j=l[g[i]];j;j-=j&(-j)){
			s[i][0]++;
			s[i][s[i][0]]=h[j];
			sum-=a[h[j]].s;
		}
	}
	if(sum<k)printf("invalid request!\n");
	else printf("%d\n",t[ask(1,p,k)]);
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&c[i]);
		p++;
		t[p]=c[i];
	}
	memset(h,-1,sizeof(h));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs(1,0);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&q[i].w,&q[i].u,&q[i].v);
		if(!q[i].w){
			p++;
			t[p]=q[i].v;
		}
	}
	sort(t+1,t+p+1);
	p=unique(t+1,t+p+1)-t-1;
	k=0;
	memset(h,0,sizeof(h));
	for(i=1;i<=n;i++)add(i,c[i],1);
	for(i=1;i<=m;i++){
		u=q[i].u;
		v=q[i].v;
		w=q[i].w;
		if(!w){
			add(u,c[u],-1);
			c[u]=v;
			add(u,v,1);
		}else{
			x=lca(u,v);
			y=f[x][0];
			ask(u,v,x,y,w);
		}
	}
}
