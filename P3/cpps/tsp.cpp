/**
   @file Algoritmos para el problema del viajante de comercio
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <ctime>
#include <utility>
#include <cstdlib>
#include <chrono>
#include "grafo.h"
#include "colonia.h"
using namespace std;

vector<int> tsp_1(const Grafo<peso_t>& g, const double coordenadas[][2] = 0) {
  vector<int> trayecto(1, 0);
  list<int> disponibles;
  for (int i = g.numNodos()-1; i > 0; i--)
    disponibles.push_front(i);

  while(!disponibles.empty()) {
    list<int>::iterator it = disponibles.begin(), cercano = it, fin = disponibles.end();
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

vector<int> triangulo_inicial(const double coordenadas[][2], int n) {
  vector<int> iniciales = {0,1,2};
  if (coordenadas[0][1] < coordenadas[1][1])
     swap(iniciales[0], iniciales[1]);
  if (coordenadas[iniciales[0]][1] < coordenadas[2][1])
     swap(iniciales[0], iniciales[2]);

  if (coordenadas[iniciales[1]][0] > coordenadas[iniciales[2]][0])
     swap(iniciales[1], iniciales[2]);
  for (int i = 3; i < n; i++)
     if (coordenadas[i][1] > coordenadas[iniciales[0]][1]) {
        if (coordenadas[iniciales[0]][0] < coordenadas[iniciales[1]][0])
           iniciales[1] = iniciales[0];
        else if (coordenadas[iniciales[0]][0] > coordenadas[iniciales[2]][0])
           iniciales[2] = iniciales[0];
        iniciales[0] = i;
     }
     else if (coordenadas[i][0] < coordenadas[iniciales[1]][0])
        iniciales[1] = i;
     else if (coordenadas[i][0] > coordenadas[iniciales[2]][0])
        iniciales[2] = i;

  return iniciales;
}

pair<int,list<int>::iterator> PesoNuevoCircuito(int nodo,list<int> & trayecto,const Grafo<peso_t> & g){
  list<int>::iterator pos_insercion = trayecto.begin(), i, tope = prev(trayecto.end());
  peso_t pesoMin = g.peso(*pos_insercion, nodo) + g.peso(nodo, *next(pos_insercion)) - g.peso(*pos_insercion, *next(pos_insercion));

  for(i = next(pos_insercion); i != tope; ++i)
  {
    int peso = g.peso(*i,nodo) + g.peso(nodo,*next(i)) - g.peso(*i, *next(i));

    if (peso < pesoMin){
      pesoMin = peso;
      pos_insercion = i;
    }
  }

  return pair<int,list<int>::iterator>(pesoMin, ++pos_insercion);
}


vector<int> tsp_2(const Grafo<peso_t>& g, const double coordenadas[][2]){
  vector<int> triangulo = triangulo_inicial(coordenadas, g.numNodos());  // Inicializamos el vector con las ciudades que forman el mayor triángulo en el grafo.

  list<int> disponibles;
  for (int i = 0; i < g.numNodos(); i++)
    if (i != triangulo[0] && i != triangulo[1] && i != triangulo[2])
       disponibles.push_front(i);

  list<int> trayecto_l(triangulo.begin(), triangulo.end());
  trayecto_l.push_back(trayecto_l.front());
  while (!disponibles.empty()){
    list<int>::iterator minimo = disponibles.begin();
    pair<int,list<int>::iterator> PesoIndiceMin = PesoNuevoCircuito(*minimo,trayecto_l,g);

    for(list<int>::iterator it = ++disponibles.begin(); it != disponibles.end(); it++){
      pair<int,list<int>::iterator> PesoIndicetmp = PesoNuevoCircuito(*it,trayecto_l,g);
      if(PesoIndiceMin.first > PesoIndicetmp.first){
        minimo = it;
        PesoIndiceMin=PesoIndicetmp;
      }
    }

    trayecto_l.insert(PesoIndiceMin.second,*minimo);
    disponibles.erase(minimo);
  }

  trayecto_l.pop_back();
  vector<int> trayecto(trayecto_l.begin(), trayecto_l.end());
  return trayecto;
}

vector<int> tsp_3(const Grafo<peso_t>& g, const double coordenadas[][2] = 0) {
   Colonia c(g);
   for (int i = 0; i < 64; i++)
      c.itera(64);
   return c.itera(512);
}

void print(const vector<int> ids, ostream& os = cout) {
  for (vector<int>::const_iterator i = ids.cbegin(); i != ids.cend(); ++i)
    os << ((*i)+1) << '\n';

  os << '\n';
}

string nombre_optimo(const char* nombre) {
  string nm(nombre);
  return nm.substr(0, nm.find_last_of(".")) + ".opt.tour";
}

string nombre_salida(const char* nombre, char num) {
  string nm(nombre);
  return "resultados" + nm.substr(nm.find("TSP"), nm.find(".tsp")-nm.find("TSP")) + "_" + num + ".tour";
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

int ejecutar(vector<int> (*f)(const Grafo<peso_t>&, const double[][2]), const Grafo<peso_t>& g, const double coordenadas[][2], ostream& fo) {
  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  vector<int> ciclo;
  tantes = chrono::steady_clock::now();
  ciclo = f(g, coordenadas);
  tdespues = chrono::steady_clock::now();

  print(ciclo, fo);
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << longitud(ciclo, g) << " " << transcurrido.count() << endl;

  return 0;
}

int main(int argc, char * argv[])
{
  if ((argc != 3 && argc != 4) || (argv[2][0] != '1' && argv[2][0] != '2' && argv[2][0] != '3' && argv[2][0] != 'o') || (argc == 4 && argv[3][0] != 't'))
  {
    cerr << "Formato " << argv[0] << " [datos].tsp 1/2/3/o [t]" << endl;
    return -1;
  }
  bool a_archivo = argc == 4;
  srand(time(0));
  int n;

  ifstream fin(argv[1]);
  string s;
  if (!(fin >> s))
     return -1;
  fin >> n;
  Grafo<peso_t> g(n);
  double coordenadas[n][2];
  int id;
  double x, y;
  while(fin >> id >> x >> y) {
     coordenadas[id-1][0] = x;
     coordenadas[id-1][1] = y;
  }
  g.pesosDesdeCoordenadas(coordenadas);

  ofstream fout;
  if (argv[2][0] != 'o') {
    fout.open(nombre_salida(argv[1], argv[2][0]));
    fout << "DIMENSION: " << g.numNodos() << '\n';

    if (argv[2][0] == '1')
      return ejecutar(tsp_1, g, coordenadas, fout);
    if (argv[2][0] == '2')
      return ejecutar(tsp_2, g, coordenadas, fout);
    if (argv[2][0] == '3')
      return ejecutar(tsp_3, g, coordenadas, fout);
  }

  cout << "Longitud óptima: " << longitud_desde_archivo(nombre_optimo(argv[1]), g) << endl;
  return 0;
}
