#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=10;
const int T=100;
const int M=1e9;
const int X[4]={1,-1,0,0};
const int Y[4]={0,0,1,-1};

int p[N][N];
long long a[T][T];
char s[N];
int n,m,i,j,k,u,v,q;

int det(int n){
	int i,j,k;
	long long ans,t,u,v;
	bool b;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			a[i][j]+=M;
			a[i][j]%=M;
		}
	b=false;
	ans=1;
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			u=a[i][i];
			v=a[j][i];
			while(v){
				t=u/v;
				u%=v;
				swap(u,v);
				for(k=i;k<=n;k++){
					a[i][k]=(a[i][k]-t*a[j][k]%M+M)%M;
					swap(a[i][k],a[j][k]);
				}
				b^=1;
			}
		}
		ans*=a[i][i];
		ans%=M;
		if(!ans)return 0;
	}
	if(b)return (M-ans)%M;
	else return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%s",s+1);
		for(j=1;j<=m;j++)
			if(s[j]=='.'){
				q++;
				p[i][j]=q;
			}
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(p[i][j]){
				for(k=0;k<4;k++){
					u=i+X[k];
					v=j+Y[k];
					if(p[u][v]){
						a[p[i][j]][p[i][j]]++;
						a[p[i][j]][p[u][v]]--;
					}
				}
			}
	printf("%d\n",det(q-1));
	return 0;
}
