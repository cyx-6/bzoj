#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

const int N=32;
const int T=1e4;

int a[N],s[N],t[N];
int n,m,i,j,k;
double ans,avg;

double sqr(double x){
	return x*x;
}

void sa(){
	double temp,sum,pre;
	int i,j,k,u,v;
	memset(s,0,sizeof(s));
	for(i=1;i<=n;i++){
		t[i]=rand()%m+1;
		s[t[i]]+=a[i];
	}
	sum=0;
	for(i=1;i<=m;i++)sum+=sqr(s[i]-avg);
	for(temp=T;temp>1e-1;temp*=0.9){
		k=rand()%n+1;
		u=t[k];
		if(temp<500)v=rand()%m+1;
		else v=min_element(s+1,s+m+1)-s;
		if(u==v)continue;
		pre=sum;
		sum-=sqr(s[u]-avg);
		sum-=sqr(s[v]-avg);
		s[u]-=a[k];
		s[v]+=a[k];
		sum+=sqr(s[u]-avg);
		sum+=sqr(s[v]-avg);
		if(sum<pre || rand()%T<temp)t[k]=v;
		else{
			s[u]+=a[k];
			s[v]-=a[k];
			sum=pre;
		}
	}
	ans=min(ans,sum);
}

int main(){
	srand(20160321);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		k+=a[i];
	}
	avg=(double)k/m;
	ans=1e15;
	for(i=1;i<=T;i++)sa();
	printf("%.2lf\n",sqrt(ans/m));
	return 0;
}
