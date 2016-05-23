#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=100100;

int f[N],p[N],q[N],g[N],ans[N],c[N];
char t[2];
int n,m,i,j,k,u,v;

int get(int cur){
	if(!g[cur])return cur;
	else{
		g[cur]=get(g[cur]);
		return g[cur];
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		f[v]=u;
	}
	c[1]=1;
	for(i=1;i<=m;i++){
		scanf("%s%d",&t,&q[i]);
		p[i]=t[0]=='C';
		if(p[i])c[q[i]]++;
	}
	for(i=1;i<=n;i++)
		if(!c[i])g[i]=f[i];
	for(i=m;i;i--){
		if(p[i]){
			c[q[i]]--;
			if(!c[q[i]])g[q[i]]=f[q[i]];
		}else ans[i]=get(q[i]);
	}
	for(i=1;i<=m;i++)
		if(ans[i])printf("%d\n",ans[i]);
	return 0;
}
