#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=128;
const int M=65536;
const int X[4]={1,-1,0,0};
const int Y[4]={0,0,1,-1};

char a[N][N];
int p[N][N],b[N][N][5],ans[N][N][4];
int f[M],d[M],c[M],t[M];
int s[M][2];
bool g[N][N],h[N][N];
int n,m,i,j,k,l,r,q,x,y,u,v,e;

bool legal(int x,int y){
	return x && x<=n && y && y<=m;
}

void add(int u,int v,int w){
	b[u][v][0]++;
	b[u][v][b[u][v][0]]=w;
}

void dfs(int x,int y,int pre){
	int i,u,v,cur,tar,t;
	cur=p[x][y];
	k++;
	c[cur]=d[cur]=k;
	f[cur]=pre;
	t=0;
	q++;
	s[q][0]=x;
	s[q][1]=y;
	for(i=0;i<4;i++){
		u=x+X[i];
		v=y+Y[i];
		tar=p[u][v];
		if(legal(u,v) && a[u][v]!='S' && tar!=f[cur]){
			if(d[tar])c[cur]=min(c[cur],d[tar]);
			else{
				dfs(u,v,cur);
				c[cur]=min(c[cur],c[tar]);
				if(c[tar]>=d[cur]){
					g[x][y]=true;
					e++;
					while(!(s[q][0]==u && s[q][1]==v)){
						add(s[q][0],s[q][1],e);
						q--;
					}
					add(u,v,e);
					add(x,y,e);
					q--;
				}
				t++;
			}
		}
	}
	if(!pre && t==1)g[x][y]=false;
}

bool check(int u1,int v1,int u2,int v2,int u3,int v3){
	int i,j;
	if(!g[u1][v1])return true;
	for(i=1;i<=b[u2][v2][0];i++)
		for(j=1;j<=b[u3][v3][0];j++)
			if(b[u2][v2][i]==b[u3][v3][j])return true;
	return false;
}

int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			k++;
			p[i][j]=k;
		}
	k=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]!='S' && !d[p[i][j]]){
				q=0;
				dfs(i,j,0);
			}
	memset(h,false,sizeof(h));
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]=='M'){
				l=r=1;
				s[1][0]=i;
				s[1][1]=j;
				h[i][j]=true;
				break;
			}
	while(l<=r){
		x=s[l][0];
		y=s[l][1];
		for(i=0;i<4;i++){
			u=x+X[i];
			v=y+Y[i];
			if(legal(u,v) && (a[u][v]=='w' || a[u][v]=='K') && !h[u][v]){
				r++;
				h[u][v]=true;
				s[r][0]=u;
				s[r][1]=v;
			}
		}
		l++;
	}
	memset(ans,0x7,sizeof(ans));
	l=1;
	r=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]=='P'){
				for(k=0;k<4;k++){
					u=i+X[k];
					v=j+Y[k];
					if(h[u][v]){
						r++;
						s[r][0]=i;
						s[r][1]=j;
						t[r]=k;
						ans[i][j][k]=0;
					}
				}
			}
	while(l<=r){
		x=s[l][0];
		y=s[l][1];
		k=t[l];
		u=x-X[k];
		v=y-Y[k];
		if(u && u<=n && v && v<=m && a[u][v]!='S'){
			if(ans[u][v][k]>ans[x][y][k]+1){
				ans[u][v][k]=ans[x][y][k]+1;
				r++;
				s[r][0]=u;
				s[r][1]=v;
				t[r]=k;
				for(i=0;i<4;i++)
					if(legal(u+X[i],v+Y[i]) && i!=k && check(u,v,u+X[i],v+Y[i],u+X[k],v+Y[k]) && ans[u][v][i]>ans[u][v][k] && a[u+X[i]][v+Y[i]]!='S'){
						ans[u][v][i]=ans[u][v][k];
						r++;
						s[r][0]=u;
						s[r][1]=v;
						t[r]=i;
					}
			}
		}
		l++;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]=='K'){
				for(k=1;k<4;k++)ans[i][j][0]=min(ans[i][j][0],ans[i][j][k]);
				if(ans[i][j][0]!=ans[0][0][0])printf("%d\n",ans[i][j][0]);
				else printf("NO\n");
				break;
			}
	return 0;
}
