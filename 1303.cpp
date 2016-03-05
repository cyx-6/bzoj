#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=100100;
const int M=200200;

int a[N];
int s[M],t[M];
int n,m,i,j,k,ans;

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==m){
			k=i;
			a[i]=0;
		}else a[i]=(a[i]-m)/abs(a[i]-m);
	}
	s[n]=t[n]=1;
	for(i=k-1;i;i--){
		a[i]+=a[i+1];
		s[a[i]+n]++;
	}
	for(i=k+1;i<=n;i++){
		a[i]+=a[i-1];
		t[a[i]+n]++;
	}
	k=n<<1;
	for(i=1;i<=k;i++)
		ans+=s[i]*t[k-i];
	printf("%d\n",ans);
	return 0;
}
