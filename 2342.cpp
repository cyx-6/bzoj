#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=1001000;

char s[N],a[N];
int d[N],f[N];
int n,m,i,j,k,ans;

void manacher(){
	int i,k,p;
	p=k=0;
	for(i=1;i<=n;i++){
		if(p>=i)d[i]=min(d[(k<<1)-i],p-i);
		else d[i]=0;
		while(a[i+d[i]]==a[i-d[i]-1])d[i]++;
		if(i+d[i]>p){
			k=i;
			p=i+d[i];
		}
	}
}

int get(int x){
	if(!f[x])return x;
	else{
		f[x]=get(f[x]);
		return f[x];
	}
}

int main(){
	scanf("%d",&n);
	scanf("%s",a+1);
	a[0]='<';
	a[n+1]='>';
	manacher();
	for(i=1;i<=n;i++){
		for(j=get(i-(d[i]>>1));j<i && j+d[j]<i;j=get(j))f[j]=get(j+1);
		if(j<i)ans=max(ans,(i-j)<<2);
	}
	printf("%d\n",ans);
	return 0;
}
