#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=100100;
const int M=3003000;
const int K=20;

struct suffix{
	int p,x,y;
};

struct data{
	int l,r,s;
};

char s[N];
data a[M];
int sa[N],rank[N],height[N],h[N];
int f[N][K];
int lg[N];
suffix g[N];
int n,m,i,j,k,l1,l2,r1,r2;

int comp(suffix u,suffix v){
	return u.x<v.x || (u.x==v.x && u.y<v.y);
}

void build(){
	int i,j,k,p;
	for(i=1;i<=n;i++)rank[i]=s[i]-'a'+1;
	for(k=1;k<=n;k<<=1){
		for(i=1;i<=n;i++)g[i]=(suffix){i,rank[i],i+k<=n?rank[i+k]:0};
		sort(g+1,g+n+1,comp);
		p=0;
		for(i=1;i<=n;i++){
			if(comp(g[i-1],g[i]))p++;
			rank[g[i].p]=p;
		}
		if(p>=n)break;
	}
	for(i=1;i<=n;i++)sa[rank[i]]=i;
	k=0;
	for(i=1;i<=n;i++){
		if(k)k--;
		j=sa[rank[i]-1];
		while(s[i+k]==s[j+k])k++;
		height[rank[i]]=k;
	}
}

void prepare(){
	int i,j;
	lg[1]=0;
	for(i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(i=1;i<=n;i++)f[i][0]=height[i];
	for(i=n;i;i--)
		for(j=1;j<K;j++)
			if(i+(1<<j)-1<=n)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

int ask(int l,int r){
	int k;
	if(l>r)swap(l,r);
	if(!l)return 0;
	if(l==r)return n-sa[l]+1;
	l++;
	k=lg[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}

void insert(int &cur,int pre,int l,int r,int tar){
	int mid;
	k++;
	cur=k;
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

int find1(int cur,int pre,int l,int r,int tar){
	int mid,ans;
	if(l==r)return a[cur].s-a[pre].s?l:0;
	mid=(l+r)>>1;
	ans=0;
	if(tar>mid)if(a[a[cur].r].s-a[a[pre].r].s)ans=find1(a[cur].r,a[pre].r,mid+1,r,tar);
	if(!ans)return find1(a[cur].l,a[pre].l,l,mid,tar);
	else return ans;
}

int find2(int cur,int pre,int l,int r,int tar){
	int mid,ans;
	if(l==r)return a[cur].s-a[pre].s?l:0;
	mid=(l+r)>>1;
	ans=0;
	if(tar<=mid)if(a[a[cur].l].s-a[a[pre].l].s)ans=find2(a[cur].l,a[pre].l,l,mid,tar);
	if(!ans)return find2(a[cur].r,a[pre].r,mid+1,r,tar);
	else return ans;
}

bool check(int l,int r,int len,int pos){
	int x,y;
	if(l>r)return false;
	x=find1(h[r],h[l-1],1,n,pos);
	y=find2(h[r],h[l-1],1,n,pos);
	return max(ask(x,pos),ask(y,pos))>=len;
}

int solve(int l1,int r1,int l2,int r2){
	int l,r,mid;
	l=1;
	r=r2-l2+1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(l1,r1-mid+1,mid,rank[l2]))l=mid+1;
		else r=mid-1;
	}
	return r;
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	build();
	prepare();
	k=0;
	for(i=1;i<=n;i++)insert(h[i],h[i-1],1,n,rank[i]);
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		printf("%d\n",solve(l1,r1,l2,r2));
	}
	return 0;
}
