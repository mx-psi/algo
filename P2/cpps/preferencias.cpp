/**
   @file Cálculo de número de inversiones
*/


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include "generadores.h"
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

   @param T: vector de elementos.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de parejas de elementos que se encuentran
   en una posición invertida respecto de su contenido.
   Aplica un algoritmo trivial de eficiencia O(n^2).
*/
int preferencias_trivial( int T[], int num_elem) {
   int res = 0;
   for (int i = 0; i < num_elem-1; i++)
      for (int j = i+1; j < num_elem; j++)
         if (T[i] > T[j])
            res++;

   return res;
}

static int fusion(int T[], int inicial, int final, int U[], int V[])
{
  int j = 0;
  int k = 0;
  int merges = 0;

  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k])
      {
	       T[i] = U[j];
          j++;
      }

    else{
	     T[i] = V[k];
        merges += (final - inicial)/2-inicial-j;
	      k++;

      }

    }


  return merges;
}

static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}





/**
*@brief
*@param T[]
*@param inicial
*@param final
*/

const int UMBRAL_MS = 2;

static int mergesort_lims(int T[], int inicial, int final)
{
  int merges = 0;

  if(final - inicial < UMBRAL_MS)
  {
      merges = preferencias_trivial(T+inicial, final-inicial);
      insercion_lims(T, inicial, final);
  }


    else{
      int k = (final - inicial)/2;

      int * U = new int [k - inicial + 1];

      int l, l2;

      for (l = 0, l2 = inicial; l < k; l++, l2++)
	     U[l] = T[l2];

       U[l] = INT_MAX;

      int * V = new int [final - k + 1];

      for (l = 0, l2 = k; l < final - k; l++, l2++)
	     V[l] = T[l2];

      V[l] = INT_MAX;

      merges+=mergesort_lims(U, 0, k);
      merges+=mergesort_lims(V, 0, final - k);
      merges+= fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };

    return merges;
}

/**
   @brief Calcula número de inversiones usando DyV

   @param T: vector de elementos.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de parejas de elementos que se encuentran
   en una posición invertida respecto de su contenido.
   Aplica un algoritmo Divide y Vencerás
*/
int preferencias_dyv( int T[], int num_elem) {
   return mergesort_lims(T, 0, num_elem);
}

int ejecutar(int (*f)(int*, int), int n) {
  int* T = new int[n];
  get_preferencias(T, n);

  /*
  for (int i = 0; i < n; i++)
     cout << T[i] << " ";

  cout << "\n\n";
  */

  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  tantes = chrono::steady_clock::now();
  int inversiones = f(T, n);
  tdespues = chrono::steady_clock::now();

  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << n << " " << inversiones << " " << transcurrido.count() << endl;
  delete [] T;

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
