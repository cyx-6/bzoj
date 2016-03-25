#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=500500;
const int M=2002000;
const int I=2147483647;

int s[M];
int a[N],t[N],c[N],f[N];
int n,m,i,j,k,p,q;
long long ans;

int lowbit(int x){
	return x&(-x);
}

int find(int x){
	return lower_bound(t+1,t+k+1,x)-t;
}

void add(int x){
	for(;x<=k;x+=lowbit(x))c[x]++;
}

int sum(int x){
	int y;
	y=0;
	for(;x;x-=lowbit(x))y+=c[x];
	return y;
}

void up(int cur){
	int u,v;
	u=cur<<1;
	v=cur<<1|1;
	s[cur]=a[s[u]]<=a[s[v]]?s[u]:s[v];
}

void build(int cur,int l,int r){
	int mid;
	if(l==r){
		s[cur]=l;
		return;
	}
	mid=(l+r)>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	up(cur);
}

int ask(int cur,int l,int r,int u,int v){
	int mid,p,q;
	if(l>=u && r<=v)return s[cur];
	mid=(l+r)>>1;
	if(v<=mid)return ask(cur<<1,l,mid,u,v);
	if(u>mid)return ask(cur<<1|1,mid+1,r,u,v);
	p=ask(cur<<1,l,mid,u,v);
	q=ask(cur<<1|1,mid+1,r,u,v);
	return a[p]<=a[q]?p:q;
}

void clear(int cur,int l,int r,int tar){
	int mid;
	if(l==r){
		a[l]=I;
		return;
	}
	mid=(l+r)>>1;
	if(tar<=mid)clear(cur<<1,l,mid,tar);
	else clear(cur<<1|1,mid+1,r,tar);
	up(cur);
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[i]=a[i];
	}
	sort(t+1,t+n+1);
	k=unique(t+1,t+n+1)-t-1;
	for(i=n;i;i--){
		f[i]=sum(find(a[i])-1);
		add(find(a[i]));
		ans+=f[i];
	}
	printf("%lld\n",ans);
	build(1,1,n);
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		if(a[k]!=I){
			p=ask(1,1,n,k,n);
			q=a[k];
			while(a[p]<=q){
				ans-=f[p];
				clear(1,1,n,p);
				p=ask(1,1,n,k,n);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
