/**
    @file Algoritmos para el ejercicio de la estación de ITV
  */

#include <iostream>
#include <sstream>
#include <chrono>
#include "gen_coches.h"
using namespace std::chrono;

peso_t max(const vector<int>& asignacion, const vector<peso_t>& v, int lineas) {
  vector<peso_t> max_cada_una(lineas, 0);
  for (int i = asignacion.size()-1; i >= 0; i--)
    max_cada_una[asignacion[i]] += v[i];

  return *max_element(max_cada_una.cbegin(), max_cada_una.cend());
}

void backtrack(const vector<peso_t>& p, vector<int>& asignados, vector<peso_t>& pesos_asignados, vector<int>& mejor, int lineas, peso_t& cota_max) {
  for (int i = 0; i < lineas; i++) {
    if ((pesos_asignados[i] += p[asignados.size()]) < cota_max) {
      asignados.push_back(i);
      if (asignados.size() < p.size())
        backtrack(p, asignados, pesos_asignados, mejor, lineas, cota_max);
      else {
        peso_t nueva_cota = *max_element(pesos_asignados.cbegin(), pesos_asignados.cend());
        if (nueva_cota < cota_max) {
          cota_max = nueva_cota;
          mejor = asignados;
        }
      }
      asignados.pop_back();
    }
    pesos_asignados[i] -= p[asignados.size()];
  }
}
bool mayor(pair<int, peso_t> a, pair<int, peso_t> b) { return a.second > b.second; }

vector<int> reparto_greedy(const vector<peso_t> p, int lineas) {
  vector<pair<int, peso_t> > p_indices;
  for (int i = p.size()-1; i >= 0; i--)
    p_indices.push_back(pair<int, peso_t>(i, p[i]));
  
  sort(p_indices.begin(), p_indices.end(), mayor);
  vector<int> elegidos(p.size());
  vector<peso_t> pesos_asignados(lineas, 0);  // Tiempo total de cada línea
  elegidos[p_indices.back().first] = 0;   // El mayor va a la primera línea
  pesos_asignados[0] = p_indices.back().second;
  p_indices.pop_back();
  
  while(!p_indices.empty()) {
    int linea_mas_vacia = 0;
    for (int i = 1; i < lineas; i++)
      if (pesos_asignados[i] < pesos_asignados[linea_mas_vacia])
        linea_mas_vacia = i;

    elegidos[p_indices.back().first] = linea_mas_vacia;
    pesos_asignados[linea_mas_vacia] += p_indices.back().second;
    p_indices.pop_back();
  }
  return elegidos;
}

vector<int> reparto_backtrack(const vector<peso_t> p, int lineas){
  vector<int> asignados, elegidos;
  vector<peso_t> pesos_asignados(lineas, 0);  // Tiempo total de cada línea
  asignados.push_back(0);  // Considera que el primer coche va a la primera línea
  pesos_asignados[0] = p.front();
  
  /* Toma como cota el máximo en un reparto greedy */
  peso_t cota_max = max(reparto_greedy(p, lineas), p, lineas);
  
  backtrack(p, asignados, pesos_asignados, elegidos, lineas, cota_max);

  return elegidos;
}

void print(const vector<int> v, const vector<peso_t> p, int lineas, ostream& os = cout) {
  os << "Tiempo de línea más ocupada: " << max(v, p, lineas) << " |-> ";
  for(int i = 0; i < p.size(); i++)
    os << i << " (" << p[i] << ") -> " << v[i] << ", ";
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
  vector<int> res;
  chrono::steady_clock::time_point ta, tb;
  chrono::duration<double> t;

  ta = chrono::steady_clock::now();
  res = reparto_backtrack(pesos, num_lineas);
  tb = chrono::steady_clock::now();
  print(res, pesos, num_lineas);
  t = chrono::duration_cast<chrono::duration<double>>(tb - ta);

  cout << "Tiempo (s): " << t.count() << endl;
}