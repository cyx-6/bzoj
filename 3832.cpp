#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N=500500;
const int M=2002000;

struct heap{
	priority_queue<int> a,b;
	void push(int x){
		a.push(x);
	}
	void del(int x){
		b.push(x);
	}
	int top(){
		while(!b.empty() && a.top()==b.top()){
			a.pop();
			b.pop();
		}
		return a.top();
	}
};

struct edge{
	int t,next;
	bool f;
};

edge e[M];
heap s;
int h[N],a[N],b[N],p[N],d[N];
int n,m,i,j,k,u,v,w,l,r,ans,pos,dis;

void addedge(int u,int v,bool w){
	h[0]++;
	e[h[0]]=(edge){v,h[u],w};
	h[u]=h[0];
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v,1);
		addedge(v,u,0);
		d[v]++;
	}
	l=1;
	for(i=1;i<=n;i++)
		if(!d[i]){
			r++;
			p[r]=i;
		}
	while(l<=r){
		for(i=h[p[l]];i!=-1;i=e[i].next)
			if(e[i].f){
				d[e[i].t]--;
				if(!d[e[i].t]){
					r++;
					p[r]=e[i].t;
				}
			}
		l++;
	}
	for(i=1;i<=n;i++){
		k=p[i];
		for(j=h[k];j!=-1;j=e[j].next)
			if(!e[j].f)a[k]=max(a[k],a[e[j].t]+1);
	}
	for(i=n;i;i--){
		k=p[i];
		for(j=h[k];j!=-1;j=e[j].next)
			if(e[j].f)b[k]=max(b[k],b[e[j].t]+1);
	}
	for(i=1;i<=n;i++)s.push(b[i]);
	ans=n;
	for(i=1;i<=n;i++){
		k=p[i];
		s.del(b[k]);
		for(j=h[k];j!=-1;j=e[j].next)
			if(!e[j].f)s.del(a[e[j].t]+b[k]+1);
		dis=s.top();
		if(dis<ans || (dis==ans && k<=pos)){
			ans=dis;
			pos=k;
		}
		s.push(a[k]);
		for(j=h[k];j!=-1;j=e[j].next)
			if(e[j].f)s.push(a[k]+b[e[j].t]+1);
	}
	printf("%d %d\n",pos,ans);
	return 0;
}
