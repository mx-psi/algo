#ifndef __GENERADORES_H__
#define __GENERADORES_H__

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

typedef int peso_t;

double uniforme(){
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

pair<vector<peso_t>,peso_t> gen_contenedores(int s_min, int s_max, int p_min, int p_max){
  int n = uniforme()*(s_max- s_min) + s_min;
  vector<peso_t> p(n);

  for(int i = 0; i < n; i++)
    p[i] = uniforme()*(p_max- p_min) + p_min;

  int K = (p_min + p_max)*n/2.0;
  return pair<vector<peso_t>,peso_t>(p,K);
}


#endif