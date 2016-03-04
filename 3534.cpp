#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

const int N=64;
const int E=1e-10;

double a[N][N];
int n,m,i,j,k;
double t;

double det(int n){
	int i,j,k;
	double t,ans;
	ans=1;
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++)
			if(fabs(a[j][i])>E){
				t=a[j][i]/a[i][i];
				for(k=i;k<=n;k++)
					a[j][k]-=a[i][k]*t;
			}
		ans*=a[i][i];
		if(fabs(ans)<E)return 0;
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	t=1;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			scanf("%lf",&a[i][j]);
			if(i==j)continue;
			if(a[i][j]>1-E)a[i][j]-=E;
			if(i<j)t*=1-a[i][j];
			a[i][j]=a[i][j]/(1-a[i][j]);
		}
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i!=j)a[i][i]-=a[i][j];
	printf("%.8lf\n",fabs(det(n-1)*t));
	return 0;
}
