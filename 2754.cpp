#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>

using namespace std;

const int N=200200;
const int K=20;

struct data{
	map<int,int> t;
	int f;
};

struct edge{
	int t,next;
};

data a[N];
edge e[N];
int s[N],t[N],q[N],l[N],r[N],p[N],h[N],d[N],b[N];
int f[N][K];
int n,m,i,j,k,c,ans;

void insert(int k){
	int i,t;
	t=1;
	for(i=l[k];i<=r[k];i++){
		if(!a[t].t[s[i]]){
			c++;
			a[t].t[s[i]]=c;
		}
		p[i]=t=a[t].t[s[i]];
	}
}

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void build(){
	int i,j,k,l,r,u,v,w;
	map<int,int>::iterator it;
	l=r=1;
	q[1]=1;
	a[1].f=1;
	while(l<=r){
		u=q[l];
		for(it=a[u].t.begin();it!=a[u].t.end();it++){
			k=it->first;
			w=it->second;
			for(v=a[u].f;v!=1 && !a[v].t[k];v=a[v].f);
			a[w].f=a[v].t[k] && a[v].t[k]!=w?a[v].t[k]:1;
			addedge(a[w].f,w);
			r++;
			q[r]=w;
		}
		l++;
	}
}

void dfs(int cur){
	int i;
	c++;
	b[cur]=c;
	d[cur]=d[a[cur].f]+1;
	for(i=1;i<K;i++)f[cur][i]=f[f[cur][i-1]][i-1];
	for(i=h[cur];i!=-1;i=e[i].next){
		f[e[i].t][0]=cur;
		dfs(e[i].t);
	}		
}

int comp(int u,int v){
	return b[u]<b[v];
}

int lca(int u,int v){
	int i,del;
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

void solve(int cur){
	int i;
	for(i=h[cur];i!=-1;i=e[i].next){
		solve(e[i].t);
		t[cur]+=t[e[i].t];
	}
}

void work(int cur){
	int i;
	t[cur]+=t[a[cur].f];
	for(i=h[cur];i!=-1;i=e[i].next)work(e[i].t);
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&k);
		l[i]=c+1;
		r[i]=c+k;
		c+=k;
		for(j=l[i];j<=r[i];j++)scanf("%d",&s[j]);
		scanf("%d",&k);
		l[i+n]=c+1;
		r[i+n]=c+k;
		c+=k;
		for(j=l[i+n];j<=r[i+n];j++)scanf("%d",&s[j]);
	}
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		l[i+(n<<1)]=c+1;
		r[i+(n<<1)]=c+k;
		c+=k;
		for(j=l[i+(n<<1)];j<=r[i+(n<<1)];j++)scanf("%d",&s[j]);
	}
	c=1;
	for(i=1;i<=(n<<1)+m;i++)insert(i);
	memset(h,-1,sizeof(h));
	build();
	c=0;
	dfs(1);
	for(i=1;i<=n;i++){
		k=0;
		for(j=l[i];j<=r[i];j++){
			k++;
			q[k]=p[j];
		}
		for(j=l[i+n];j<=r[i+n];j++){
			k++;
			q[k]=p[j];
		}
		sort(q+1,q+k+1,comp);
		k=unique(q+1,q+k+1)-q-1;
		t[q[1]]++;
		for(j=2;j<=k;j++){
			t[q[j]]++;
			t[lca(q[j],q[j-1])]--;
		}
	}
	solve(1);
	for(i=1;i<=m;i++)printf("%d\n",t[p[r[i+(n<<1)]]]);
	memset(t,0,sizeof(t));
	for(i=1;i<=m;i++)t[p[r[i+(n<<1)]]]++;
	work(1);
	for(i=1;i<=n;i++){
		k=0;
		for(j=l[i];j<=r[i];j++){
			k++;
			q[k]=p[j];
		}
		for(j=l[i+n];j<=r[i+n];j++){
			k++;
			q[k]=p[j];
		}
		sort(q+1,q+k+1,comp);
		k=unique(q+1,q+k+1)-q-1;
		ans=t[q[1]];
		for(j=2;j<=k;j++)ans+=t[q[j]]-t[lca(q[j],q[j-1])];
		if(i<n)printf("%d ",ans);
		else printf("%d",ans);
	}
	return 0;
}
