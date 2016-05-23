#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

const int N=50050;
const int M=100100;
const int K=2000000;
const int T=22;

struct data{
	int l,r,i,j;
};

priority_queue<data,vector<data> > h;
data q[K];
data z;
int a[N],b[M],c[M],next[M];
int d[K];
int g[K][T];
int s[N],p[N];
int pow[T],log[N];
bool f[N];
int n,m,i,j,k,t,sum,root,u,v,w,l,r;

bool operator < (data u,data v){
	return d[u.i]+d[u.j]<d[v.i]+d[v.j];
}

void addedge(int u,int v,int w){
	a[0]++;
	b[a[0]]=v;
	c[a[0]]=w;
	next[a[0]]=a[u];
	a[u]=a[0];
}

void getsize(int cur,int pre){
	int i;
	s[cur]=1;
	for(i=a[cur];i!=-1;i=next[i]){
		if(f[b[i]] && b[i]!=pre){
			getsize(b[i],cur);
			s[cur]+=s[b[i]];
		}
	}
}

void getroot(int cur,int pre){
	int i,k;
	k=0;
	for(i=a[cur];i!=-1;i=next[i]){
		if(f[b[i]] && b[i]!=pre){
			getroot(b[i],cur);
			if(root)return;
			else k=max(k,s[b[i]]);
		}
	}
	if(k<=sum>>1 && s[cur]>=sum>>1)root=cur;
}

void dfs(int cur,int pre){
	int i;
	t++;
	d[t]=p[cur];
	q[t]=((data){l,r,t,0});
	for(i=a[cur];i!=-1;i=next[i])
		if(f[b[i]] && b[i]!=pre){
			p[b[i]]=p[cur]+c[i];
			dfs(b[i],cur);
		}
}

void solve(int cur){
	int i;
	t++;
	l=r=t;
	q[t]=(data){l,r,t,0};
	f[cur]=false;
	for(i=a[cur];i!=-1;i=next[i])
		if(f[b[i]]){
			p[b[i]]=c[i];
			dfs(b[i],cur);
			r=t;
		}
	getsize(cur,0);
	for(i=a[cur];i!=-1;i=next[i])
		if(f[b[i]]){
			sum=s[b[i]];
			root=0;
			getroot(b[i],cur);
			solve(root);
		}
}

void rmq(){
	int i,j,k;
	pow[0]=1;
	for(i=1;i<T;i++)pow[i]=pow[i-1]<<1;
	log[1]=0;
	for(i=2;i<=n;i++)log[i]=log[i>>1]+1;
	for(i=t;i;i--){
		g[i][0]=i;
		for(j=1;j<T;j++){
			if(i+pow[j]-1<=t)g[i][j]=d[g[i][j-1]]>d[g[i+pow[j-1]][j-1]]?g[i][j-1]:g[i+pow[j-1]][j-1];
			else break;
		}
	}
}

int ask(int l,int r){
	int k;
	if(l==r)return l;
	k=log[r-l+1];
	return d[g[l][k]]>d[g[r-pow[k]+1][k]]?g[l][k]:g[r-pow[k]+1][k];
}

int main(){
	memset(a,-1,sizeof(a));
	scanf("%d%d",&n,&m);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	memset(f,true,sizeof(f));
	getsize(1,0);
	sum=s[1];
	root=0;
	getroot(1,0);
	solve(root);
	rmq();
	for(i=1;i<=t;i++){
		q[i].j=ask(q[i].l,q[i].r);
		h.push(q[i]);
	}
	for(i=1;i<=m;i++){
		z=h.top();
		h.pop();
		printf("%d\n",d[z.i]+d[z.j]);
		if(z.j-1>=z.l)h.push((data){z.l,z.j-1,z.i,ask(z.l,z.j-1)});
		if(z.j+1<=z.r)h.push((data){z.j+1,z.r,z.i,ask(z.j+1,z.r)});
	}
	return 0;
}
