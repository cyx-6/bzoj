#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=200200;
const int M=6006000;
const int T=99999;

struct data{
	int l,r,s;
};

data a[M];
int h[N];
int n,m,i,j,k,l,r,b,x,ans,t;

void insert(int &cur,int pre,int l,int r,int tar){
	int mid;
	t++;
	cur=t;
	a[cur].s=a[pre].s+1;
	if(l==r)return;
	mid=(l+r)>>1;
	if(tar<=mid){
		a[cur].r=a[pre].r;
		insert(a[cur].l,a[pre].l,l,mid,tar);
	}else{
		a[cur].l=a[pre].l;
		insert(a[cur].r,a[pre].r,mid+1,r,tar);
	}
}

bool ask(int cur,int pre,int l,int r,int u,int v){
	int mid;
	if(u>v)return false;
	if(v<0 || u>T)return false;
	if(u<=l && v>=r)return a[cur].s-a[pre].s>0;
	mid=(l+r)>>1;
	if(u<=mid && ask(a[cur].l,a[pre].l,l,mid,u,v))return true;
	if(v>mid && ask(a[cur].r,a[pre].r,mid+1,r,u,v))return true;
	return false;
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&k);
		insert(h[i],h[i-1],0,T,k);
	}
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&b,&x,&l,&r);
		ans=0;
		for(j=18;~j;j--){
			if(b&(1<<j))ans+=(ask(h[r],h[l-1],0,T,ans-x,ans+(1<<j)-x-1)^1)*(1<<j);
			else ans+=ask(h[r],h[l-1],0,T,ans+(1<<j)-x,ans+(1<<(j+1))-x-1)*(1<<j);
		}
		printf("%d\n",ans^b);
	}
	return 0;
}
