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

double benford(){
 return (pow(10, uniforme())-1)/9;
}

double box_muller(double mu, double sigma){
 double r;
 do {
  r = mu+sqrt(-2*log(uniforme()))*cos(2*M_PI*uniforme())*sigma;   // Usa dos valores aleatorios uniformes distintos
 }while (r <= 0 || r >= 1);
 return r;
}

double box_muller(){
 return box_muller(0.5, 0.5);
}

pair<vector<peso_t>,int> gen_coches(int s_min, int s_max, int p_min, int p_max, double r, double (*f)()){
  int n = uniforme()*(s_max- s_min) + s_min;
  vector<peso_t> p(n);

  for(int i = 0; i < n; i++)
    p[i] = f()*(p_max - p_min) + p_min;

  int M = 2+n*r*(1+3*benford())/2.0;
  return pair<vector<peso_t>,int>(p,M);
}


#endif
