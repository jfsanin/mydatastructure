#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

//All the Implementations are with trees
template <class E>
class DisjointSetDummy{
   unordered_map<E,E> sets; // This is going to keep the relation node-parent
   public :
   /*
   Each element is his own parent
   We have data.size() number of sets
   */
   void init(const vector<E> &data){
      for(E elem:data){
         sets[elem] = elem;
      }
   }

   /*
   Always the constructor in a class is called, but there is no rule about call init function,
   so it's good idea call in the constructor.
   */
   DisjointSetDummy(const vector<E> &data){
      init(data);
   }

   /*
   O(n) (I assume that equality takes O(1))
   this complexity is achieved because in the unionSet function we can increase the
   height of a set (or tree) at most n, i.e
   data = {1,2,3,4}
   unionSet(1,2)
   unionSet(2,3)
   unionSet(3,4)
   result = 1->2->3->4
   */
   E find(E elem){
      if(sets[elem]==elem){
         return elem;
      }
      else{
         return find(sets[elem]);
      }
   }

   //O(1) Constant time, (well I assume that assignation in the hashmap is O(1))
   void unionSet(E a, E b){
      sets[a] = b;
   }
};

/*
Complexity O(log(n))
See: https://en.wikipedia.org/wiki/Proof_of_O%28log*n%29_time_complexity_of_unionSet%E2%80%93find
*/

template <class E>
class DisjointSetWithoutPathCompression{
   unordered_map<E,E> sets;
   unordered_map<E,int> rank;
   public:
   /*
   Each element is his own parent
   We have data.size() number of sets
   */
   void init(const vector<E> &data){
      for(E elem:data){
         sets[elem] = elem;
         rank[elem] = 0;
      }
   }

   DisjointSetWithoutPathCompression(const vector<E> &data){
      init(data);
   }

   int find(E elem){
      if(sets[elem]==elem){
         return elem;
      }
      else{
         return find(sets[elem]);
      }
   }
   /*
   I use union-by-rank, there are three cases when items are going to be joined
   Let A,B the elements which are going to be joined, so we have:
   First : Rank of A is greater than Rank of B, so the root of A have to be the root of B's root, this does not change the rank of the set
   Second: Rank of A is lesser than Rank of B, so the root of B have to be the root of A's root, this does not change the rank of the set
   Third:  Rank of A is equal to Rank of B, so is possible to choose whichever element, find its root and attach the other element root
           to it, this increase the Rank of the new set in 1*/
   int unionSet(E a, E b){
      E aParent = find(a);
      E bParent = find(b);
      if(rank[aParent]>rank[bParent]){
         sets[bParent] = aParent;
      }
      else if(rank[aParent]<rank[bParent]){
         sets[aParent] = bParent;
      }
      else{
         sets[bParent] = aParent;
         ++rank[aParent];
      }
   }
};

/*
O(inverse ackerman function(n)), (almost constant)
This is a union-by-rank, path compression, disjoint-set
*/
template<class E>
class DisjointSet{
   unordered_map<E,E> sets; // This is going to keep the relation node-parent
   unordered_map<E,E> rank;
   public :
   /*
   Each element is his own parent
   We have data.size() number of sets
   */
   void init(const vector<E> &data){
      for(E elem:data){
         sets[elem] = elem;
         rank[elem] = 0;
      }
   }

   /*
   Always the constructor in a class is called, but there is no rule about call init function,
   so it's good idea call in the constructor.
   */
   DisjointSet(const vector<E> &data){
      init(data);
   }

   /*
   Path compression is a clever way to see that every time we ask for a root, we can decrease the lenght of the search of every node that is in the path from the element
   which we want to know to its root, just changing the parent of each node in the path to the root that was found. so every every node in the path are going to have a lenght of 1 node
   in the search the next time who someone ask.
   */
   E find(E elem){
      if(sets[elem]==elem){
         return elem;
      }
      else{
         E parent = find(sets[elem]);
         sets[elem] = parent;
         return parent;
      }
   }

   void unionSet(E a, E b){
      E aParent = find(a);
      E bParent = find(b);

      if(rank[aParent]>rank[bParent]){
         sets[bParent] = aParent;
      }
      else if(rank[aParent]< rank[bParent]){
         sets[aParent] = bParent;
      }
      else{
         sets[bParent] = aParent;
         ++rank[aParent];
      }
   }

};

void testDisjointSetDummy(){
   vector <int> data = {1,2,10,20};
   DisjointSetDummy <int> disjointSetDummy(data);

   //Test if all the elements are disjoint sets
   set<int> resultSets;
   for(int elem:data){
      resultSets.insert(disjointSetDummy.find(elem));
   }
   if(resultSets.size() == data.size()){
      cout<<"Initialization was correct"<<"\n";
   }
   else{
      cout<<"Initialization was not correct, or maybe was the find function!!"<<"\n";
   }

   //Test unionSet
   disjointSetDummy.unionSet(data[0],data[2]);
   disjointSetDummy.unionSet(data[1],data[3]);
   if(disjointSetDummy.find(data[0]) == disjointSetDummy.find(data[2]) &&
      disjointSetDummy.find(data[1]) == disjointSetDummy.find(data[3])){

      cout<<"unionSet works well"<<"\n";
   }
   else{
      cout<<"unionSet is not workin"<<"\n";
   }
}

void testDisjointSetWithoutPathCompression(){
   vector <int> data = {1,2,10,20};
   DisjointSetWithoutPathCompression <int> disjointSetWithoutPathCompression(data);

   //Test if all the elements are disjoint sets
   set<int> resultSets;
   for(int elem:data){
      resultSets.insert(disjointSetWithoutPathCompression.find(elem));
   }
   if(resultSets.size() == data.size()){
      cout<<"Initialization was correct"<<"\n";
   }
   else{
      cout<<"Initialization was not correct, or maybe was the find function!!"<<"\n";
   }

   //Test unionSet
   disjointSetWithoutPathCompression.unionSet(data[0],data[2]);
   disjointSetWithoutPathCompression.unionSet(data[1],data[3]);
   if(disjointSetWithoutPathCompression.find(data[0]) == disjointSetWithoutPathCompression.find(data[2]) &&
      disjointSetWithoutPathCompression.find(data[1]) == disjointSetWithoutPathCompression.find(data[3])){

      cout<<"unionSet works well"<<"\n";
   }
   else{
      cout<<"unionSet is not workin"<<"\n";
   }
}

void testDisjointSet(){
   vector <char> data = {'a','b','z','x'};
   DisjointSet <char> disjointSet(data);

   //Test if all the elements are disjoint sets
   set<char> resultSets;
   for(int elem:data){
      resultSets.insert(disjointSet.find(elem));
   }
   if(resultSets.size() == data.size()){
      cout<<"Initialization was correct"<<"\n";
   }
   else{
      cout<<"Initialization was not correct, or maybe was the find function!!"<<"\n";
   }

   //Test unionSet
   disjointSet.unionSet(data[0],data[2]);
   disjointSet.unionSet(data[3],data[1]);
   if(disjointSet.find(data[0]) == disjointSet.find(data[2]) &&
      disjointSet.find(data[1]) == disjointSet.find(data[3])){
      cout<<"unionSet works well"<<"\n";
   }
   else{
      cout<<"unionSet is not workin"<<"\n";
   }
}

int main(){
   testDisjointSetDummy();
   testDisjointSetWithoutPathCompression();
   testDisjointSet();
}
