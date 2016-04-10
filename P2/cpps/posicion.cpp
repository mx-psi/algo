/**
    @file Cálculo de el elemento en su posición
 */

 #include <iostream>
 #include <ctime>
 #include <cstdlib>
 #include <chrono>
 #include <unistd.h>
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
 for(int i = 0; i < n; i++)
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

int posicion_dyv_rec(const int v[], int n, int ajuste = 0){
  if(n == 1){
		if(v[0] == ajuste)
			return 0;
		else
			return -1;
	}

	int medio = n/2;

	if(medio == v[medio]-ajuste)
		return medio;
	else if(medio < v[medio]-ajuste)
		return posicion_dyv_rec(v, n/2, ajuste);
	else if(n == 2)
    return -1;
  else{
		int pos_rel_der = posicion_dyv_rec(v+medio+1, (n-1)/2, medio+1+ajuste);
		if(pos_rel_der != -1)
			return pos_rel_der+medio+1;
		else
			return -1;
	}
}

int posicion_dyv1(const int v[], int n){
  return posicion_dyv_rec(v,n);
}

 /**
  @brief Localiza un elemento en un vector ordenado
  @pre `n` >= 0
  @param v: vector de elementos.
  @param n: número de elementos.
  @return Posición del elemento si está, `-1` en otro caso
  @note Versión divide y vencerás 2 (no recursiva)
*/
int posicion_dyv2(const int v[], int n){
}


 int ejecutar(int (*f)(const int*, int), int n) {
   int* T = new int[n];
   get_elementoensuposicion(T, n);

    chrono::steady_clock::time_point tantes, tdespues;
   chrono::duration<double> transcurrido;

   tantes = chrono::steady_clock::now();
   f(T,n);
   tdespues = chrono::steady_clock::now();

   transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
   cout << n << " " << transcurrido.count() << endl;
   delete [] T;

   return 0;
 }

const int MAX = 100000;

 int ejecutar_media(int (*f)(const int*, int), int n, int MAX = MAX) {
   int* T = new int[n];
   double total = 0;
   for(int m = 0; m < MAX; m++){
     get_elementoensuposicion(T, n);

      chrono::steady_clock::time_point tantes, tdespues;
     chrono::duration<double> transcurrido;

     tantes = chrono::steady_clock::now();
     f(T,n);
     tdespues = chrono::steady_clock::now();

     transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
     total += transcurrido.count();
   }
   if(n != 5)
    cout << n << " " << total/MAX << endl;
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
    return ejecutar_media(posicion_obvia, n, MAX);
 else if (argv[2][0] == '1')
    return ejecutar_media(posicion_dyv1, n, MAX);
 else
    return ejecutar(posicion_dyv2, n);
 }
