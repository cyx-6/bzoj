#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

#define ll long long
#define N 1024
#define M 3600
#define P M_PI*2

int a[N],b[N];
pair<double,int> c[N];
int n,m,i,j,k,x,y;
double u,v;
ll ans[N];
ll sum,t;

int main(){
	scanf("%d",&n);
	for(i=0;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for(i=1;i<=n;i++){
		t=(ll)a[i]*a[0]+(ll)b[i]*b[0];
		if(t>0)sum+=t;
	}
	printf("%lld\n",sum);
	for(i=0;i<=M;i++){
		u=-cos(P*i/M);
		v=-sin(P*i/M);
		for(j=1;j<=n;j++)c[j]=make_pair(a[j]*u+b[j]*v,j);
		sort(c+1,c+n+1);
		x=y=0;
		for(j=1;j<=n;j++){
			x+=a[c[j].second];
			y+=b[c[j].second];
			ans[j]=max(ans[j],(ll)x*x+(ll)y*y);
		}
	}
	sum=0;
	for(i=1;i<=n;i++)sum=max(sum,ans[i]);
	printf("%lld\n",sum);
	for(i=1;i<=n;i++){
		printf("%lld",ans[i]);
		if(i<n)printf(" ");
	}
	return 0;
}
