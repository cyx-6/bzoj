#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=1001000;
const int M=1e9+9;
const int C=28;

char a[N],b[N],c[N];
int f[N][4];
int g[4][4][C][C][C];
int n,m,i,j,k,t,u,v,w,x,y,z,l1,r1,l2,r2,l3,r3;

int main(){
	for(u=0;u<C;u++)
		for(v=0;v<C;v++)
			for(w=0;w<C;w++){
				l1=r1=u;
				if(u==27){
					l1=1;
					r1=26;
				}
				l2=r2=v;
				if(v==27){
					l2=1;
					r2=26;
				}
				l3=r3=w;
				if(w==27){
					l3=1;
					r3=26;
				}
				for(x=l1;x<=r1;x++)
					for(y=l2;y<=r2;y++)
						for(z=l3;z<=r3;z++){
							if(x==y && y==z)g[0][0][u][v][w]++;
							if(x==y && y<z)g[0][1][u][v][w]++;
							if(x<y && y==z)g[0][2][u][v][w]++;
							if(x<y && y<z)g[0][3][u][v][w]++;
							if(x==y)g[1][1][u][v][w]++;
							if(x<y)g[1][3][u][v][w]++;
							if(y==z)g[2][2][u][v][w]++;
							if(y<z)g[2][3][u][v][w]++;
							g[3][3][u][v][w]++;
						}
			}
	scanf("%d",&t);
	for(;t;t--){
		scanf("%s%s%s",a+1,b+1,c+1);
		n=x=strlen(a+1);
		y=strlen(b+1);
		z=strlen(c+1);
		n=max(n,y);
		n=max(n,z);
		for(i=1;i<=x;i++)a[i]=a[i]=='?'?27:a[i]-'a'+1;
		for(i=x+1;i<=n;i++)a[i]=0;
		for(i=1;i<=y;i++)b[i]=b[i]=='?'?27:b[i]-'a'+1;
		for(i=y+1;i<=n;i++)b[i]=0;
		for(i=1;i<=z;i++)c[i]=c[i]=='?'?27:c[i]-'a'+1;
		for(i=z+1;i<=n;i++)c[i]=0;
		f[0][0]=1;
		for(i=1;i<=n;i++){
			f[i][0]=f[i][1]=f[i][2]=f[i][3]=0;
			for(j=0;j<=3;j++)
				for(k=0;k<=3;k++){
					f[i][j]+=(long long)f[i-1][k]*g[k][j][a[i]][b[i]][c[i]]%M;
					if(f[i][j]>=M)f[i][j]-=M;
				}
		}
		printf("%d\n",f[n][3]);
	}
	return 0;
}
