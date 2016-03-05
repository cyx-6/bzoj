#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=20;
const int K=101;
const int M=65536;

int a[N],s[N],p[N];
double f[K][M];
int n,m,i,j,k;

int main(){
	scanf("%d%d",&m,&n);
	for(i=1;i<=n+1;i++)p[i]=1<<(i-1);
	for(i=1;i<=n;i++){
		scanf("%d%d",&s[i],&k);
		while(k){
			a[i]+=p[k];
			scanf("%d",&k);
		}
	}
	for(i=m;i;i--)
		for(j=0;j<p[n+1];j++){
			for(k=1;k<=n;k++){
				if((a[k]&j)==a[k])f[i][j]+=max(f[i+1][j],f[i+1][j|p[k]]+s[k]);
				else f[i][j]+=f[i+1][j];
			}
			f[i][j]/=n;
		}
	printf("%.6lf\n",f[1][0]);
	return 0;
}
