#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=2048;

int a[N][N][2],b[N][N][2];
int n,m,i,j,k,u,v,w,x,y,z,t;

int aska(int k,int cur,int l,int r){
	int mid,t;
	t=a[k][cur][0];
	if(l>=v && r<=y)return max(t,a[k][cur][1]);
	mid=(l+r)>>1;
	if(v<=mid)t=max(t,aska(k,cur<<1,l,mid));
	if(y>mid)t=max(t,aska(k,cur<<1|1,mid+1,r));
	return t;
}

int askb(int k,int cur,int l,int r){
	int mid,t;
	t=b[k][cur][0];
	if(l>=v && r<=y)return max(t,b[k][cur][1]);
	mid=(l+r)>>1;
	if(v<=mid)t=max(t,askb(k,cur<<1,l,mid));
	if(y>mid)t=max(t,askb(k,cur<<1|1,mid+1,r));
	return t;
}

void adda(int k,int cur,int l,int r,int d){
	int mid;
	a[k][cur][1]=max(a[k][cur][1],d);
	if(l>=v && r<=y){
		a[k][cur][0]=max(a[k][cur][0],d);
		return;
	}
	mid=(l+r)>>1;
	if(v<=mid)adda(k,cur<<1,l,mid,d);
	if(y>mid)adda(k,cur<<1|1,mid+1,r,d);
}

void addb(int k,int cur,int l,int r,int d){
	int mid;
	b[k][cur][1]=max(b[k][cur][1],d);
	if(l>=v && r<=y){
		b[k][cur][0]=max(b[k][cur][0],d);
		return;
	}
	mid=(l+r)>>1;
	if(v<=mid)addb(k,cur<<1,l,mid,d);
	if(y>mid)addb(k,cur<<1|1,mid+1,r,d);
}

int ask(int cur,int l,int r){
	int mid,t;
	t=aska(cur,1,1,m);
	if(l>=u && r<=x)return max(t,askb(cur,1,1,m));
	mid=(l+r)>>1;
	if(u<=mid)t=max(t,ask(cur<<1,l,mid));
	if(x>mid)t=max(t,ask(cur<<1|1,mid+1,r));
	return t;
}

void add(int cur,int l,int r,int d){
	int mid;
	addb(cur,1,1,m,d);
	if(l>=u && r<=x){
		adda(cur,1,1,m,d);
		return;
	}
	mid=(l+r)>>1;
	if(u<=mid)add(cur<<1,l,mid,d);
	if(x>mid)add(cur<<1|1,mid+1,r,d);
}

int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(;t;t--){
		scanf("%d%d%d%d%d",&x,&y,&z,&u,&v);
		u++;
		v++;
		x=u+x-1;
		y=v+y-1;
		k=ask(1,1,n);
		add(1,1,n,k+z);
	}
	x=n;
	y=m;
	u=v=1;
	printf("%d\n",ask(1,1,n));
	return 0;
}
