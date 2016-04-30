#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=1001000;
const int M=2147483647;

struct D{
	int d[2],u[2],v[2];
	int l,r;
};

D a[N];
int n,m,i,j,k,root,x,y,ans;

int comp(D u,D v){
	return u.d[k]<v.d[k] || (u.d[k]==v.d[k] && u.d[k^1]<v.d[k^1]);
}

void update(int cur,int tar){
	a[cur].u[0]=min(a[cur].u[0],a[tar].u[0]);
	a[cur].v[0]=max(a[cur].v[0],a[tar].v[0]);
	a[cur].u[1]=min(a[cur].u[1],a[tar].u[1]);
	a[cur].v[1]=max(a[cur].v[1],a[tar].v[1]);	
}

void make(int cur,int x,int y){
	a[cur].u[0]=a[cur].v[0]=x;
	a[cur].u[1]=a[cur].v[1]=y;
}

void build(int &cur,int l,int r,int d){
	k=d;
	cur=(l+r)>>1;
	nth_element(a+l,a+cur,a+r+1,comp);
	make(cur,a[cur].d[0],a[cur].d[1]);
	if(l<cur){
		build(a[cur].l,l,cur-1,d^1);
		update(cur,a[cur].l);
	}
	if(cur<r){
		build(a[cur].r,cur+1,r,d^1);
		update(cur,a[cur].r);
	}
}

void insert(int &cur,int tar,int d){
	if(!cur){
		cur=tar;
		return;
	}
	update(cur,n);
	if(a[tar].d[d]<a[cur].d[d] || (a[tar].d[d]==a[cur].d[d] && a[tar].d[d^1]<a[cur].d[d^1]))insert(a[cur].l,tar,d^1);
	else insert(a[cur].r,tar,d^1);
}

int dis(int cur,int x,int y){
	int sum;
	sum=0;
	if(x<a[cur].u[0])sum+=a[cur].u[0]-x;
	if(x>a[cur].v[0])sum+=x-a[cur].v[0];
	if(y<a[cur].u[1])sum+=a[cur].u[1]-y;
	if(y>a[cur].v[1])sum+=y-a[cur].v[1];
	return sum;
}

void ask(int cur,int x,int y){
	int l,r;
	ans=min(abs(x-a[cur].d[0])+abs(y-a[cur].d[1]),ans);
	l=a[cur].l?dis(a[cur].l,x,y):M;
	r=a[cur].r?dis(a[cur].r,x,y):M;
	if(l<r){
		if(l<ans)ask(a[cur].l,x,y);
		if(r<ans)ask(a[cur].r,x,y);
	}else{
		if(r<ans)ask(a[cur].r,x,y);
		if(l<ans)ask(a[cur].l,x,y);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].d[0],&a[i].d[1]);
	build(root,1,n,0);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&k,&x,&y);
		if(k&1){
			n++;
			make(n,x,y);
			a[n].d[0]=x;
			a[n].d[1]=y;
			insert(root,n,0);
		}else{
			ans=M;
			ask(root,x,y);
			printf("%d\n",ans);
		}
	}
	return 0;
}
