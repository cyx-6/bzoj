#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=1024;

int a[N][N],f[N][N];
int n,m,t,i,j,k;

int main(){
	scanf("%d",&t);
	for(;t;t--){
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)
			for(j=m;j;j--)scanf("%d",&a[i][j]);
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			f[i][j]=max(f[i-1][j-1]+a[i][j],max(f[i-1][j],f[i][j-1]));
		printf("%d\n",f[n][m]);
	}
	return 0;
}
