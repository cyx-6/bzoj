#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=256;
const int M=64;
const int T=1e4;

struct data{
	int t;
	int s[M];
	void clear(){
		memset(s,0,sizeof(s));
	}
	void make(int c){
		clear();
		t=0;
		while(c){
			t++;
			s[t]=c%T;
			c/=T;
		}
		t=max(t,1);
	}
	void print(){
		int i;
		printf("%d",s[t]);
		for(i=t-1;i;i--)printf("%04d",s[i]);
		printf("\n");
	}
};

data operator * (data u,data v){
	int i,j;
	data w;
	w.clear();
	w.t=u.t+v.t-1;
	for(i=1;i<=u.t;i++)
		for(j=1;j<=v.t;j++)
			w.s[i+j-1]+=u.s[i]*v.s[j];
	for(i=1;i<=w.t;i++){
		w.s[i+1]+=w.s[i]/T;
		w.s[i]%=T;
	}
	if(w.s[w.t+1])w.t++;
	return w;
}

data operator + (data u,data v){
	int i,k;
	u.t=max(u.t,v.t);
	for(i=1;i<=u.t;i++)u.s[i]+=v.s[i];
	u.s[u.t+1]=0;
	for(i=1;i<=u.t;i++){
		u.s[i+1]+=u.s[i]/T;
		u.s[i]%=T;
	}
	if(u.s[u.t+1])u.t++;
	return u;
}

data operator + (data u,int c){
	data v;
	v.make(c);
	return u+v;
}

data operator / (data d,int c){
	int i,k;
	k=0;
	for(i=d.t;i;i--){
		k*=T;
		k+=d.s[i];
		d.s[i]=k/c;
		k%=c;
	}
	if(!d.s[d.t] && d.t)d.t--;
	return d;
}

data f[N];
data ans;
int n,m,i,j,k,u,v,w;

int main(){
	scanf("%d",&n);
	if(n==1){
		printf("1\n");
		return 0;
	}
	f[1].make(1);
	for(i=2;i<<1<=n;i++){
		f[i]=f[i-1];
		for(u=1;u<<1<i;u++){
			v=i-u-1;
			if(u==v)f[i]=f[i]+f[u]*(f[u]+1)/2;
			else f[i]=f[i]+f[u]*f[v];
		}
		for(u=1;u*3<i;u++)
			for(v=u;v*2<i-u;v++){
				w=i-1-u-v;
				if(u==v && v==w)f[i]=f[i]+f[u]*(f[u]+1)*(f[u]+2)/6;
				if(u==v && v<w)f[i]=f[i]+f[u]*(f[u]+1)/2*f[w];
				if(u<v && v==w)f[i]=f[i]+f[v]*(f[v]+1)/2*f[u];
				if(u<v && v<w)f[i]=f[i]+f[u]*f[v]*f[w];
			}
	}
	ans.make(0);
	ans=ans+f[n>>1]*(f[n>>1]+1)/2;
	for(u=1;u*3<n;u++)
		for(v=u;v*2<n-u;v++){
			w=n-1-u-v;
			if(w<<1>=n)continue;
			if(u==v && v==w)ans=ans+f[u]*(f[u]+1)*(f[u]+2)/6;
			if(u==v && v<w)ans=ans+f[u]*(f[u]+1)/2*f[w];
			if(u<v && v==w)ans=ans+f[v]*(f[v]+1)/2*f[u];
			if(u<v && v<w)ans=ans+f[u]*f[v]*f[w];
		}
	for(u=1;u*4<n;u++)
		for(v=u;v*3<n-u;v++)
			for(w=v;w*2<n-u-v;w++){
				k=n-1-u-v-w;
				if(k<<1>=n)continue;
				if(u==v && v==w && w==k)ans=ans+f[u]*(f[u]+1)*(f[u]+2)*(f[u]+3)/24;
				if(u==v && v==w && w<k)ans=ans+f[u]*(f[u]+1)*(f[u]+2)/6*f[k];
				if(u<v && v==w && w==k)ans=ans+f[v]*(f[v]+1)*(f[v]+2)/6*f[u];
				if(u==v && v<w && w<k)ans=ans+f[u]*(f[u]+1)/2*f[w]*f[k];
				if(u<v && v==w && w<k)ans=ans+f[v]*(f[v]+1)/2*f[u]*f[k];
				if(u<v && v<w && w==k)ans=ans+f[w]*(f[w]+1)/2*f[u]*f[v];
				if(u==v && v<w && w==k)ans=ans+(f[u]*(f[u]+1)/2)*(f[w]*(f[w]+1)/2);
				if(u<v && v<w && w<k)ans=ans+f[u]*f[v]*f[w]*f[k];
			}
	ans.print();
	return 0;
}
