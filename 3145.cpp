#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=200200;
const int M=8008000;
const int K=18;

struct data{
	int l,r,u,v,s;
};

data a[M];
char s[N],x[N],y[N];
int h1[N],h2[N],sa1[N],sa2[N],rank1[N],rank2[N];
int t1[N],t2[N],c[N],lg[N],p[N];
int h[N],g[N];
int f[N][K];
bool f1[N],f2[N];
int n,m,i,j,k,ans,d,u,v,w,l,r;

void build(int n,char *s,int *sa,int *rank,int *h){
	int i,j,k,p,m;
	int *x,*y;
	x=t1;
	y=t2;
	m=128;
	for(i=1;i<=m;i++)c[i]=0;
	for(i=1;i<=n;i++)c[x[i]=s[i]]++;
	for(i=2;i<=m;i++)c[i]+=c[i-1];
	for(i=n;i;i--)sa[c[x[i]]--]=i;
	for(k=1;k<=n;k<<=1){
		p=1;
		for(i=n-k+1;i<=n;i++)y[p++]=i;
		for(i=1;i<=n;i++)if(sa[i]>k)y[p++]=sa[i]-k;
		for(i=1;i<=m;i++)c[i]=0;
		for(i=1;i<=n;i++)c[x[y[i]]]++;
		for(i=2;i<=m;i++)c[i]+=c[i-1];
		for(i=n;i;i--)sa[c[x[y[i]]]--]=y[i];
		swap(x,y);
		p=2;
		x[sa[1]]=1;
		for(i=2;i<=n;i++)x[sa[i]]=y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k] && sa[i]+k<=n && sa[i-1]+k<=n?p-1:p++;
		if(p>n)break;
		m=p;
	}
	for(i=1;i<=n;i++)rank[sa[i]]=i;
	k=1;
	for(i=1;i<=n;i++){
		if(k)k--;
		if(rank[i]==1)continue;
		j=sa[rank[i]-1];
		while(s[i+k]==s[j+k])k++;
		h[rank[i]]=k;
	}
}

void rmq(){
	int i,j,k;
	for(i=d;i;i--){
		f[i][0]=h2[i];
		for(j=1;j<K;j++){
			if(i+(1<<j)<=d)f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
			else break;
		}
	}
	lg[1]=0;
	for(i=2;i<=n+m+1;i++)lg[i]=lg[i>>1]+1;
}

int ask(int l,int r){
	int k;
	l=rank2[l];
	r=rank2[r];
	if(l>r)swap(l,r);
	l++;
	k=lg[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}

int comp(int u,int v){
	return h1[rank1[u]]>h1[rank1[v]] || (h1[rank1[u]]==h1[rank1[v]] && rank1[u]<rank1[v]);
}

int get(int cur){
	if(!g[cur])return cur;
	else{
		g[cur]=get(g[cur]);
		return g[cur];
	}
}

void insert(int &cur,int l,int r,int tar){
	int mid;
	k++;
	cur=k;
	a[cur].u=a[cur].v=tar;
	if(l==r)return;
	mid=(l+r)>>1;
	if(rank2[tar]<=mid)insert(a[cur].l,l,mid,tar);
	else insert(a[cur].r,mid+1,r,tar);
}

void update(int cur){
	int u,v;
	u=a[cur].l;
	v=a[cur].r;
	a[cur].s=max(a[u].s,a[v].s);
	a[cur].u=a[u].u;
	a[cur].v=a[v].v;
	u=a[u].v;
	v=a[v].u;
	if(u<=m ^ v<=m)a[cur].s=max(a[cur].s,ask(u,v));
}

int comb(int u,int v){
	if(!u || !v)return u+v;
	a[u].l=comb(a[u].l,a[v].l);
	a[u].r=comb(a[u].r,a[v].r);
	update(u);
	return u;
}

int main(){
	scanf("%s",x+1);
	scanf("%s",y+1);
	n=strlen(x+1);
	m=strlen(y+1);
	for(i=1;i<=n;i++)s[i]=x[i];
	s[n+1]='~';
	for(i=1;i<=m;i++)s[i+n+1]=y[i];
	s[n+m+2]='|';
	n++;
	m++;
	d=n+m;
	build(d,s,sa1,rank1,h1);
	reverse(s+1,s+d+1);
	build(d,s,sa2,rank2,h2);
	rmq();
	for(i=1;i<=d;i++){
		p[i]=i;
		if(i>2 && i!=n+1 && i!=n+2)insert(h[i],1,d,d-i+3);
		if(d-i+1>1 && d-i+1<=m)f1[i]=true;
		if(d-i+1>m+1 && d-i+1<=d)f2[i]=true;
	}
	sort(p+1,p+d+1,comp);
	for(i=1;i<=d;i++){
		l=p[i];
		r=sa1[rank1[p[i]]-1];
		u=get(l);
		v=r?get(r):0;
		if(u && v && u!=v){
			g[v]=u;
			f1[u]|=f1[v];
			f2[u]|=f2[v];
			h[u]=comb(h[u],h[v]);
			if(!(l==1 || l==n+1 || r==1 || r==n+1))w=1;
			else w=0;
			if(f1[u] && f2[u])ans=max(ans,h1[rank1[p[i]]]+w+a[h[u]].s);
		}
	}
	printf("%d\n",ans);
	return 0;
}
