#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=100100;
const int M=128;

int a[N][M];
int s[M],p[N],q[N];
int t[M][M];
int n,m,i,j,k,d;

bool check(int u,int v){
	int i,ans;
	ans=0;
	for(i=1;i<=d;i++)ans+=a[u][i]*a[v][i];
	return !(ans%m);
}

bool mul(int n,int k){
	int i,j,ans;
	if(k&1){
		ans=0;
		for(i=1;i<=d;i++)
			for(j=1;j<=d;j++){
				ans+=t[i][j]*a[n][i]*a[n][j];
				t[i][j]+=a[n][i]*a[n][j];
				t[i][j]%=3;
			}
		return ans%3!=(n-1)%3;
	}else{
		ans=0;
		for(i=1;i<=d;i++){
			ans^=s[i]&a[n][i];
			s[i]^=a[n][i];
		}
		return ans!=(n-1&1);
	}
}

int main(){
	scanf("%d%d%d",&n,&d,&m);
	for(i=1;i<=n;i++)p[i]=i;
	random_shuffle(p+1,p+n+1);
	for(i=1;i<=n;i++)q[p[i]]=i;
	for(i=1;i<=n;i++)
		for(j=1;j<=d;j++){
			scanf("%d",&a[p[i]][j]);
			a[p[i]][j]%=m;
		}
	for(i=1;i<=n;i++)
		if(mul(i,m))
			for(j=i-1;j;j--)
				if(check(i,j)){
					if(q[i]<q[j])printf("%d %d\n",q[i],q[j]);
					else printf("%d %d\n",q[j],q[i]);
					return 0;
				}
	printf("-1 -1\n");
	return 0;
}
