#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=1024;
const int M=300300;
const int T=12001200;
const int D=30;

struct data{
	int t[2];
	int s;
};

struct query{
	int u,v,t;
};

data a[T];
int c[N];
query q[N];
int h[M];
int n,m,i,j,k,t,u,d,l,r,f;

void insert(int &cur,int pre,int s,int d){
	int k;
	t++;
	cur=t;
	a[cur].s=a[pre].s+1;
	if(d<0)return;
	k=(s>>d)&1;
	insert(a[cur].t[k],a[pre].t[k],s,d-1);
	a[cur].t[k^1]=a[pre].t[k^1];
}

int ask(int k,int d){
	int i,sum,t;
	if(d<0)return 0;
	sum=0;
	for(i=1;i<=f;i++){
		t=!((q[i].t>>d)&1);
		sum+=a[a[q[i].u].t[t]].s-a[a[q[i].v].t[t]].s;
	}
	if(sum>=k){
		for(i=1;i<=f;i++){
			t=!((q[i].t>>d)&1);
			q[i].u=a[q[i].u].t[t];
			q[i].v=a[q[i].v].t[t];
		}
		return ask(k,d-1)|(1<<d);
	}else{
		for(i=1;i<=f;i++){
			t=(q[i].t>>d)&1;
			q[i].u=a[q[i].u].t[t];
			q[i].v=a[q[i].v].t[t];
		}
		return ask(k-sum,d-1);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&c[i]);
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		insert(h[i],h[i-1],k,D);
	}
	scanf("%d",&t);
	for(;t;t--){
		scanf("%d%d%d%d%d",&u,&d,&l,&r,&k);
		f=0;
		for(i=u;i<=d;i++){
			f++;
			q[f].u=h[r];
			q[f].v=h[l-1];
			q[f].t=c[i];
		}
		printf("%d\n",ask(k,D));
	}
	return 0;
}
