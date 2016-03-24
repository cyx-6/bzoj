#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

const int N=65536;
const int M=131072;
const int K=256;

struct edge{
	int t,next;
};

edge e1[M],e2[M];
int h1[N],h2[N],a[N],f[N],t[N],b[N];
int s[N][K];
int n,m,i,j,k,u,v,w,ans;

void addedge(int *h,edge *e,int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void add(int d,int k){
	int i;
	for(i=t[k];i && s[k][i]>d;i--)
		s[k][i+1]=s[k][i];
	s[k][i+1]=d;
	t[k]++;
}

void modify(int p,int d,int k){
	int i,c;
	c=lower_bound(s[k]+1,s[k]+t[k]+1,a[p])-s[k];
	a[p]=d;
	for(i=c-1;i && s[k][i]>d;i--)
		s[k][i+1]=s[k][i];
	s[k][i+1]=d;
	c=i+1;
	for(i=c+1;i<=t[k] && s[k][i]<d;i++)
		s[k][i-1]=s[k][i];
	s[k][i-1]=d;
}

int ask(int d,int k){
	return t[k]-(upper_bound(s[k]+1,s[k]+t[k]+1,d)-s[k])+1;
}

void dfs(int cur,int pre){
	int i;
	f[cur]=pre;
	if(t[b[pre]]<k)b[cur]=b[pre];
	else{
		addedge(h2,e2,b[pre],cur);
		b[cur]=cur;
	}
	add(a[cur],b[cur]);
	for(i=h1[cur];i!=-1;i=e1[i].next)
		if(e1[i].t!=f[cur])dfs(e1[i].t,cur);
}

void work(int cur,int del){
	int i;
	ans+=ask(del,cur);
	for(i=h2[cur];i!=-1;i=e2[i].next)
		work(e2[i].t,del);
}

void solve(int cur,int del){
	int i;
	if(b[cur]==cur)work(cur,del);
	else{
		ans+=a[cur]>del;
		for(i=h1[cur];i!=-1;i=e1[i].next)
			if(e1[i].t!=f[cur])solve(e1[i].t,del);
	}
}

int main(){
	scanf("%d",&n);
	memset(h1,-1,sizeof(h1));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(h1,e1,u,v);
		addedge(h1,e1,v,u);		
	}
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	t[0]=n;
	k=sqrt(n+1e-6);
	memset(h2,-1,sizeof(h2));
	dfs(1,0);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&w,&u,&v);
		u^=ans;
		v^=ans;
		if(!w){
			ans=0;
			solve(u,v);
			printf("%d\n",ans);
		}else if(w&1)modify(u,v,b[u]);
		else{
			n++;
			f[n]=u;
			addedge(h1,e1,u,n);
			addedge(h1,e1,n,u);
			if(t[b[u]]<k)b[n]=b[u];
			else{
				b[n]=n;
				addedge(h2,e2,b[u],n);
			}
			a[n]=v;
			add(a[n],b[n]);
		}
	}
	return 0;
}
