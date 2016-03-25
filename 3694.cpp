#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N=4096;
const int M=200200;

struct edge{
	int t,d,next;
};

struct data{
	int u,v,w;
};

edge e[M];
data c[M];
int h[N],f[N],d[N],p[N],q[N],ans[N];
int n,m,i,j,k,u,v,w,t;

int comp(data p,data q){
	return p.w<q.w;
}

void addedge(int u,int v,int w){
	h[0]++;
	e[h[0]]=(edge){v,w,h[u]};
	h[u]=h[0];
}

void build(int cur,int pre){
	int i;
	p[cur]=pre;
	q[cur]=q[pre]+1;
	for(i=h[cur];i!=-1;i=e[i].next)
		if(e[i].t!=pre){
			d[e[i].t]=d[cur]+e[i].d;
			build(e[i].t,cur);
		}
}

int get(int x){
	if(!f[x])return x;
	else{
		f[x]=get(f[x]);
		return f[x];
	}
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&u,&v,&w,&t);
		if(t){
			addedge(u,v,w);
			addedge(v,u,w);
		}else{
			k++;
			c[k]=(data){u,v,w};
		}
	}
	build(1,0);
	for(i=1;i<=k;i++)c[i].w+=d[c[i].u]+d[c[i].v];
	sort(c+1,c+k+1,comp);
	for(i=1;i<=k;i++){
		u=get(c[i].u);
		v=get(c[i].v);
		while(u!=v){
			if(q[u]>q[v])swap(u,v);
			ans[v]=c[i].w-d[v];
			f[v]=get(p[v]);
			v=get(v);
		}
	}
	for(i=2;i<=n;i++)printf("%d ",ans[i]?ans[i]:-1);
	return 0;
}
