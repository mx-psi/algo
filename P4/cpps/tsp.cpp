/**
   @file Algoritmos para el problema del viajante de comercio
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include "grafo.h"
//#include <ctime>
//#include <cstdlib>

using namespace std;

//Luego se busca el mínimo recorriendo los relacionados de k-i para todo i en relacionados
vector<int> RelacionadosCon(int k, int max, vector<int> camino){
	vector<int> relacionados;
	for(int i = 1; i <= max; i++)
		if(find(camino.begin(), camino.end(), i) == camino.end() && i != k)
			relacionados.push_back(i);
	if(k != camino[camino.size()-1])
		relacionados.push_back(1);
	return relacionados;
}

/*
int Cotasion1(vector<int>& camino, Grafo<int>& g){
	int recorrido = 0;
	for(int i = 0; i < camino.size(); i++)
		recorrido += g.peso(camino[i], camino[i+1]);

}

int Ramificacion(vector<int>& camino, Grafo<int>& g){
}
*/

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
  /*
    if (argv[2][0] == '1')
      return ejecutar(tsp_1, g, coordenadas, fout);
    if (argv[2][0] == '2')
      return ejecutar(tsp_2, g, coordenadas, fout);
    if (argv[2][0] == '3')
      return ejecutar(tsp_3, g, coordenadas, fout);
    */
  }

  cout << "Longitud óptima: " << longitud_desde_archivo(nombre_optimo(argv[1]), g) << endl;
  return 0;
}
