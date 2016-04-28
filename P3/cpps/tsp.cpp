/**
   @file Algoritmos para el problema del viajante de comercio
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include "grafo.h"
using namespace std;

int ejecutar(int (*f)(const Grafo*), const Grafo*) {
  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  tantes = chrono::steady_clock::now();
  f(g);
  tdespues = chrono::steady_clock::now();

  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << n << " " << transcurrido.count() << endl;

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
  /* TODO: Leer tamaño desde archivo */
  Grafo g = new Grafo(n);
  peso_t coordenadas[n][2];
  /* TODO: Generar vector de coordenadas desde archivo */
  g.pesosDesdeCoordenadas(coordenadas);

  if (argv[2][0] == '1')
     return ejecutar(tsp_1, g);
  else if (argv[2][0] == '2')
     return ejecutar(tsp_2, g);
  else
     return ejecutar(tsp_3, g);
}
