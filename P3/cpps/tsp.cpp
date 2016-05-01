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
#include "colonia.h"
using namespace std;

vector<int> tsp_1(const Grafo<peso_t>& g) {
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

vector<int> tsp_2(const Grafo<peso_t>& g) {
  return {24,13,15}; // TODO: algoritmo 2
}

vector<int> tsp_3(const Grafo<peso_t>& g) {
   Colonia c(g);
   for (int i = 0; i < 64; i++)
      c.itera(64);
   return c.itera(512);
}

void print(const vector<int> ids, bool a_archivo, ostream& os = cout) {
  for (vector<int>::const_iterator i = ids.begin(); i != ids.end(); ++i)
    os << (a_archivo ? (*i)+1 : *i) << (a_archivo ? '\n' : ' ');
 
  os << '\n';
}

string nombre_optimo(const char* nombre) {
  return string(nombre).substr(0, string(nombre).find_last_of(".")) + ".opt.tour";
}

peso_t longitud_desde_archivo(string nombre, const Grafo<peso_t>& g) {
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

int ejecutar(vector<int> (*f)(const Grafo<peso_t>&), const Grafo<peso_t>& g, bool a_archivo) {
  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  vector<int> ciclo;
  tantes = chrono::steady_clock::now();
  ciclo = f(g);
  tdespues = chrono::steady_clock::now();

  print(ciclo, a_archivo);
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  if (!a_archivo)
    cout << longitud(ciclo, g) << " " << transcurrido.count() << endl;

  return 0;
}

int main(int argc, char * argv[])
{
  if ((argc != 3 && argc != 4) || (argv[2][0] != '1' && argv[2][0] != '2' && argv[2][0] != '3') || (argc == 4 && argv[3][0] != 't'))
  {
    cerr << "Formato " << argv[0] << " [datos].tsp 1/2/3 [t]" << endl;
    return -1;
  }
  bool a_archivo = argc == 4;
  srand(time(0));
  int n;

  ifstream f(argv[1]);
  string s;
  if (!(f >> s))
     return -1;
  f >> n;
  Grafo<peso_t> g(n);
  double coordenadas[n][2];
  int id;
  double x, y;
  while(f >> id >> x >> y) {
     coordenadas[id-1][0] = x;
     coordenadas[id-1][1] = y;
  }
  g.pesosDesdeCoordenadas(coordenadas);

  if (a_archivo)
    cout << "DIMENSION: " << g.numNodos() << '\n';
  else
    cout << "Longitud óptima: " << longitud_desde_archivo(nombre_optimo(argv[1]), g) << '\n';
  if (argv[2][0] == '1')
     return ejecutar(tsp_1, g, a_archivo);
  else if (argv[2][0] == '2')
     return ejecutar(tsp_2, g, a_archivo);
  else
     return ejecutar(tsp_3, g, a_archivo);
}
