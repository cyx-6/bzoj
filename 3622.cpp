#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=2048;
const int M=1e9+9;

int c[N][N],f[N][N];
int a[N],b[N],t[N],p[N];
int n,m,i,j,k;

int main(){
	scanf("%d%d",&n,&m);
	if((n-m)&1){
		printf("0\n");
		return 0;
	}
	m=(n+m)>>1;
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(i=1;i<=n;i++)
		for(t[i]=t[i-1];t[i]<n && a[i]>b[t[i]+1];t[i]++);
	p[0]=1;
	for(i=1;i<=n;i++)p[i]=(long long)p[i-1]*i%M;
	for(i=0;i<=n;i++){
		c[i][0]=c[i][i]=1;
		for(j=1;j<i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%M;
	}
	f[0][0]=1;
	for(i=1;i<=n;i++){
		for(j=0;j<=i;j++){
			f[i][j]=f[i-1][j];
			if(j && t[i]>=j){
				f[i][j]+=(long long)f[i-1][j-1]*(t[i]-j+1)%M;
				f[i][j]%=M;
			}
		}
	}
	for(i=n;i>=m;i--){
		f[n][i]=(long long)f[n][i]*p[n-i]%M;
		for(j=i+1;j<=n;j++){
			f[n][i]+=M-(long long)f[n][j]*c[j][i]%M;
			f[n][i]%=M;
		}
	}
	printf("%d\n",f[n][m]);
	return 0;
}
