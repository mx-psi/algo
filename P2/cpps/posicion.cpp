/**
    @file Cálculo de el elemento en su posición
 */

 #include <iostream>
 #include <ctime>
 #include <cstdlib>
 #include <chrono>
 #include "generadores.h"
 using namespace std;


/**
   @brief Localiza un elemento en un vector ordenado
   @pre `n` >= 0
   @param v: vector de elementos.
   @param v: número de elementos.
   @return Posición del elemento si está, `-1` en otro caso
   @note Versión obvia (búsqueda secuencial)
*/
int posicion_obvia(const int v[], int n){
 for (int i = 0; i < n; i++)
  if(v[i] == i)
   return i;
 return -1;
}

/**
  @brief Localiza un elemento en un vector ordenado
  @pre `n` >= 0
  @param v: vector de elementos.
  @param n: número de elementos.
  @return Posición del elemento si está, `-1` en otro caso
  @note Versión divide y vencerás 1 (recursiva)
*/
int posicion_dyv1(const int v[], int n){
}

 /**
  @brief Localiza un elemento en un vector ordenado
  @pre `n` >= 0
  @param v: vector de elementos.
  @param n: número de elementos.
  @return Posición del elemento si está, `-1` en otro caso
  @note Versión divide y vencerás 2 (no recursiva)
*/
int posicion_dyv2(const int T[], int n){
}


 int ejecutar(int (*f)(const int*, int), int n) {
   int* T = new int[n];
   get_elementoensuposicion(T, n);

    chrono::steady_clock::time_point tantes, tdespues;
   chrono::duration<double> transcurrido;

   tantes = chrono::steady_clock::now();
   int i = f(T,n);
   tdespues = chrono::steady_clock::now();

   transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
   cout << n << " " << i << " " << transcurrido.count() << endl;
   delete [] T;

   return 0;
 }

 int main(int argc, char * argv[])
 {

 if (argc != 3 || (argv[2][0] != 't' && argv[2][0] != '1' && argv[2][0] != '2')){
  cerr << "Formato " << argv[0] << " <num_elem> t/1/2" << endl;
  return -1;
 }

 int n = atoi(argv[1]);

 if (argv[2][0] == 't')
    return ejecutar(posicion_obvia, n);
 else if (argv[2][0] == '1')
    return ejecutar(posicion_dyv1, n);
 else
    return ejecutar(posicion_dyv2, n);
 }
