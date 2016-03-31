#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=100100;
const int M=512;
const int C=26;

char a[N];
char s[M];
int l[M],r[M],x[N],y[N],t[N];
int f[N][C];
int n,m,i,j,k,u,v,w,sum;
long long ans;

int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	scanf("%d%d%d",&m,&u,&v);
	for(i=1;i<=m;i++){
		scanf("%s%d%d",s+i,&l[i],&r[i]);
		s[i]-='a';
	}
	for(i=n;i;i--){
		a[i]-='a';
		for(j=0;j<C;j++)f[i][j]=f[i+1][j];
		f[i][a[i]]++;
	}
	for(i=0;i<C;i++)f[0][i]=f[1][i];
	t[0]=-m;
	for(i=1;i<=n;i++){
		sum+=t[i]>=u && t[i]<=v;
		for(j=1;j<=m;j++){
			for(;x[j]<=i && f[x[j]][s[j]]-f[i+1][s[j]]>=l[j];x[j]++){
				if(t[x[j]]==v)sum--;
				t[x[j]]++;
				if(t[x[j]]==u)sum++;
			}
			for(;y[j]<=i && f[y[j]][s[j]]-f[i+1][s[j]]>r[j];y[j]++){
				if(t[y[j]]==u)sum--;
				t[y[j]]--;
				if(t[y[j]]==v)sum++;
			}
		}
		ans+=sum;
	}
	printf("%lld\n",ans);
	return 0;
}
