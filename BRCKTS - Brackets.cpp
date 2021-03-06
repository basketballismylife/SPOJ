#include <bits/stdc++.h>
using namespace std ;

#define inf 0x3f3f3f3f
#define INF 1000111000111000111LL
#define mod (lli)1000000007
#define endl '\n'
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define fi first
#define se second
#define all(cc) (cc).begin(),(cc).end()
using lli = long long int ;
using pii = pair<int, int> ;
using vi = vector<int> ;
using vb = vector<bool> ;
using vvi = vector<vector<int>> ;
using vlli = vector<long long int> ;
using vpii = vector<pair<int, int>> ;

int left (int p) { return p<<1 ; }
int right(int p) { return (p<<1)+1 ; }

int T, n, q, t ;
pii z ;
string s ;
vpii tree ;

pii merge(pii x, pii y)
  {
    int c=min(x.fi, y.se) ;
    return mp(x.fi+y.fi-c, x.se+y.se-c) ;
  }

void build(int p, int l, int r)
  {
    if(l==r)
      {
        if(s[l]=='(') tree[p]=mp(1, 0) ;
        else tree[p]=mp(0, 1) ;
      }
    else
      {
        build(left(p), l, (l+r)/2) ;
        build(right(p), (l+r)/2 + 1, r) ;
        pii x=tree[left(p)] ;
        pii y=tree[right(p)] ;
        tree[p]=merge(x, y) ;
      }
  }

pii query(int p, int l, int r, int lq, int rq)
  {
    if(lq>r || rq<l) return mp(0, 0) ;
    if(lq<=l && rq>=r) return tree[p] ;
    pii x=query(left(p), l, (l+r)/2, lq, rq) ;
    pii y=query(right(p), (l+r)/2 + 1, r, lq, rq) ;
    return merge(x, y) ;
  }

void update(int p, int l, int r, int idx)
  {
    if(idx<l || idx>r) return ;
    if(l==r)
      {
        if(s[l]=='(') tree[p]=mp(1, 0) ;
        else tree[p]=mp(0, 1) ;
        return ;
      }
    update(left(p), l, (l+r)/2, idx) ;
    update(right(p), (l+r)/2 +1, r, idx) ;
    pii x=tree[left(p)] ;
    pii y=tree[right(p)] ;
    tree[p]=merge(x, y) ;
  }

int main()
  {
    ios_base::sync_with_stdio (false) ; cin.tie(0) ; cout.tie(0) ;
    T=1 ;
    while(cin>> n >> s)
      {
        z=mp(0, 0) ;
        tree.assign(4*n+1, z) ;
        build(1, 0, n-1) ;
        cout<< "Test " << T++ << ":" << endl ;
        cin>> q ;
        for(int i=0 ; i<q ; i++)
          {
            cin>> t ;
            if(t)
              {
                t-- ;
                if(s[t]=='(') s[t]=')' ;
                else s[t]='(' ;
                update(1, 0, n-1, t) ;
              }
            else
              {
                z=query(1, 0, n-1, 0, n-1) ;
                if(!z.fi && !z.se) cout<< "YES" << endl ;
                else cout<< "NO" << endl ;
              }
          }
      }
  }
