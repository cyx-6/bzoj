#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

#define pa pair<int,int>
#define mp make_pair
#define A first
#define B second
#define N 400400
#define K 20

pa a[N],c[N];
int f[N][K];
int n,m,i,j,k,p,u,v,w;

int sum(int l,int r){
	int i,ans;
	ans=0;
	for(i=K-1;~i;i--){
		if(f[l][i] && f[l][i]<r){
			ans+=1<<i;
			l=f[l][i];
		}
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d%d",&u,&v);
		if(u>v)v+=m;
		c[i]=a[i]=mp(u,v);
		c[i+n]=a[i+n]=mp(u+m,v+m);
	}
	m=n<<1;
	sort(c+1,c+m+1);
	j=m;
	for(i=m-1;i;i--){
		while(j &&  c[j].A>c[i].B)j--;
		f[i][0]=j;
		for(k=1;k<K;k++)
			if(f[i][k-1])f[i][k]=f[f[i][k-1]][k-1];
	}
	for(i=1;i<=n;i++)
		printf("%d ",sum(lower_bound(c+1,c+m+1,a[i])-c,lower_bound(c+1,c+m+1,a[i+n])-c)+1);
	return 0;
}
