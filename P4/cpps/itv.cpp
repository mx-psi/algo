/**
    @file Algoritmos para el ejercicio de la estación de ITV
  */

#include <iostream>
#include <sstream>
#include <chrono>
#include "gen_coches.h"
using namespace std::chrono;

struct Coche{
  int id;
  peso_t tiempo;

  Coche(int i, peso_t t){
    id = i;
    tiempo = t;
  }
};

vector<Coche> a_coches(const vector<peso_t> v) {
  vector<Coche> coches;
  for(int i = 0; i < v.size(); i++)
    coches.push_back(Coche(i,v[i]));

  return coches;
}

vector<vector<int> > reparto_backtrack(const vector<peso_t> p, int lineas){
  vector<Coche> conts = a_coches(p);

  vector<vector<int> > elegidos(lineas);

  /* Implementar backtrack aquí de forma que elegidos tome el mejor resultado encontrado */

  return elegidos;
}

peso_t suma(const vector<int>& pos, const vector<peso_t>& v){
  peso_t suma = 0;
  for(vector<int>::const_iterator it = pos.cbegin(); it != pos.cend(); ++it)
    suma += v[*it];
  return suma;
}

peso_t max(const vector<vector<int> >& pos, const vector<peso_t>& v){
  peso_t max = 0, prev_max;
  for(vector<vector<int> >::const_iterator it = pos.cbegin(); it != pos.cend(); ++it)
    if ((prev_max = suma(*it, v)) > max)
      max = prev_max;
  return max;
}

void print(const vector<vector<int> > v, const vector<peso_t> p, ostream& os = cout) {
  os << "Tiempo: " << max(v, p) << " |-> ";
  for(vector<vector<int> >::const_iterator i = v.cbegin(); i != v.cend(); ++i) {
    for(vector<int>::const_iterator j = i->begin(); j != i->end(); ++j)
      os << *j << " (" << p[*j] << ") ";
    os << '\n';
  }
  os << '\n';
}

void print(int m, const vector<peso_t> v, ostream& os = cout) {
  if (v.empty())
     return;
  os << m << ": [" << v[0];
  for(int i = 1; i < v.size(); i++)
    os << ", " << v[i];
  os << "]\n";
}

const int SMIN = 18, SMAX = 54, PMIN = 10, PMAX = 100;
const double RATIO = 1.0/8;

int main(int argc, char* argv[]) {
  vector<peso_t> pesos;
  int num_lineas;

  if (argc == 1 || (argc == 2 && argv[1][0] == 'n')) {
    srand(time(0));
    rand();  // "Quema" un número aleatorio: en Windows el primero es muy previsible
    pair<vector<peso_t>,int> datos;
    int cantidad;
    if (argc == 1)
      datos = gen_coches(SMIN,SMAX,PMIN,PMAX,RATIO,uniforme);
    else {
      stringstream(argv[1]+1) >> cantidad;
      datos = gen_coches(cantidad,cantidad,PMIN,PMAX,RATIO,uniforme);
    }
    pesos = datos.first;
    num_lineas = datos.second;
  }
  else if (argc == 2){
    stringstream str(argv[1]);
    str >> num_lineas;
    peso_t p;
    while(str >> p)
      pesos.push_back(p);
  }
  else {
    cerr << "Uso:\n  " << argv[0] << "                                               o\n  "
                       << argv[0] << " n(cantidad de coches)                         o\n  "
                       << argv[0] << " \"(cantidad de líneas) (tiempo1) (tiempo2)...\"";
    return -1;
  }
  print(num_lineas, pesos);
  vector<vector<int> > res;
  chrono::steady_clock::time_point ta, tb;
  chrono::duration<double> t;

  ta = chrono::steady_clock::now();
  res = reparto_backtrack(pesos, num_lineas);
  tb = chrono::steady_clock::now();
  print(res, pesos);
  t = chrono::duration_cast<chrono::duration<double>>(tb - ta);

  cout << "Tiempo (s): " << t.count() << endl;
}