/**
   @file Algoritmos para el problema del viajante de comercio
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include "grafo.h"
using namespace std;

vector<int> tsp_1(const Grafo& g) {
  vector<int> trayecto(1, 0);    // Empieza por un nodo arbitrario
  list<int> disponibles;
  for (int i = g.numNodos()-1; i > 0; i--)
    disponibles.push_front(i);

  while(!disponibles.empty()) {
    list<int>::const_iterator it = disponibles.begin(), cercano = it, fin = disponibles.end();
    int actual = trayecto.back();
    peso_t d_actual = g.peso(actual, *cercano);
    for (++it; it != fin; ++it) {
      peso_t d_candidato = g.peso(actual, *it);
      if (d_candidato < d_actual) {
        cercano = it;
        d_actual = d_candidato;
      }
    }

    trayecto.push_back(*cercano);
    disponibles.erase(cercano);
  }

  return trayecto;
}

vector<int> tsp_2(const Grafo& g) {
  return {24,13,15}; // TODO: algoritmo 2
}

vector<int> tsp_3(const Grafo& g) {
  return {19,20,21}; // TODO: algoritmo 3
}

peso_t longitud(const vector<int> ids, const Grafo& g) {
  peso_t l = g.peso(ids.back(), ids.front());
  for (int i = 1; i < ids.size(); i++)
    l += g.peso(ids[i], ids[i-1]);
  return l;
}

void print(const vector<int> ids, ostream& os = cout) {
  for (vector<int>::const_iterator i = ids.begin(); i != ids.end(); ++i)
    os << *i << " ";
 
  os << '\n';
}

string nombre_optimo(const char* nombre) {
  return string(nombre).substr(0, string(nombre).find_last_of(".")) + ".opt.tour";
}

peso_t longitud_desde_archivo(string nombre, const Grafo& g) {
  ifstream f(nombre);
  f.ignore(1024, '\n');
  int primero, actual, anterior;
  peso_t l = 0;
  f >> actual;
  primero = anterior = actual;
  while(f >> actual) {
    l += g.peso(anterior-1, actual-1);
    anterior = actual;
  }

  return l + g.peso(primero-1,actual-1);
}

int ejecutar(vector<int> (*f)(const Grafo&), const Grafo& g) {
  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  vector<int> ciclo;
  tantes = chrono::steady_clock::now();
  ciclo = f(g);
  tdespues = chrono::steady_clock::now();

  print(ciclo);
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << longitud(ciclo, g) << " " << transcurrido.count() << endl;

  return 0;
}

int main(int argc, char * argv[])
{
  if (argc != 3 || (argv[2][0] != '1' && argv[2][0] != '2' && argv[2][0] != '3'))
  {
    cerr << "Formato " << argv[0] << " [datos].tsp 1/2/3" << endl;
    return -1;
  }
  srand(time(0));
  int n;

  ifstream f(argv[1]);
  string s;
  if (!(f >> s))
     return -1;
  f >> n;
  Grafo g(n);
  peso_t coordenadas[n][2];
  int id;
  peso_t x, y;
  while(f >> id >> x >> y) {
     coordenadas[id-1][0] = x;
     coordenadas[id-1][1] = y;
  }
  g.pesosDesdeCoordenadas(coordenadas);

  cout << "Longitud óptima: " << longitud_desde_archivo(nombre_optimo(argv[1]), g) << '\n';
  if (argv[2][0] == '1')
     return ejecutar(tsp_1, g);
  else if (argv[2][0] == '2')
     return ejecutar(tsp_2, g);
  else
     return ejecutar(tsp_3, g);
}
