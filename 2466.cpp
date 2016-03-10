#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<bitset>

using namespace std;

const int N=128;

bitset<N> a[N];
bool s[N];
int n,m,i,j,k,u,v,ans;

void dfs(int cur,int sum){
	int i;
	if(sum>=ans)return;
	if(!cur){
		ans=sum;
		return;
	}
	if(!a[cur][cur]){
		s[cur]=1;
		dfs(cur-1,sum+1);
		s[cur]=0;
		dfs(cur-1,sum);
	}else{
		s[cur]=a[cur][n+1];
		for(i=cur+1;i<=n;i++)
			if(a[cur][i])s[cur]^=s[i];
		dfs(cur-1,sum+s[cur]);
	}
}

int main(){
	scanf("%d",&n);
	while(n){
		for(i=1;i<=n;i++){
			a[i].reset();
			a[i][n+1]=a[i][i]=1;
		}
		for(i=1;i<n;i++){
			scanf("%d%d",&u,&v);
			a[u][v]=a[v][u]=1;
		}
		k=0;
		for(i=1;i<=n;i++){
			for(j=i;j<=n;j++)if(a[j][i])break;
			if(j>n)continue;
			swap(a[i],a[j]);
			for(j=1;j<=n;j++)
				if(j!=i && a[j][i])a[j]^=a[i];
		}
		ans=n;
		dfs(n,0);
		printf("%d\n",ans);
		scanf("%d",&n);
	}
	return 0;
}
