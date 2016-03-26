#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

const int N=100100;
const int M=200200;

struct edge{
	int t,next;
};

edge e1[M],e2[M];
int h1[N],h2[N],b[N],s[N],d[N],f[N],a[N],t[N][2];
int n,m,i,j,k,u,v,w,sum,p,q,ans;

void addedge(int *h,edge *e,int u,int v){
	h[0]++;
	e[h[0]]=(edge){v,h[u]};
	h[u]=h[0];
}

void dfs(int cur,int pre){
	int i;
	f[cur]=pre;
	d[cur]=d[pre]^1;
	if(s[b[pre]]<k)b[cur]=b[pre];
	else{
		b[cur]=cur;
		addedge(h2,e2,b[pre],cur);
	}
	s[b[cur]]++;
	t[b[cur]][d[cur]&1]^=a[cur];
	for(i=h1[cur];i!=-1;i=e1[i].next)
		if(e1[i].t!=pre)dfs(e1[i].t,cur);
}

void work(int cur,int k){
	int i;
	ans^=t[cur][k];
	for(i=h2[cur];i!=-1;i=e2[i].next)
		work(e2[i].t,k);
}

void solve(int cur,int k){
	int i;
	if(b[cur]==cur)work(cur,k);
	else{
		if(d[cur]==k)ans^=a[cur];
		for(i=h1[cur];i!=-1;i=e1[i].next)
			if(e1[i].t!=f[cur])solve(e1[i].t,k);
	}
}

int main(){
	scanf("%d%d",&n,&p);
	p++;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]%=p;
	}
	memset(h1,-1,sizeof(h1));
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(h1,e1,u,v);
		addedge(h1,e1,v,u);
	}
	memset(h2,-1,sizeof(h2));
	k=sqrt(n+1e-6);
	s[0]=n;
	dfs(1,0);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d",&q);
		if(q==1){
			scanf("%d",&u);
			u^=sum;
			ans=0;
			solve(u,d[u]^1);
			if(ans)printf("MeiZ\n");
			else printf("GTY\n");
			sum+=ans>0;
		}else if(q==2){
			scanf("%d%d",&u,&v);
			u^=sum;
			v^=sum;
			v%=p;
			t[b[u]][d[u]]^=a[u];
			a[u]=v;
			t[b[u]][d[u]]^=a[u];
		}else{
			scanf("%d%d%d",&u,&v,&w);
			u^=sum;
			v^=sum;
			w^=sum;
			a[v]=w;
			a[v]%=p;
			addedge(h1,e1,u,v);
			addedge(h1,e1,v,u);
			f[v]=u;
			d[v]=d[u]^1;
			if(s[b[u]]<k)b[v]=b[u];
			else{
				b[v]=v;
				addedge(h2,e2,b[u],v);
			}
			s[b[v]]++;
			t[b[v]][d[v]]^=a[v];
		}
	}
	return 0;
}
