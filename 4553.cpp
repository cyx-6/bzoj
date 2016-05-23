#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=100100;
const int M=100000;

struct data{
	int d,l,r,ans,p;
};

data a[N];
int s[N],t[N];
int n,m,i,j,k,u,v,clock,ans;

int comp1(data u,data v){
	return u.d<v.d;
}

int comp2(data u,data v){
	return u.l<v.l;
}

int comp3(data u,data v){
	return u.p<v.p;
}

void add(int x,int y){
	for(;x<=M;x+=x&(-x)){
		if(t[x]==clock)s[x]=max(s[x],y);
		else{
			t[x]=clock;
			s[x]=y;
		}
	}
}

int ask(int x){
	int y;
	y=0;
	for(;x;x-=x&(-x))if(t[x]==clock)y=max(y,s[x]);
	return y;
}

void solve(int l,int r){
	int mid,i,j,k;
	if(l==r){
		ans=max(ans,a[l].ans);
		return;
	}
	mid=(l+r)>>1;
	solve(l,mid);
	clock++;
	sort(a+l,a+mid+1,comp1);
	sort(a+mid+1,a+r+1,comp2);
	k=l;
	for(i=mid+1;i<=r;i++){
		while(k<=mid && a[k].d<=a[i].l){
			add(a[k].r,a[k].ans);
			k++;
		}
		a[i].ans=max(a[i].ans,ask(a[i].d)+1);
	}
	sort(a+mid+1,a+r+1,comp3);
	solve(mid+1,r);
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i].d);
		a[i].l=a[i].r=a[i].d;
		a[i].p=i;
		a[i].ans=1;
	}
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		a[u].l=min(a[u].l,v);
		a[u].r=max(a[u].r,v);
	}
	solve(1,n);
	printf("%d\n",ans);
	return 0;
}
