#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=128;
const int M=65536;
const int I=1e9;

struct edge{
	int t,d,next;
};

int h[N];
int a[N][N];
edge e[M];
int d[N],gap[N],cur[N],t[M],s[N];
int n,m,i,j,k,u,v,w,ans,S,T,U,V;

void addedge(int u,int v,int w){
	h[0]++;
	e[h[0]]=(edge){v,w,h[u]};
	h[u]=h[0];
}

int isap(int S,int T,int n){
	int i,k,u,v,sum;
	memset(t,0,sizeof(t));
	memset(cur,-1,sizeof(cur));
	memset(gap,0,sizeof(gap));
	gap[0]=n;
	sum=0;
	while(t[S]<=n){
		u=s[0]?e[s[s[0]]].t:S;
		if(u==T){
			k=I;
			for(i=1;i<=s[0];i++)k=min(k,e[s[i]].d);
			sum+=k;
			for(i=1;i<=s[0];i++){
				e[s[i]].d-=k;
				e[s[i]^1].d+=k;
			}
			s[0]=0;
		}else{
			v=cur[u]==-1?h[u]:cur[u];
			while(v!=-1){
				if(e[v].d>0 && t[e[v].t]==t[u]-1)break;
				v=e[v].next;
			}
			cur[u]=v;
			if(v==-1){
				gap[t[u]]--;
				if(!gap[t[u]])return sum;
				t[u]++;
				gap[t[u]]++;
				if(s[0])s[0]--;
			}else{
				s[0]++;
				s[s[0]]=v;
			}
		}
	}
	return sum;
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&m);
		for(j=1;j<=m;j++){
			scanf("%d",&k);
			a[i][k]=1;
			d[i]--;
			d[k]++;
		}
	}
	memset(h,-1,sizeof(h));
	U=n+1;
	V=n+2;
	S=n+3;
	T=n+4;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
			if(a[i][j]){
				addedge(i,j,I);
				addedge(j,i,0);
			}
		if(d[i]>0){
			addedge(S,i,d[i]);
			addedge(i,S,0);
		}else{
			addedge(i,T,-d[i]);
			addedge(T,i,0);
		}
		addedge(U,i,I);
		addedge(i,U,0);
		addedge(i,V,I);
		addedge(V,i,0);
	}
	addedge(V,U,I);
	u=h[0];
	addedge(U,V,0);
	v=h[0];
	isap(S,T,n+4);
	ans=e[v].d;
	e[u].d=e[v].d=0;
	ans-=isap(V,U,n+2);
	printf("%d\n",ans);
	return 0;
}
