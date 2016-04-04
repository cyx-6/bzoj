#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<set>

using namespace std;

const int N=400400;
const int M=1601600;
const int K=20;

struct data{
	int l,r;
};

data a[N],c[N];
int f[N][K];
int t[N];
set<int> s;
set<int>::iterator x,y;
bool p[M],q[M];
int n,m,i,j,k,u,v,w;

int comp(data u,data v){
	return u.l<v.l || (u.l==v.l && u.r<v.r);
}

int sum(int l,int r){
	int i,ans;
	ans=0;
	for(i=K-1;~i;i--){
		if(f[l][i]<=r){
			ans+=1<<i;
			l=f[l][i]+1;
		}
	}
	return ans;
}

bool empty(int cur,int l,int r,int u,int v){
	int mid;
	if(p[cur])return false;
	if(l>=u && r<=v)return !q[cur];
	mid=(l+r)>>1;
	if(v<=mid)return empty(cur<<1,l,mid,u,v);
	if(u>mid)return empty(cur<<1|1,mid+1,r,u,v);
	return empty(cur<<1,l,mid,u,v)&empty(cur<<1|1,mid+1,r,u,v);
}

void use(int cur,int l,int r,int u,int v){
	int mid;
	q[cur]=true;
	if(l>=u && r<=v){
		p[cur]=true;
		return;
	}
	mid=(l+r)>>1;
	if(u<=mid)use(cur<<1,l,mid,u,v);
	if(v>mid)use(cur<<1|1,mid+1,r,u,v);
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
		m++;
		t[m]=a[i].l;
		m++;
		t[m]=a[i].r;
	}
	sort(t+1,t+m+1);
	m=unique(t+1,t+m+1)-t-1;
	for(i=1;i<=n;i++){
		a[i].l=lower_bound(t+1,t+m+1,a[i].l)-t;
		a[i].r=lower_bound(t+1,t+m+1,a[i].r)-t;
		c[i]=(data){a[i].l,a[i].r};
	}
	sort(c+1,c+n+1,comp);
	j=n;
	for(i=0;i<K;i++)f[m+1][i]=m+1;
	for(i=m;i;i--){
		f[i][0]=f[i+1][0];
		while(j && c[j].l==i){
			f[i][0]=min(f[i][0],c[j].r);
			j--;
		}
		for(k=1;k<K;k++){
			if(f[i][k-1]!=m+1)f[i][k]=f[f[i][k-1]+1][k-1];
			else f[i][k]=m+1;
		}
	}
	printf("%d\n",sum(1,m));
	s.insert(0);
	s.insert(m+1);
	for(i=1;i<=n;i++){
		u=a[i].l;
		v=a[i].r;
		if(empty(1,1,m,u,v)){
			x=lower_bound(s.begin(),s.end(),u);
			y=lower_bound(s.begin(),s.end(),v);
			x--;
			if(sum((*x)+1,(*y)-1)==sum((*x)+1,u-1)+sum(v+1,(*y)-1)+1){
				use(1,1,m,u,v);
				printf("%d ",i);
				s.insert(u);
				s.insert(v);
			}
		}
	}
	printf("\n");
	return 0;
}
