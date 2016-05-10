#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=65536;
const int M=666;
const int T=1333;

int a[M][T],b[M][T];
int c[N],s[M];
int next[M],pre[M];
int n,m,i,j,k,t,k1,k2,p1,p2,d,ans,head,tail;
char ch[2];

void split(int k){
	int i;
	t++;
	if(next[k]){
		pre[next[k]]=t;
		pre[t]=k;
		next[t]=next[k];
		next[k]=t;
	}else{
		next[k]=t;
		pre[t]=k;
		tail=t;
	}
	for(i=1;i<=M;i++){
		a[t][i]=b[t][i]=a[k][i+M];
		b[k][i]=a[k][i];
	}
	s[k]=s[t]=M;
	sort(b[k]+1,b[k]+s[k]+1);
	sort(b[t]+1,b[t]+s[t]+1);
}

void add(int k,int p,int d){
	int i;
	s[k]++;
	for(i=s[k];i>p;i--)a[k][i]=a[k][i-1];
	a[k][p]=d;
	i=s[k];
	while(i>1 && b[k][i-1]>d){
		b[k][i]=b[k][i-1];
		i--;
	}
	b[k][i]=d;
	if(s[k]==(M<<1))split(k);
}

void modify(int k,int p,int d){
	int i,q;
	q=lower_bound(b[k]+1,b[k]+s[k]+1,a[k][p])-b[k];
	b[k][q]=d;
	a[k][p]=d;
	while(q>1 && b[k][q]<b[k][q-1]){
		swap(b[k][q],b[k][q-1]);
		q--;
	}
	while(q<s[k] && b[k][q]>b[k][q+1]){
		swap(b[k][q],b[k][q+1]);
		q++;
	}
}

void find(int &k,int &p){
	int last;
	k=head;
	while(k && s[k]<p){
		p-=s[k];
		last=k;
		k=next[k];
	}
	if(!k){
		if(s[last]<M<<1){
			k=last;
			p=s[last]+1;
		}else{
			t++;
			next[tail]=k=t;
			pre[t]=tail;
			tail=t;
		}
	}
}

int sum(int k1,int p1,int k2,int p2,int d){
	int ans,i;
	ans=0;
	if(k1==k2){
		for(i=p1;i<=p2;i++)ans+=a[k1][i]<=d;
		return ans;
	}
	if(p1>1){
		for(i=p1;i<=s[k1];i++)ans+=a[k1][i]<=d;
		k1=next[k1];
	}
	if(p2<s[k2]){
		for(i=1;i<=p2;i++)ans+=a[k2][i]<=d;
		k2=pre[k2];
	}
	for(i=k1;i!=next[k2];i=next[i])ans+=upper_bound(b[i]+1,b[i]+s[i]+1,d)-b[i]-1;
	return ans;
}

int ask(){
	int l,r,mid;
	l=0;
	r=70000;
	while(l<=r){
		mid=(l+r)>>1;
		if(sum(k1,p1,k2,p2,mid)>=k)r=mid-1;
		else l=mid+1;
	}
	return l;
}

int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&c[i]);
	head=t=1;
	for(i=1;i<=n;i++){
		s[t]++;
		a[t][s[t]]=b[t][s[t]]=c[i];
		if(s[t]==M || i==n){
			sort(b[t]+1,b[t]+s[t]+1);
			if(i<n){
				next[t]=t+1;
				pre[t+1]=t;
				t++;
			}
		}
	}
	tail=t;
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%s",ch);
		if(ch[0]=='Q'){
			scanf("%d%d%d",&p1,&p2,&k);
			p1^=ans;
			p2^=ans;
			k^=ans;
			find(k1,p1);
			find(k2,p2);
			ans=ask();
			printf("%d\n",ans);
		}else if(ch[0]=='M'){
			scanf("%d%d",&p1,&d);
			p1^=ans;
			d^=ans;
			find(k1,p1);
			modify(k1,p1,d);
		}else{
			scanf("%d%d",&p1,&d);
			p1^=ans;
			d^=ans;
			find(k1,p1);
			add(k1,p1,d);
		}
	}
	return 0;
}
