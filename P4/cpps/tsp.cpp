/**
   @file Algoritmos para el problema del viajante de comercio
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include <climits>
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
  if(k != camino[camino.size()-1] || k == max-1)
    relacionados.push_back(1);
  return relacionados;
}

// Cota dada en el enunciado
int cota1(vector<int>& camino, const Grafo<int>& g){
	int recorrido = 0;
  // Peso del recorrido ya hecho
	for(int i = 0; i < camino.size()-1; i++)
		recorrido += g.peso(camino[i], camino[i+1]);

  // Para cada i halla el peso mínimo entre los relacionados
  for(int i = 0; i < g.numNodos(); i++){
    if((find(camino.begin(), camino.end(), i) == camino.end()) || (i == camino[camino.size()-1])){ // No toy seguro de la segunda parte del OR, que ha subido
      vector<int> v = RelacionadosCon(i,g.numNodos(),camino);
      int min = 0;
      for(int j = 0; j < v.size(); j++)
        if(g.peso(i,v[j]) < g.peso(i,min))
          min = v[j];
      recorrido += g.peso(i,min);
    }
  }
  return recorrido;
}

// Nuestra función de acotación
int cota2(vector<int>& camino, const Grafo<int>& g){
  return 0; // TODO
}

const int INFINITO = INT_MAX;

class Compare{
public:
  bool operator()(pair<vector<int>,int> a, pair<vector<int>,int> b){
    return a.second < b.second;
  }
};

vector<int> tsp_cota(const Grafo<peso_t>& g, int (*cota)(vector<int>&, const Grafo<int>&)) {
  priority_queue<pair<vector<int>,int>,vector<pair<vector<int>,int> >,Compare> cola;
  vector<int> inicial = {1}, mejor_camino;
  int mejor_longitud = INFINITO;
  cola.push({inicial,cota(inicial,g)});

  // Mientras haya caminos posiblemente mejores que el mejor encontrado
  while(!cola.empty() && cola.top().second < mejor_longitud){
    vector<int> camino_actual = cola.top().first;
    int cota_actual = cola.top().second;
    cola.pop();
    // No podemos formar directamente una solución
    if(camino_actual.size() < g.numNodos()- 2){
      for(int i = 0; i < g.numNodos(); i++){
        if(find(camino_actual.begin(), camino_actual.end(), i) == camino_actual.end()){
          vector<int> nuevo_camino = camino_actual;
          nuevo_camino.push_back(i);

          int nueva_cota = cota(nuevo_camino,g);
          if(nueva_cota < mejor_longitud)
            cola.push({nuevo_camino,nueva_cota});
        }
      }
    }
    else{// Podemos formar una solución
      for(int i = 0; i < g.numNodos(); i++){
        if(find(camino_actual.begin(), camino_actual.end(), i) == camino_actual.end()){
          vector<int> pos_sol = camino_actual;
          pos_sol.push_back(i);
          int long_sol = longitud(pos_sol, g);
          bool encontrado = false;

          // Añade el nodo restante (TODO: no sé si cambiar esto)
          for(int j = 0; !encontrado && j < g.numNodos(); j++)
            if(find(pos_sol.begin(), pos_sol.end(), i) == pos_sol.end()){
              pos_sol.push_back(j);
              encontrado = true;
            }

          // Actualiza la mejor solución
          if(long_sol < mejor_longitud){
            mejor_longitud = long_sol;
            mejor_camino = pos_sol;
          }
        }
      }
    }
  }
  return mejor_camino;
}

vector<int> tsp_1(const Grafo<peso_t>& g) {
  return tsp_cota(g,cota1);
}

vector<int> tsp_2(const Grafo<peso_t>& g) {
  return tsp_cota(g,cota2);
}

vector<int> tsp_3(const Grafo<peso_t>& g) {
  // TODO: Backtracking con función de acotación descrita
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
  int barpos = nm.find_last_of("\\/")+1;
  return "resultadosTSP/" + nm.substr(barpos, nm.find(".tsp")-barpos) + "_" + num + ".tour";
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

int ejecutar(vector<int> (*f)(const Grafo<peso_t>&), const Grafo<peso_t>& g, ostream& fo) {
  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  vector<int> ciclo;
  tantes = chrono::steady_clock::now();
  ciclo = f(g);
  tdespues = chrono::steady_clock::now();

  print(ciclo, fo);
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << longitud(ciclo, g) << " " << transcurrido.count() << endl;

  return 0;
}

vector<int> (*const tsp[])(const Grafo<peso_t>&) = {tsp_1, tsp_2, tsp_3};

int main(int argc, char * argv[])
{
  if ((argc != 3 && argc != 4) || ((argv[2][0] < '1' || argv[2][0] > '3') && argv[2][0] != 'o') || (argc == 4 && argv[3][0] != 't'))
  {
    cerr << "Formato " << argv[0] << " [datos].tsp 1/2/3/o [t]" << endl;
    return -1;
  }
  srand(time(0));
  int n;

  ifstream fin(argv[1]);
  string s;
  if (!(fin >> s)){
     cerr << "El fichero de datos no ha podido leerse correctamente." << endl;
     return -1;
  }
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
    return ejecutar(tsp[argv[2][0] - '1'], g, fout);
  }

  cout << "Longitud óptima: " << longitud_desde_archivo(nombre_optimo(argv[1]), g) << endl;
  return 0;
}
