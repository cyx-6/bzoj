#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

#define arr vector<int>
#define N 200200
#define M 400400

struct edge{
	int t,next;
};

arr a[N],s[N],t[N];
int b[N],f[N],d[N];
int n,m,i,j,k,u,v,w,ans;

void add(arr *a,int k,int d){
	a[k].insert(lower_bound(a[k].begin(),a[k].end(),d),d);
}

void del(arr *a,int k,int d){
	a[k].erase(lower_bound(a[k].begin(),a[k].end(),d));
}

int ask(arr *a,int k,int d){
	return a[k].size()-(upper_bound(a[k].begin(),a[k].end(),d)-a[k].begin());
}

void dfs(int cur,int pre){
	arr::iterator it;
	f[cur]=pre;
	if(b[pre] && a[b[pre]].size()<k)b[cur]=b[pre];
	else{
		b[cur]=cur;
		add(t,b[pre],cur);
	}
	add(a,b[cur],d[cur]);
	for(it=s[cur].begin();it!=s[cur].end();it++)
		if(*it!=pre)dfs(*it,cur);
}

void work(int cur,int del){
	arr::iterator it;
	ans+=ask(a,cur,del);
	for(it=t[cur].begin();it!=t[cur].end();it++)
		work(*it,del);
}

void solve(int cur,int del){
	arr::iterator it;
	if(b[cur]==cur)work(cur,del);
	else{
		ans+=d[cur]>del;
		for(it=s[cur].begin();it!=s[cur].end();it++)
			if(*it!=f[cur])solve(*it,del);
	}
}

void trans(int cur,int u,int v){
	arr::iterator it;
	if(b[cur]==cur){
		del(t,u,cur);
		add(t,v,cur);
	}else{
		del(a,u,d[cur]);
		add(a,v,d[cur]);
		b[cur]=v;
		for(it=s[cur].begin();it!=s[cur].end();it++)
			if(*it!=f[cur])trans(*it,u,v);
	}
}

void split(int cur){
	if(b[cur]==cur)del(t,b[f[cur]],cur);
	else{
		trans(cur,b[cur],cur);
		b[cur]=cur;
	}
	del(s,f[cur],cur);
	del(s,cur,f[cur]);
	f[cur]=0;
}

void modify(int cur,int tar){
	del(a,b[cur],d[cur]);
	d[cur]=tar;
	add(a,b[cur],d[cur]);
}

int main(){
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add(s,u,v);
		add(s,v,u);
	}
	for(i=1;i<=n;i++)scanf("%d",&d[i]);
	k=sqrt(n*100+1e-6);
	dfs(1,0);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d",&w);
		if(w!=3){
			scanf("%d%d",&u,&v);
			u^=ans;
			v^=ans;
		}else{
			scanf("%d",&u);
			u^=ans;
		}
		if(w==0){
			ans=0;
			solve(u,v);
			printf("%d\n",ans);
		}else if(w==1)modify(u,v);
		else if(w==2){
			n++;
			f[n]=u;
			d[n]=v;
			add(s,n,u);
			add(s,u,n);
			if(a[b[u]].size()<k){
				b[n]=b[u];
				add(a,b[u],v);
			}else{
				b[n]=n;
				add(a,n,v);
				add(t,b[u],n);
			}
		}else if(w==3)split(u);
	}
	return 0;
}
