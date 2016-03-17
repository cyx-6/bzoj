#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=100100;

struct data{
	int t[2];
	int s,f,c,d;
	bool r;
};

data a[N];
int f[N],g[N],t[N],s[N];
int n,m,i,j,k,u,v,w,ans,x,y,p,q;
char c[4];

bool isroot(int cur){
	return cur!=a[a[cur].f].t[0] && cur!=a[a[cur].f].t[1];
}

void down(int cur){
	int tar;
	if(a[cur].r){
		tar=a[cur].t[0];
		swap(a[tar].t[0],a[tar].t[1]);
		a[tar].r^=1;
		tar=a[cur].t[1];
		swap(a[tar].t[0],a[tar].t[1]);
		a[tar].r^=1;
		a[cur].r=false;
	}
}

void up(int cur){
	a[cur].s=a[a[cur].t[0]].s+a[a[cur].t[1]].s+1;
	a[cur].c=a[a[cur].t[0]].c+a[a[cur].t[1]].c+a[cur].d;	
}

void rotate(int cur){
	int u,v,l,r;
	u=a[cur].f;
	v=a[u].f;
	l=cur==a[u].t[1];
	r=l^1;
	if(v && !isroot(u))a[v].t[u==a[v].t[1]]=cur;
	a[cur].f=v;
	a[u].f=cur;
	a[u].t[l]=a[cur].t[r];
	if(a[cur].t[r])a[a[cur].t[r]].f=u;
	a[cur].t[r]=u;
	up(u);
	up(cur);
}

void splay(int cur){
	int i,u,v;
	t[0]=0;
	for(i=cur;!isroot(i);i=a[i].f){
		t[0]++;
		t[t[0]]=i;
	}
	down(i);
	for(i=t[0];i;i--)down(t[i]);
	while(!isroot(cur)){
		u=a[cur].f;
		v=a[u].f;
		if(!isroot(u)){
			if(u==a[v].t[0] ^ cur==a[u].t[0])rotate(cur);
			else rotate(u);
		}
		rotate(cur);
	}
}

void access(int cur){
	int pre;
	pre=0;
	while(cur){
		splay(cur);
		a[cur].d-=a[pre].c+a[pre].s;
		a[cur].d+=a[a[cur].t[1]].c+a[a[cur].t[1]].s;
		a[cur].t[1]=pre;
		up(cur);
		pre=cur;
		cur=a[cur].f;
	}
}

void changeroot(int cur){
	access(cur);
	splay(cur);
	a[cur].r^=1;
	swap(a[cur].t[0],a[cur].t[1]);
}

int get(int cur){
	if(!f[cur])return cur;
	else{
		f[cur]=get(f[cur]);
		return f[cur];
	}
}

int find(int cur,int n){
	int sum,size,ans;
	sum=0;
	while(cur){
		down(cur);
		size=a[a[cur].t[1]].c+a[a[cur].t[1]].s+a[cur].d+1;
		if((size+sum)<<1>=n){
			ans=cur;
			cur=a[cur].t[1];
		}else{
			sum+=size;
			cur=a[cur].t[0];
		}
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		g[i]=i;
		ans^=i;
		s[i]=1;
	}
	for(i=1;i<=m;i++){
		scanf("%s",c);
		if(c[0]=='A'){
			scanf("%d%d",&u,&v);
			x=get(u);
			y=get(v);
			if(s[x]<s[y]){
				swap(u,v);
				swap(x,y);
			}
			f[y]=x;
			s[x]+=s[y];
			changeroot(v);
			access(u);
			splay(u);
			a[v].f=u;
			a[u].d+=a[a[u].t[1]].s+a[a[u].t[1]].c;
			a[u].t[1]=v;
			up(u);
			changeroot(g[x]);
			access(g[y]);
			splay(g[x]);
			ans^=g[x]^g[y];
			g[x]=find(g[x],s[x]);
			splay(g[x]);
			if((a[a[g[x]].t[1]].s+a[a[g[x]].t[1]].c+a[g[x]].d+1)<<1==s[x]){
				for(j=a[g[x]].t[0];a[j].t[1];j=a[j].t[1])down(j);
				g[x]=min(g[x],j);
			}
			ans^=g[x];
		}else if(c[0]=='Q'){
			scanf("%d",&u);
			printf("%d\n",g[get(u)]);
		}else printf("%d\n",ans);
	}
	return 0;
}
