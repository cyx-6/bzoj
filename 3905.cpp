#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=9;
const int M=1024;
const int P=1e9+7;

int a[N],ans[N],s[N];
int f[N][M];
char c[N];
bool b[N];
int n,m,i,j,k,t;

void solve(int m){
	int i,j,k,u,v,p,h;
	f[0][0]=s[0]=1;
	h=n-m+1;
	for(i=1;i<=h;i++)s[i]=s[i-1]*m;
	for(i=0;i<n;i++){
		for(j=0;j<s[h];j++)f[i+1][j]=0;
		for(p=0;p<(1<<n);p++){
			if(p&a[i+1])continue;
			for(j=m-1;j<n;j++){
				b[j]=true;
				for(k=j-m+1;k<=j;k++)
					if(k>=0 && (!(p&(1<<k)) || a[i+1]&(1<<k))){
						b[j]=false;
						break;
					}
			}
			for(u=0;u<s[h];u++){
				if(!f[i][u])continue;
				v=0;
				for(k=m-1;k<n;k++){
					if(b[k]){
						if(u/s[k-m+1]%m<m-1)v+=(u/s[k-m+1]%m+1)*s[k-m+1];
						else{
							v=-1;
							break;
						}
					}
				}
				if(v!=-1){
					f[i+1][v]+=f[i][u];
					if(f[i+1][v]>=P)f[i+1][v]-=P;
				}
			}
		}
	}
	ans[m-1]=0;
	for(i=0;i<s[h];i++){
		ans[m-1]+=f[n][i];
		if(ans[m-1]>=P)ans[m-1]-=P;
	}
}

int main(){
	scanf("%d",&t);
	for(;t;t--){
		scanf("%d",&n);
		m=1;
		for(i=1;i<=n;i++){
			scanf("%s",c);
			a[i]=0;
			for(j=0;j<n;j++){
				if(c[j]=='o'){
					m<<=1;
					if(m>=P)m-=P;
				}else a[i]|=1<<j;
			}
		}
		ans[0]=1;
		for(i=2;i<=n;i++)solve(i);
		ans[n]=(m-ans[n-1]+P)%P;
		for(i=n-1;i;i--)ans[i]=(ans[i]-ans[i-1]+P)%P;
		for(i=0;i<=n;i++)printf("%d\n",ans[i]);
	}
	return 0;
}
