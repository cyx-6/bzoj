#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=666;

int a[N][N];
int f[N],next[N],c[N],q[N],s[N],g[N];
int n,m,i,j,k,e,t,u,v,l,r,ans;

void addedge(int u,int v){
	a[u][0]++;
	a[u][a[u][0]]=v;
}

int get(int cur){
	if(!f[cur])return cur;
	else{
		f[cur]=get(f[cur]);
		return f[cur];
	}
}

void comb(int u,int v){
	u=get(u);
	v=get(v);
	if(u!=v)f[u]=v;
}

int lca(int u,int v){
	k++;
	while(1){
		if(u){
			u=get(u);
			if(g[u]==k)return u;
			g[u]=k;
			u=next[c[u]];
		}
		swap(u,v);
	}
}

void blossom(int u,int v){
	int x,y;
	while(u!=v){
		x=c[u];
		y=next[x];
		if(get(y)!=v)next[y]=x;
		if(s[x]==2){
			r++;
			q[r]=x;
			s[x]=1;
		}
		if(s[y]==2){
			r++;
			q[r]=y;
			s[y]=1;
		}
		comb(u,x);
		comb(x,y);
		u=y;
	}
}

void bfs(int cur){
	int i,j,u,v,w;
	for(i=1;i<=n+m*3;i++)next[i]=f[i]=s[i]=0;
	s[cur]=1;
	l=r=1;
	q[1]=cur;
	while(l<=r){
		u=q[l];
		for(i=1;i<=a[u][0];i++){
			v=a[u][i];
			if(c[u]==v)continue;
			if(get(u)==get(v))continue;
			if(s[v]==2)continue;
			if(s[v]==1){
				w=lca(u,v);
				if(get(u)!=w)next[u]=v;
				if(get(v)!=w)next[v]=u;
				blossom(u,w);
				blossom(v,w);
			}else if(!c[v]){
				next[v]=u;
				for(u=v;u;u=w){
					v=next[u];
					w=c[v];
					c[u]=v;
					c[v]=u;
				}
				return;
			}else{
				next[v]=u;
				r++;
				q[r]=c[v];
				s[c[v]]=1;
				s[v]=2;
			}
		}
		l++;
	}
}

int main(){
	scanf("%d",&t);
	for(;t;t--){
		scanf("%d%d%d",&n,&m,&e);
		for(i=1;i<=n+m*3;i++)a[i][0]=c[i]=0;
		for(i=1;i<=e;i++){
			scanf("%d%d",&u,&v);
			for(j=0;j<3;j++){
				addedge(u,n+v+j*m);
				addedge(n+v+j*m,u);
			}
		}
		for(i=1;i<=m;i++){
			addedge(i+n,i+n+m);
			addedge(i+n+m,i+n);
			addedge(i+n,i+n+m*2);
			addedge(i+n+m*2,i+n);
			addedge(i+n+m,i+n+m*2);
			addedge(i+n+m*2,i+n+m);
		}
		for(i=1;i<=n+m*3;i++)if(!c[i])bfs(i);
		ans=0;
		for(i=1;i<=n+m*3;i++)ans+=c[i]>0;
		printf("%d\n",(ans>>1)-n);
	}
	return 0;
}
