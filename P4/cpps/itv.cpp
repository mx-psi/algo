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
  for (int i = 0; i < lineas && !(i && pesos_asignados[i-1] == pesos_asignados[i]); i++) {
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

bool mayor_tiempo_primero(const pair<int, peso_t>& a, const pair<int, peso_t>& b) {
  return a.second > b.second;
}

vector<int> reparto_greedy(const vector<peso_t>& p, int lineas) {
  vector<pair<int, peso_t> > p_indices;
  for (int i = p.size()-1; i >= 0; i--)
    p_indices.push_back(pair<int, peso_t>(i, p[i]));
  
  sort(p_indices.begin(), p_indices.end(), mayor_tiempo_primero);
  vector<int> elegidos(p.size());
  vector<peso_t> pesos_asignados(lineas, 0);  // Tiempo de cada línea
  vector<pair<int, peso_t> >::const_iterator it;
  int asignados = 0;
  for (it = p_indices.begin(); it != p_indices.end() && asignados < lineas; ++it, ++asignados) {
    elegidos[it->first] = asignados;          // Asigna a líneas distintas todos los coches de más tiempo
    pesos_asignados[asignados] += it->second;
  }
  
  for (; it != p_indices.end(); ++it) {
    int linea_mas_vacia = 0;
    for (int i = 1; i < lineas; i++)
      if (pesos_asignados[i] < pesos_asignados[linea_mas_vacia])
        linea_mas_vacia = i;

    elegidos[it->first] = linea_mas_vacia;    // Asigna los siguientes coches a la línea menos ocupada
    pesos_asignados[linea_mas_vacia] += it->second;
  }
  return elegidos;
}

vector<int> reparto_backtrack(const vector<peso_t>& p, int lineas){
  vector<int> asignados, elegidos;
  vector<peso_t> pesos_asignados(lineas, 0);  // Tiempo total de cada línea
  asignados.push_back(0);  // Considera que el primer coche va a la primera línea
  pesos_asignados[0] = p.front();
  
  /* Toma como cota el máximo en un reparto greedy */
  elegidos = reparto_greedy(p, lineas);
  peso_t cota_max = max(elegidos, p, lineas);
  
  backtrack(p, asignados, pesos_asignados, elegidos, lineas, cota_max);

  return elegidos;
}

void print(const vector<int>& v, const vector<peso_t>& p, int lineas, ostream& os = cout) {
  os << "Tiempo de línea más ocupada: " << max(v, p, lineas) << " |-> ";
  for(int i = 0; i < p.size(); i++)
    os << i << " (" << p[i] << ") -> " << v[i] << ", ";
  os << '\n';
}

void print(int m, const vector<peso_t>& v, ostream& os = cout) {
  if (v.empty())
     return;
  os << m << ": [" << v[0];
  for(int i = 1; i < v.size(); i++)
    os << ", " << v[i];
  os << "]\n";
}

const int SMIN = 18, SMAX = 54, PMIN = 10, PMAX = 100;
const double RATIO = 1.0/8;
const int MAX_COCHES = 18, NUM_TESTS = 100;

int compare(int num_lineas) {
  srand(time(0));
  rand();  // "Quema" un número aleatorio: en Windows el primero es muy previsible

  pair<vector<peso_t>,int> datos;
  vector<peso_t> pesos;
  peso_t t_greedy, t_backtrack;
  for (int i = num_lineas+1; i <= MAX_COCHES; i++) {
    t_greedy = t_backtrack = 0;
    for (int t = 0; t < NUM_TESTS; t++) {
      datos = gen_coches(i,i,PMIN,PMAX,RATIO,uniforme);
      pesos = datos.first;
      
      t_greedy    += max(reparto_greedy   (pesos, num_lineas), pesos, num_lineas);
      t_backtrack += max(reparto_backtrack(pesos, num_lineas), pesos, num_lineas);
    }
    double media_greedy    = t_greedy    * 1.0 / NUM_TESTS;
    double media_backtrack = t_backtrack * 1.0 / NUM_TESTS;
    cout << i << " " << media_greedy << " " << media_backtrack << '\n';
  }

  return 0;
}

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
  else if (argc == 2 && (argv[1]++)[0] == 'c') {
    stringstream str(argv[1]);
    str >> num_lineas;
    return compare(num_lineas);
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
                       << argv[0] << " c(cantidad de líneas)    o\n  "
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