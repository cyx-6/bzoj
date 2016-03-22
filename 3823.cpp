#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=10001000;

int a[N];
int n,m,i,j,k,sum,ans,del;

int main(){
	scanf("%d%d",&n,&m);
	a[1]=1;
	for(i=2;i<=n && i<m;i++)a[i]=(long long)(m-m/i)*a[m%i]%m;
	ans=del=1;
	for(i=n;i;i--){
		k=i<<1;
		while(k>=m && !(k%m)){
			k/=m;
			sum++;
		}
		del=(long long)del*k%m;
		k=n-i+1;
		while(k>=m && !(k%m)){
			k/=m;
			sum--;
		}
		del=(long long)del*a[k%m]%m;
		ans^=sum?0:del;
	}
	printf("%d\n",ans);
	return 0;
}
