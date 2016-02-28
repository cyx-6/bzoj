#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<set>
#include<cmath>
#include<cstring>

using namespace std;

const int N=100100;
const int M=200200;
const int K=2002000;
const int L=17;

struct T{
	int t[2];
	int d;
	bool s;
};

struct E{
	int t,next;
};

struct D{
	int p;
	bool f;
};

struct P{
	double x;
	int k;
	bool f;
};

struct C{
	double x,y,r;
};

set<D> s;
C c[N];
T a[K];
P p[M];
E e[N];
int f[N],g[N],h[N];
int n,m,i,j,k;
long double ans;

double sqr(double x){
	return x*x;
}

double calc(const D &d){
	int t;
	t=d.f?-1:1;
	return c[d.p].y+c[d.p].r*t;
}

double dis(int u,int v){
	return sqr(c[u].x-c[v].x)+sqr(c[u].y-c[v].y);
}

bool operator < (const D &u,const D &v){
	int p,q;
	p=u.p;
	q=v.p;
	if(dis(p,q)>=sqr(c[p].r)+sqr(c[q].r))return c[p].y<c[q].y;
	else return calc(u)<calc(v);
}

void addedge(int u,int v){
	h[0]++;
	e[h[0]]=(E){v,h[u]};
	h[u]=h[0];
}

void add(int p){
	set<D>::iterator it;
	s.insert((D){p,1});
	it=s.find((D){p,1});
	if(it==s.begin())g[p]=0;
	else{
		it--;
		if((*it).f)g[p]=(*it).p;
		else g[p]=g[(*it).p];
	}
	s.insert((D){p,0});
	if(g[p])addedge(g[p],p);
}

void del(int p){
	s.erase((D){p,0});
	s.erase((D){p,1});	
}

int comp(P u,P v){
	return u.x<v.x;
}

void down(int cur,int del){
	int l,r;
	if(a[cur].d&(1<<del))swap(a[cur].t[0],a[cur].t[1]);
	l=a[cur].t[0];
	r=a[cur].t[1];
	if(l)a[l].d^=a[cur].d;
	if(r)a[r].d^=a[cur].d;
	a[cur].d=0;
}

void up(int cur){
	a[cur].s=a[a[cur].t[0]].s&a[a[cur].t[1]].s;
}

void insert(int &cur,int tar,int del){
	if(!cur){
		k++;
		cur=k;
	}
	if(del<0){
		a[cur].s=true;
		return;
	}
	down(cur,del);
	insert(a[cur].t[(tar&(1<<del))>0],tar,del-1);
	up(cur);
}

int mex(int cur,int del){
	if(!cur)return 0;
	if(~del)down(cur,del);
	if(!a[a[cur].t[0]].s)return mex(a[cur].t[0],del-1);
	else return mex(a[cur].t[1],del-1)+(1<<del);
}

int comb(int p,int q,int del){
	if(!p || !q)return p|q;
	if(~del){
		down(p,del);
		down(q,del);
	}else{
		a[p].s=true;
		return p;
	}
	a[p].t[0]=comb(a[p].t[0],a[q].t[0],del-1);
	a[p].t[1]=comb(a[p].t[1],a[q].t[1],del-1);
	up(p);
	return p;
}

void dfs(int cur){
	int sum,i;
	g[cur]=0;
	if(h[cur]==-1)insert(g[cur],0,L);
	sum=0;
	for(i=h[cur];i!=-1;i=e[i].next){
		dfs(e[i].t);
		sum^=f[e[i].t];
	}
	insert(g[cur],sum,L);
	for(i=h[cur];i!=-1;i=e[i].next){
		a[g[e[i].t]].d^=sum^f[e[i].t];
		g[cur]=comb(g[cur],g[e[i].t],L);
	}
	f[cur]=mex(g[cur],L);
}

void solve(int cur,int sg){
	int i;
	double s;
	s=sqr(c[cur].r);
	for(i=h[cur];i!=-1;i=e[i].next){
		sg^=f[e[i].t];
		s-=sqr(c[e[i].t].r);
	}
	if(!sg)ans+=s;
	for(i=h[cur];i!=-1;i=e[i].next)solve(e[i].t,sg^f[e[i].t]);
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf%lf",&c[i].x,&c[i].y,&c[i].r);
		m++;
		p[m]=(P){c[i].x-c[i].r,i,1};
		m++;
		p[m]=(P){c[i].x+c[i].r,i,0};
	}
	sort(p+1,p+m+1,comp);
	memset(h,-1,sizeof(h));
	for(i=1;i<=m;i++){
		if(p[i].f)add(p[i].k);
		else del(p[i].k);
	}
	dfs(1);
	solve(1,0);
	printf("%.6lf\n",(double)(ans*M_PI));
	return 0;
}
