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
    @pre `num_elem` >= 0
    @param T: vector de elementos.
    @param num_elem: número de elementos.
    @return Posición del elemento si está, `-1` en otro caso
    @note Versión obvia (búsqueda secuencial)
 */
 int posicion_trivial(const int T[], int num_elem){
  for (int i = 0; i < num_elem; i++)
   if(T[i] == i)
    return i;
  return -1;
 }


 /**
    @brief Localiza un elemento en un vector ordenado
    @param T: vector de elementos.
    @param ini: Posición en la que se comienza a buscar
    @param fin: Posición en la que se termina
    @return Posición del elemento si está, `-1` en otro caso
    @note Función recursiva llamada por el *wrapper*
    @see posicion_dyv1
 */
 int posicion_dyv1_rec(const int T[], int ini, int fin){
 }

 /**
    @brief Localiza un elemento en un vector ordenado
    @pre `num_elem` >= 0
    @param T: vector de elementos.
    @param num_elem: número de elementos.
    @return Posición del elemento si está, `-1` en otro caso
    @note Versión divide y vencerás 1 (búsqueda binaria recursiva)
 */
 int posicion_dyv1(const int T[], int num_elem){
  return posicion_dyv1_rec(T, 0, num_elem - 1);
 }

 /**
    @brief Localiza un elemento en un vector ordenado
    @pre `num_elem` >= 0
    @param T: vector de elementos.
    @param num_elem: número de elementos.
    @return Posición del elemento si está, `-1` en otro caso
    @note Versión divide y vencerás 2 (búsqueda binaria no recursiva)
 */
 int posicion_dyv2(const int T[], int num_elem){
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

     if (argc != 3 || (argv[2][0] != 't' && argv[2][0] != '1' && argv[2][0] != '2'))
     {
       cerr << "Formato " << argv[0] << " <num_elem> t/1/2" << endl;
       return -1;
     }

   int n = atoi(argv[1]);

   if (argv[2][0] == 't')
      return ejecutar(posicion_trivial, n);
   else if (argv[2][0] == '1')
      return ejecutar(posicion_dyv1, n);
   else
      return ejecutar(posicion_dyv2, n);
 }
