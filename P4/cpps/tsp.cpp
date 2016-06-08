/**
   @file Algoritmos para el problema del viajante de comercio
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <utility>
#include <algorithm>
#include <chrono>
#include "grafo.h"

using namespace std;

#define INFINITO 2147483647;
vector<int> tsp_greedy(const Grafo<peso_t>& g) {
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


//Luego se busca el mínimo recorriendo los relacionados de k-i para todo i en relacionados
vector<int> RelacionadosCon(int k, int max, vector<int> camino){
  vector<int> relacionados;
  for(int i = 0; i < max; i++)
    if(find(camino.begin(), camino.end(), i) == camino.end() && i != k)
      relacionados.push_back(i);
  if(k != camino.back() || k == max-1)
    relacionados.push_back(1);
  return relacionados;
}

// Cota dada en el enunciado
int cota1(vector<int>& camino, const Grafo<int>& g){
	int recorrido = 0;
	for(int i = 0; i < camino.size()-1; i++)
		recorrido += g.peso(camino[i], camino[i+1]);

  for(int i = 0; i < g.numNodos(); i++){
    if((i == camino.back()) || (find(camino.begin(), camino.end(), i) == camino.end())){
      vector<int> v = RelacionadosCon(i,g.numNodos(),camino);
      int min = v[0];
      for(int j = 1; j < v.size(); j++){
        if(g.peso(i,v[j]) < g.peso(i,min))
          min = v[j];
      }
      recorrido += g.peso(i,min);
    }
  }
  return recorrido;
}

bool GeneraCiclos(vector<vector<pair<int,int> > > aristas, pair<int, int> arista_nueva){
  bool genera = false;
  bool genera1,genera2;
  for(vector<vector<pair<int,int> > >::iterator it = aristas.begin(); it != aristas.end() && !genera; ++it){
    genera1 = genera2 = false;
    for(vector<pair<int,int> >::iterator it2 = it->begin(); it2 != it->end() && (!genera1 || !genera2); ++it2){
      if((it2->first == arista_nueva.first) || (it2->second == arista_nueva.first))
        genera1 = true;
      if((it2->first == arista_nueva.second) || (it2->second == arista_nueva.second))
        genera2 = true;
    }
    genera = genera1 && genera2;
  }
  return genera || (arista_nueva.first == arista_nueva.second);
}

pair<int, int> MenorAristaSiguiente(vector<vector<pair<int,int> > > aristas, const Grafo<int>& g){
  pair<int,int> par_min;
  int minimo = INFINITO;
  for(int i = 0; i < g.numNodos(); i++){
    for(int j = 0; j < g.numNodos(); j++){
      if(g.peso(i,j) < minimo && !GeneraCiclos(aristas, pair<int,int>(i,j))){
        minimo = g.peso(i,j);
        par_min = pair<int,int>(i,j);
      }
    }
  }
  return par_min;
}

bool CompartenNodo(vector<pair<int,int> > v1, vector<pair<int,int> > v2){
  bool encontrado = false;
  for(int i = 0; i < v1.size() && !encontrado; i++){
    for(int j = 0; j < v2.size() && !encontrado; j++){
      encontrado = v1[i].first == v2[j].first || v1[i].first == v2[j].second || v1[i].second == v2[j].first || v1[i].second == v2[j].second;
    }
  }
  return encontrado;
}

template <class T>
vector<T> union_vec(const vector<T>& v1, const vector<T>& v2){
  vector<T> nuevo(v1);
  for(int i = 0; i < v2.size(); i++)
    if(find(nuevo.begin(), nuevo.end(), v2[i]) == nuevo.end())
      nuevo.push_back(v2[i]);
  return nuevo;
}

void RecomponerAristas(vector<vector<pair<int,int> > >& aristas){
  vector<vector<pair<int,int> > > nuevo;
  bool encontrado;
  for(vector<vector<pair<int,int> > >::iterator it1 = aristas.begin(); it1 != aristas.end(); ++it1){
    encontrado = false;
    for(vector<vector<pair<int,int> > >::iterator it2 = nuevo.begin(); (it2 != nuevo.end()) && !encontrado; ++it2){
      if(CompartenNodo(*it1, *it2)){
        *(it2) = union_vec(*it1, *it2);
        encontrado = true;
      }
    }
    if(!encontrado)
      nuevo.push_back(*it1);
  }
  aristas = nuevo;
}
// Nuestra función de acotación
int cota2(vector<int>& camino, const Grafo<int>& g){
  int recorrido = 0;// Peso del recorrido ya hecho
  vector<vector<pair<int,int> > > aristas;
  vector<pair<int,int> > arista;
  int total_aristas = camino.size()-1;

  for(int i = 0; i < camino.size()-1; i++){
    recorrido += g.peso(camino[i], camino[i+1]);
    arista.push_back(pair<int,int>(camino[i],camino[i+1]));
   }
  aristas.push_back(arista);
  arista.clear();

  while(total_aristas < g.numNodos()-1){
    pair<int,int> par_nuevo = MenorAristaSiguiente(aristas, g);
    arista.push_back(par_nuevo);
    aristas.push_back(arista);
    recorrido += g.peso(par_nuevo.first, par_nuevo.second);
    RecomponerAristas(aristas);
    arista.clear();
    total_aristas++;
  }
  int minimo = INFINITO;
  for(int i = 1; i < g.numNodos(); i++)
    if(g.peso(0,i) < minimo && (find(camino.begin(), camino.end(), i) == camino.end()))
      minimo = g.peso(0,i);
  return recorrido + minimo;
}
class Compare{
public:
  bool operator()(pair<vector<int>,int> a, pair<vector<int>,int> b){
    return a.second > b.second;
  }
};

vector<int> tsp_cota(const Grafo<peso_t>& g, int (*cota)(vector<int>&, const Grafo<int>&)) {
  priority_queue<pair<vector<int>,int>,vector<pair<vector<int>,int> >,Compare> cola;
  vector<int> inicial = {0}, mejor_camino = tsp_greedy(g);
  int mejor_longitud = longitud(mejor_camino,g);
  cola.push({inicial,cota(inicial,g)});

  // Mientras haya caminos posiblemente mejores que el mejor encontrado
  while((!cola.empty()) && (cola.top().second < mejor_longitud)){
    vector<int> camino_actual = cola.top().first;
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

          // Añade el otro nodo
          bool encontrado = false;
          for(int j = 0; !encontrado && j < g.numNodos(); j++){
            if(find(pos_sol.begin(), pos_sol.end(), j) == pos_sol.end()){
              pos_sol.push_back(j);
              encontrado = true;
            }
          }

          int long_sol = longitud(pos_sol, g);

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

void tsp_back_rec(vector<int>& solucion, vector<int> camino_actual, int& mejor_longitud, const Grafo<peso_t>& g){
	if(camino_actual.size() < g.numNodos()){
		for(int i = 0; i < g.numNodos(); i++){
			if(find(camino_actual.begin(), camino_actual.end(), i) == camino_actual.end()){
		      		vector<int> nuevo_camino = camino_actual;
		      		nuevo_camino.push_back(i);

		      		if(longitud(camino_actual,g) < mejor_longitud){
					//num_veces_expandidos_3++;
		      			tsp_back_rec(solucion,nuevo_camino,mejor_longitud,g);
				}
				else
					;//num_veces_poda_3++;
					
				
			}
		}
	}
	else{ // Habemus camino completo
		if(longitud(camino_actual,g) < mejor_longitud){
			mejor_longitud = longitud(camino_actual,g);
			solucion = camino_actual;
		}
		else
			;//num_veces_poda_3++;
	}
}
vector<int> tsp_backtracking(const Grafo<peso_t>& g) {
	vector<int> primera_solucion = tsp_greedy(g);
	int mejor_longitud = longitud(primera_solucion,g);
	vector<int> inicial = {0};
	vector<int> solucion; // se modifica éste

	tsp_back_rec(solucion,inicial,mejor_longitud,g);

	return solucion;
}

vector<int> tsp_1(const Grafo<peso_t>& g) {
  return tsp_cota(g,cota1);
}

vector<int> tsp_2(const Grafo<peso_t>& g) {
  return tsp_cota(g,cota2);
}

vector<int> tsp_3(const Grafo<peso_t>& g) {
	return tsp_backtracking(g);
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
  /*
  for(int i = 1; i < ciclo.size(); i++){
    cout << ciclo[i-1] << "-" << ciclo[i] << "->" << g.peso(ciclo[i-1], ciclo[i]) << "\n";
  }
  cout << ciclo[ciclo.size()-1] << "-0->" << g.peso(ciclo[ciclo.size()-1], 0) << "\n";
  cout << "\n";
  */
  cout << longitud(ciclo, g) << " " << transcurrido.count() << endl;
//  cout << "Número de nodos expandidos: " << num_nodos_expandidos_3 << endl;
//  cout << "Número de veces que se poda: " << num_veces_poda_3 << endl;
//  cout << "Tamaño máximo de nodos vivos en la cola: " << "---" << endl;

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
