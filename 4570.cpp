#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

const int N=1001000;
const double M=1e16;
const double E=1e-8;

struct P{
	int x,y;
};

typedef P V;

V operator - (P u,P v){
	return (V){v.x-u.x,v.y-u.y};
}

long long operator * (V u,V v){
	return (long long)u.x*v.y-(long long)u.y*v.x;
}

P a[N],s[N];
int n,m,i,j,k;
double ans,u,v,w,sum;

int comp(P u,P v){
	return u.x<v.x || (u.x==v.x && u.y<v.y);
}

double slope(P u,P v){
	return u.x==v.x?M:(double)(u.y-v.y)/(u.x-v.x);
}

double calc(int p,double k){
	return fabs(k)<=E?M:s[p].x+s[p].y-k*s[p].x-s[p].y/k;
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,comp);
	for(i=1;i<=n;i++){
		while(m>=2 && (s[m]-s[m-1])*(a[i]-s[m-1])>=0)m--;
		m++;
		s[m]=a[i];
	}
	ans=M;
	for(i=1;i<=m;i++){
		if(i>1)u=slope(s[i-1],s[i]);
		else u=M;
		if(i<m)v=slope(s[i],s[i+1]);
		else v=-M;
		w=-sqrt((double)s[i].y/s[i].x);
		if(w<=u && w>=v)ans=min(ans,calc(i,w));
		else{
			if(i>1)ans=min(ans,calc(i,u));
			if(i<m)ans=min(ans,calc(i,v));
		}
	}
	printf("%.4lf\n",ans);
	return 0;
}
