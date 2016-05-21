#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=1024;

int a[N][N],b[N][N],c[N][N];
int s[N],t[N],r[N],d[N];
int n,m,i,j,k;

int main(){
	srand(20160521);
	for(i=1;i<N;i++)r[i]=rand();
	while(scanf("%d",&n)==1){
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)scanf("%d",&a[i][j]);
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)scanf("%d",&b[i][j]);
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)scanf("%d",&c[i][j]);
		for(i=1;i<=n;i++)s[i]=t[i]=d[i]=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)s[i]+=r[j]*a[j][i];
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)t[i]+=s[j]*b[j][i];
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)d[i]+=r[j]*c[j][i];
		for(i=1;i<=n;i++)
			if(t[i]!=d[i])break;
		printf(i<=n?"No\n":"Yes\n");
	}
	return 0;
}
