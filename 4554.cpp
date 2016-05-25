#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=128;
const int M=2525;
const int E=200200;
const int I=1e9;

struct edge{
	int t,d,next;
};

int a[N][N];
char s[N][N];
int h[M],cur[M],gap[M],g[M],f[M];
edge e[E];
int n,m,i,j,k,t,S,T,ans;

void addedge(int u,int v,int w){
	g[0]++;
	e[g[0]]=(edge){v,w,g[u]};
	g[u]=g[0];
}

void isap(){
	int i,k,u,v;
	memset(cur,-1,sizeof(cur));
	memset(h,0,sizeof(h));
	memset(gap,0,sizeof(gap));
	gap[0]=T;
	f[0]=0;
	while(h[S]<=T){
		u=f[0]?e[f[f[0]]].t:S;
		if(u==T){
			k=I;
			for(i=1;i<=f[0];i++)k=min(k,e[f[i]].d);
			for(i=1;i<=f[0];i++){
				e[f[i]].d-=k;
				e[f[i]^1].d+=k;
			}
			ans+=k;
			f[0]=0;
		}else{
			v=cur[u]==-1?g[u]:cur[u];
			while(v!=-1){
				if(e[v].d>0 && h[e[v].t]+1==h[u])break;
				v=e[v].next;
			}
			cur[u]=v;
			if(v!=-1){
				f[0]++;
				f[f[0]]=v;
			}else{
				gap[h[u]]--;
				if(!gap[h[u]])return;
				h[u]++;
				gap[h[u]]++;
				if(f[0])f[0]--;
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(j=1;j<=m;j++){
		for(i=1;i<=n;i++){
			if(s[i][j]!='#' && (i==1 || s[i-1][j]=='#'))t++;
			a[i][j]=t;
		}
	}
	k=t;
	memset(g,-1,sizeof(g));
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(s[i][j]!='#' && (j==1 || s[i][j-1]=='#'))t++;
			if(s[i][j]=='*'){
				addedge(t,a[i][j],1);
				addedge(a[i][j],t,0);
			}
		}
	}
	S=t+1;
	T=t+2;
	for(i=1;i<=k;i++){
		addedge(i,T,1);
		addedge(T,i,0);
	}
	for(i=k+1;i<=t;i++){
		addedge(S,i,1);
		addedge(i,S,0);
	}
	isap();
	printf("%d\n",ans);
	return 0;
}
