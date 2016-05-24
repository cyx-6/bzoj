#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>

using namespace std;

map<int,int> f;
int n,m,i,j,k,a,b,p;

int power(int x,int y){
	int z;
	if(!y)return 1;
	z=power(x,y>>1);
	z=(long long)z*z%p;
	if(y&1)z=(long long)z*x%p;
	return z;
}

void solve(){
	int i,c,q,t;
	a%=p;
	b%=p;
	if(a==0){
		if(b==0)printf("1\n");
		else printf("no solution\n");
		return;
	}
	f.clear();
	c=ceil(sqrt(p));
	f[1]=p;
	q=a;
	for(i=1;i<c;i++){
		if(!f[q])f[q]=i;
		q=(long long)q*a%p;
	}
	t=power(q,p-2);
	q=b;
	for(i=0;i<=c;i++){
		if(f[q]){
			printf("%d\n",i*c+f[q]%p);
			return;
		}
		q=(long long)q*t%p;
	}
	printf("no solution\n");
}

int main(){
	while(scanf("%d%d%d",&p,&a,&b)==3)solve();
	return 0;
}
