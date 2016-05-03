/**
    @file Algoritmos para el ejercicio de contenedores
 */

#include <iostream>
#include <sstream>
#include "gen_contenedores.h"
using namespace std;


struct Cont{
  int id;
  peso_t peso;

  Cont(int i, peso_t p){
    id = i;
    peso = p;
  }
};

bool menor(Cont p1, Cont p2){ return p1.peso < p2.peso; }
bool mayor(Cont p1, Cont p2){ return p1.peso > p2.peso; }

vector<Cont> a_cont(vector<peso_t> v) {
  vector<Cont> conts;
  for(int i = 0; i < v.size(); i++)
    conts.push_back(Cont(i,v[i]));

  return conts;
}

/**
   @brief Toma el mayor número de contenedores
   @param p: pesos de los contenedores
   @param K: Capacidad máxima
   @return Vector de contenedores elegidos
*/
vector<int> max_num_conts(vector<peso_t> p, peso_t K){
  vector<Cont> conts = a_cont(p);

  sort(conts.begin(), conts.end(), menor);

  vector<int> elegidos;

  for(int i = 0; i < conts.size() && conts[i].peso <= K; i++){
    elegidos.push_back(conts[i].id);
    K -= conts[i].peso;
  }

  return elegidos;
}

vector<int> max_peso_greedy(vector<peso_t> p, peso_t capacidad){
  vector<Cont> conts = a_cont(p);

  sort(conts.begin(), conts.end(), mayor);

  vector<int> elegidos;

  for(int i = 0; i < conts.size() && capacidad > 0; i++){
    if(conts[i].peso <= capacidad){
      elegidos.push_back(conts[i].id);
      capacidad -= conts[i].peso;
    }
  }
  return elegidos;
}

peso_t suma(vector<Cont> v){
  peso_t suma = 0;
  for(vector<Cont>::iterator it = v.begin(); it != v.end(); ++it)
    suma += it->peso;
  return suma;
}

peso_t suma(vector<int> pos, vector<peso_t> v){
  peso_t suma = 0;
  for(vector<int>::iterator it = pos.begin(); it != pos.end(); ++it)
    suma += v[*it];
  return suma;
}

vector<Cont> bruto_sub(vector<Cont> p, peso_t K){
  if(p.empty() || K == 0)
    return vector<Cont>();

  peso_t max = 0;
  vector<Cont> max_v;
  for(vector<Cont>::iterator it = p.begin(); it != p.end() && max < K; ++it){
    vector<Cont>::iterator next(it);
    vector<Cont> orig_copy(++next, p.end());   // Copia todos los posteriores
    vector<Cont> v_candidato;
    if(it->peso > K)
      v_candidato = bruto_sub(orig_copy, K);
    else {
      v_candidato = bruto_sub(orig_copy, K-it->peso);
      v_candidato.push_back(*it);   // Si usamos listas, mejor usar push_front
    }
    peso_t suma1 = suma(v_candidato);
    if(suma1 > max && suma1 <= K){
      max = suma1;
      max_v = v_candidato;
    }
  }
  return max_v;
}

vector<int> max_peso_bruto(vector<peso_t> v, peso_t K){
  vector<Cont> v1 = a_cont(v);
  vector<Cont> v2 = bruto_sub(v1, K);
  vector<int> v3;
  for(int i = 0; i < v2.size(); i++)
    v3.push_back(v2[i].id);
  return v3;
}

void print(const vector<int> v, const vector<peso_t> p, ostream& os = cout) {
  os << "Suma total: " << suma(v, p) << " |-> ";
  for(int i = 0; i < v.size(); i++)
    os << v[i] << " (" << p[v[i]] << ") ";
  os << '\n';
}

void print(peso_t c, const vector<peso_t> v, ostream& os = cout) {
  if (v.empty())
     return;
  os << c << ": [" << v[0];
  for(int i = 1; i < v.size(); i++)
    os << ", " << v[i];
  os << "]\n";
}

const int SMIN = 3, SMAX = 12, PMIN = 10, PMAX = 100;
const double RATIO = 1.0/3;

int main(int argc, char* argv[]){
  vector<peso_t> pesos;
  peso_t capacidad;

  if (argc == 1) {
    srand(time(0));
    rand();  // "Quema" un número aleatorio: en Windows el primero es muy previsible
    pair<vector<peso_t>,peso_t> datos = gen_contenedores(SMIN,SMAX,PMIN,PMAX,RATIO,uniforme);
    pesos = datos.first;
    capacidad = datos.second;
  }
  else if (argc == 2){
    stringstream str(argv[1]);
    str >> capacidad;
    peso_t p;
    while(str >> p)
      pesos.push_back(p);
  }
  else {
    return -1;
  }
  print(capacidad, pesos);

  vector<int> res1 = max_num_conts(pesos, capacidad);
  vector<int> res2 = max_peso_greedy(pesos, capacidad);
  vector<int> res3 = max_peso_bruto(pesos, capacidad);
  print(res1, pesos);
  print(res2, pesos);
  print(res3, pesos);
}
