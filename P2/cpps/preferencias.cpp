/**
   @file Cálculo de número de inversiones
*/


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include "shuffle.h"
using namespace std;


/**
   @brief Localiza un elemento en un vector
   
   @param T: vector de elementos.
   @param num_elem: número de elementos. num_elem >= 0
   @param a_buscar: entero a buscar en el vector

   Averigua la posición de un elemento en un vector
   no ordenado. Aplica búsqueda secuencial.
   Si no está, devuelve num_elem
*/
int find(const int T[], int num_elem, int a_buscar) {
   int pos;
   for (pos = 0; T[pos] != a_buscar && pos < num_elem; pos++);
   return pos;
}

/**
   @brief Calcula número de inversiones

   @param T1: primer  vector de elementos.
   @param T2: segundo vector de elementos.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de elementos que están en posición
   invertida en T2 respecto de T1.
   Aplica un algoritmo trivial.
*/
int preferencias_trivial(const int T1[], const int T2[], int num_elem) {
   int res = 0;
   for (int i = 0; i < num_elem-1; i++) {
      int pos_i = find(T2, num_elem, T1[i]);
      for (int j = i+1; j < num_elem; j++)
         if (find(T2, pos_i, T1[j]) != pos_i)
            res++;
   }
   return res;
}

/**
   @brief Calcula número de inversiones usando DyV

   @param T1: primer  vector de elementos.
   @param T2: segundo vector de elementos.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de elementos que están en posición
   invertida en T2 respecto de T1.
   Aplica un algoritmo Divide y Vencerás
*/
int preferencias_dyv(const int T1[], const int T2[], int num_elem) {
   int res = 0;
   // TODO: Rellenar
   return res;
}

int ejecutar(int (*f)(const int*, const int*, int), int n) {
  int* T1 = new int[n];
  int* T2 = new int[n];
  
  for (int i = 0; i < n; i++)
     T1[i] = T2[i] = i;

  srand(time(0));
  
  shuffle(T1, n);
  shuffle(T2, n);
  
  /*
  for (int i = 0; i < n; i++)
     cout << T1[i] << " ";
  
  cout << "\n";
  
  for (int i = 0; i < n; i++)
     cout << T2[i] << " ";
  
  cout << "\n\n";
  */

  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  tantes = chrono::steady_clock::now();
  int inversiones = f(T1, T2, n);
  tdespues = chrono::steady_clock::now();

  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << n << " " << inversiones << " " << transcurrido.count() << endl;
  delete [] T1;
  delete [] T2;

  return 0;
}

int main(int argc, char * argv[])
{

    if (argc != 3 || (argv[2][0] != 't' && argv[2][0] != 'd'))
    {
      cerr << "Formato " << argv[0] << " <num_elem> t/d" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  if (argv[2][0] == 't')
     return ejecutar(preferencias_trivial, n);
  else
     return ejecutar(preferencias_dyv, n);
}
