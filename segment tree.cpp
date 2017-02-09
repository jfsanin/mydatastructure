#include <iostream>
#include <vector>

using namespace std;

struct Segment{
   vector <int> st;
   vector <int> dt;
   int sz;
   void build(int p , int l, int r){
      if(l==r){
         st[p] = l;
      }
      else{
         build(2*p, l, (l+r)/2);
         build(2*p+1, (l+r)/2 + 1 , r);
         int p1 = st[2*p] , p2 = st[2*p+1];
         st[p] = (dt[p1] <= dt[p2]) ? p1 : p2;
      }
   }

   Segment(vector<int> data){
      sz = data.size();
      st.assign(5*sz,0);
      dt = data;
      build(1,0,sz-1);
   }

   int query(int p, int l, int r, int i, int j){
      if(i>r || j< l)
         return -1;
      else if(i<= l && j>=r){
         return st[p];
      }
      else{
         int lf = query(p*2, l, (l+r)/2, i, j);
         int rg = query(p*2 + 1, (l+r)/2+1, r, i, j);
         if(lf == -1) return rg;
         if(rg == -1) return lf;
         return dt[lf] < dt[rg] ? lf : rg;
      }
   }

   int update(int p, int l, int r, int id, int v){
      if(l==r)
         return st[p] = l;
      else{
         int rg = (l+r)/2 +1;
         rg <= id ? update(p*2+1, rg, r,id, v) : update(p*2, l, (l+r)/2,id, v);
         st[p] = dt[st[p*2]] < dt[st[p*2+1]] ? st[p*2] : st[p*2+1];
      }
   }

   void update(int p, int v){
      dt[p] = v;
      update(1,0,sz-1,p,v);
   }

   int query(int i, int j){
      int ans = query(1, 0, sz-1, i, j);
      return dt[ans];
   }
};

int main(){
   vector<int> data = {5,7,9,8,10};
   Segment sg(data);
   cout<<sg.query(2,3)<<endl;
   sg.update(4,1);
   cout<<sg.query(0,4)<<endl;
}
