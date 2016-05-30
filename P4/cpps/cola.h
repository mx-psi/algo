/*
   @file Cola con prioridad con capacidad de borrado para el problema del viajante
*/
#ifndef __COLA_H__
#define __COLA_H__

#include <algorithm>
#include <vector>
using namespace std;

template<class T, class Compare>
class cola_prioridad {
  vector<T> c;
  Compare comp;
public:
  cola_prioridad():c() {}
  bool empty() const {return c.empty();}
  unsigned size() const {return c.size();}
  const T& top() const {return c.front();}
  
  void push(T x) {
    c.push_back(x);
    push_heap(c.begin(), c.end(), comp);
  }

  void pop() {
    pop_heap(c.begin(), c.end(), comp);
    c.pop_back();
  }

  void remove_less_than(const T& x){
    c.erase(lower_bound(c.begin(), c.end(), x, comp), c.end());
  }
};

#endif
