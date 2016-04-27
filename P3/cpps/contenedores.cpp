/**
    @file Algoritmos para el ejercicio de contenedores
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Cont{
  int id;
  int peso;

  Cont(int i, int p){
    id = i;
    peso = p;
  }
};

bool compara(Cont p1, Cont p2){return p1.peso > p2.peso;}

/**
   @brief Toma el mayor número de contenedores
   @param p: pesos de los contenedores
   @param K: Capacidad máxima
   @return Vector de contenedores elegidos
*/
vector<int> max_num_conts(vector<int> p, int K){
 vector<Cont> conts;
 for(int i = 0; i < p.size(); i++)
   conts.push_back(Cont(i,p[i]));
 sort(conts.begin(), conts.end(), compara);

 vector<int> elegidos;
 int carga = 0;

 for(int i = 0; i < conts.size() && carga < K; i++){
   if(carga + conts[i].peso <= K){
     elegidos.push_back(conts[i].id);
     carga += conts[i].peso;
    }
 }

 return elegidos;
}

int main(){
 vector<int> pesos;
 int capacidad;
 vector<int> resultado;
 int k;
 cin >> capacidad;
 for(int i = 0; i < 10; i++){
    cin >> k;
    pesos.push_back(k);
  }
  for(int i = 0; i < (int) resultado.size(); i++)
    cout << resultado[i] << " ";
  cout << endl;
}
