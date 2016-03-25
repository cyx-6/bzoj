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
#define N 64
#define M 4096
#define E 266144

struct edge{
	int t,d,next;
};

edge e[E];
priority_queue<pa,vector<pa>,greater<pa> > q;
int a[N][N],p[N][N];
int d[M],h[M],t[M];
bool f[M];
char c[N];
int n,m,i,j,k,u,v,w,ans,dis;

void addedge(int u,int v,int w){
	h[0]++;
	e[h[0]]=(edge){v,w,h[u]};
	h[u]=h[0];
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%s",c+1);
		for(j=1;j<=m;j++){
			a[i][j]=c[j]=='B';
			k++;
			p[i][j]=k;
		}
	}
	memset(h,-1,sizeof(h));
	k++;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			if(i<n){
				addedge(p[i][j],p[i+1][j],a[i][j]^a[i+1][j]);
				addedge(p[i+1][j],p[i][j],a[i][j]^a[i+1][j]);
			}
			if(j<m){
				addedge(p[i][j],p[i][j+1],a[i][j]^a[i][j+1]);
				addedge(p[i][j+1],p[i][j],a[i][j]^a[i][j+1]);
			}
		}
	ans=k;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			k=p[i][j];
			memset(f,false,sizeof(f));
			memset(d,0x7,sizeof(d));
			dis=d[k]=0;
			while(!q.empty())q.pop();
			q.push(mp(d[k],k));
			while(!q.empty()){
				u=q.top().B;
				q.pop();
				if(f[u])continue;
				else f[u]=true;
				dis=max(dis,d[u]+((d[u]&1)^(a[i][j]&1)));
				for(w=h[u];w!=-1;w=e[w].next){
					v=e[w].t;
					if(d[v]>d[u]+e[w].d){
						d[v]=d[u]+e[w].d;
						q.push(mp(d[v],v));
					}
				}
			}
			ans=min(ans,dis);
		}
	printf("%d\n",ans);
	return 0;
}
