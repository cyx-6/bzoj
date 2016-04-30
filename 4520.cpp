#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

#define ll long long
#define N 100100

struct data{
	int d[2],u[2],v[2];
	int l,r;
};

data a[N];
priority_queue<ll,vector<ll>,greater<ll> > h;
int n,m,i,j,k,root;

int comp(data u,data v){
	return u.d[k]<v.d[k] || (u.d[k]==v.d[k] && u.d[k^1]<v.d[k^1]);
}

void update(int cur,int tar){
	a[cur].u[0]=min(a[cur].u[0],a[tar].u[0]);
	a[cur].v[0]=max(a[cur].v[0],a[tar].v[0]);
	a[cur].u[1]=min(a[cur].u[1],a[tar].u[1]);
	a[cur].v[1]=max(a[cur].v[1],a[tar].v[1]);
}

void build(int &cur,int l,int r,int d){
	cur=(l+r)>>1;
	k=d;
	nth_element(a+l,a+cur,a+r+1,comp);
	a[cur].u[0]=a[cur].v[0]=a[cur].d[0];
	a[cur].u[1]=a[cur].v[1]=a[cur].d[1];
	if(l<cur){
		build(a[cur].l,l,cur-1,d^1);
		update(cur,a[cur].l);
	}
	if(cur<r){
		build(a[cur].r,cur+1,r,d^1);
		update(cur,a[cur].r);
	}
}

ll sqr(int x){
	return (ll)x*x;
}

ll dis(int x,int y,int z){
	return sqr(x-a[z].d[0])+sqr(y-a[z].d[1]);
}

ll assess(int cur,int tar){
	ll sum;
	sum=0;
	sum=max(sum,dis(a[cur].u[0],a[cur].u[1],tar));
	sum=max(sum,dis(a[cur].u[0],a[cur].v[1],tar));
	sum=max(sum,dis(a[cur].v[0],a[cur].u[1],tar));
	sum=max(sum,dis(a[cur].v[0],a[cur].v[1],tar));
	return sum;
}

void solve(int cur,int tar){
	ll l,r;
	h.push(dis(a[cur].d[0],a[cur].d[1],tar));
	if(h.size()>m)h.pop();
	l=a[cur].l?assess(a[cur].l,tar):0;
	r=a[cur].r?assess(a[cur].r,tar):0;
	if(l>r){
		if(l>h.top())solve(a[cur].l,tar);
		if(r>h.top())solve(a[cur].r,tar);
	}else{
		if(r>h.top())solve(a[cur].r,tar);
		if(l>h.top())solve(a[cur].l,tar);		
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].d[0],&a[i].d[1]);
	build(root,1,n,0);
	m<<=1;
	for(i=1;i<=n;i++)solve(root,i);
	printf("%lld\n",h.top());
	return 0;
}
