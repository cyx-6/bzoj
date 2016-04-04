#include<cstdlib>
#include<algorithm>
#include<cstdio>

using namespace std;

#define ll long long
#define llf long double

struct data{
	ll s[2][2];
};

data a,b;
ll n,m,p,x;

ll mul(ll a,ll b){
	ll k;
	k=a*b-(ll)((llf)a/m*b+1e-8)*m;
	return k<0?k+m:k;
}

data operator * (data u,data v){
	data w;
	w.s[0][0]=((mul(u.s[0][0],v.s[0][0])+mul(u.s[0][1],v.s[1][0])))%m;
	w.s[0][1]=((mul(u.s[0][0],v.s[0][1])+mul(u.s[0][1],v.s[1][1])))%m;
	w.s[1][0]=((mul(u.s[1][0],v.s[0][0])+mul(u.s[1][1],v.s[1][0])))%m;
	w.s[1][1]=((mul(u.s[1][0],v.s[0][1])+mul(u.s[1][1],v.s[1][1])))%m;
	return w;
}

data power(data x,ll y){
	data z;
	if(!y)return b;
	z=power(x,y>>1);
	if(y&1)return z*z*x;
	else return z*z;
}

int main(){
	scanf("%lld%lld%lld%lld%lld%lld",&m,&a.s[0][0],&a.s[0][1],&x,&n,&p);
	a.s[1][1]=b.s[0][0]=b.s[1][1]=1;
	a=power(a,n);
	printf("%lld\n",(mul(x,a.s[0][0])+a.s[0][1])%m%p);
	return 0;
}
