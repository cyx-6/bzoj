#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

#define pa pair<int,int>
#define mp make_pair
#define A first
#define B second
#define N 100100
#define M 400400

struct edge{
	int t,d,next;
};

struct data{
	int u,v,w;
};

edge e[M];
data c[M];
priority_queue<pa,vector<pa>,greater<pa> > s;
int h[N],f[N],d[N],p[N],q[N],ans[N];
bool g[N];
int n,m,i,j,k,u,v,w;

int comp(data p,data q){
	return p.w<q.w;
}

void addedge(int u,int v,int w){
	h[0]++;
	e[h[0]]=(edge){v,w,h[u]};
	h[u]=h[0];
}

void dijkstra(){
	int i,j,k;
	memset(d,0x7,sizeof(d));
	d[1]=0;
	s.push(mp(0,1));
	while(!s.empty()){
		i=s.top().B;
		s.pop();
		if(g[i])continue;
		else g[i]=true;
		for(k=h[i];k!=-1;k=e[k].next){
			j=e[k].t;
			if(d[j]>d[i]+e[k].d){
				d[j]=d[i]+e[k].d;
				s.push(mp(d[j],j));
			}
		}
	}
}

void build(int cur){
	int i;
	for(i=h[cur];i!=-1;i=e[i].next){
		if(d[e[i].t]==d[cur]+e[i].d){
			p[e[i].t]=cur;
			q[e[i].t]=q[cur]+1;
			build(e[i].t);
		}else if(e[i].t>cur && d[e[i].t]!=d[cur]-e[i].d){
			m++;
			c[m]=(data){cur,e[i].t,d[cur]+d[e[i].t]+e[i].d};
		}
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
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dijkstra();
	m=0;
	build(1);
	sort(c+1,c+m+1,comp);
	for(i=1;i<=m;i++){
		u=get(c[i].u);
		v=get(c[i].v);
		while(u!=v){
			if(q[u]>q[v])swap(u,v);
			ans[v]=c[i].w-d[v];
			f[v]=get(p[v]);
			v=get(v);
		}
	}
	for(i=2;i<=n;i++)printf("%d\n",ans[i]?ans[i]:-1);
	return 0;
}
