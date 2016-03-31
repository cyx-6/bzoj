#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define ll long long
#define N 100100
#define M 2050
#define K 12
#define P 998244353

int a[K],b[K],c[K];
int p[N],q[N];
int f[K][M];
int g[M];
int n,m,i,j,k,t;

int power(int x,int y){
    int t;
    if(!y)return 1;
    t=power(x,y>>1);
    t=(ll)t*t%P;
    if(y&1)t=(ll)t*x%P;
    return t;
}

int comb(int x,int y){
    return (ll)p[x]*q[x-y]%P*q[y]%P;
}

int main(){
    p[0]=1;
    for(i=1;i<N;i++)p[i]=(ll)p[i-1]*i%P;
    q[N-1]=power(p[N-1],P-2);
    for(i=N-2;~i;i--)q[i]=(ll)q[i+1]*(i+1)%P;
    for(i=0;i<K;i++)b[i]=1<<(K-i-1);
    memset(g,-1,sizeof(g));
    g[1]=0;
    for(i=1;i<M;i++){
        if((i<<1)>=M)break;
        if(g[i]>=0)g[i<<1]=g[i]+1;
    }
    t=0;
    scanf("%d",&n);
    while(n){
        for(i=0;i<K;i++)a[i]=0;
        m=0;
        for(i=1;i<=n;i++){
            scanf("%d",&k);
            if(g[k]>=0)a[g[k]]++;
            else m++;
        }
        for(i=0;i<K;i++){
            c[i]=min(a[i],b[i]);
            for(j=0;j<=b[i];j++)f[i][j]=0;
        }
        for(i=0;i<=c[0];i++)f[0][i]=comb(a[0],i);
        for(i=0;i<K-1;i++)
            for(j=0;j<=b[i];j++)
                if(f[i][j])
                    for(k=0;k<=c[i+1];k++)
                        if(k+(j>>1)<=b[i+1]){
                            f[i+1][k+(j>>1)]+=(ll)f[i][j]*comb(a[i+1],k)%P;
                            f[i+1][k+(j>>1)]%=P;
                        }else break;
        t++;
        printf("Case #%d: %lld\n",t,(ll)(power(2,n-m)-f[K-1][0]+P)*power(2,m)%P);
        scanf("%d",&n);
    }
    return 0;
}
