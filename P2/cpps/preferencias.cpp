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
   @brief Calcula número de inversiones

   @param T: vector de elementos.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de parejas de elementos que se encuentran
   en una posición invertida respecto de su contenido.
   Aplica un algoritmo trivial de eficiencia O(n^2).
*/
int preferencias_trivial(int T[], int num_elem) {
  int res = 0;
  for (int i = 0; i < num_elem-1; i++)
    for (int j = i+1; j < num_elem; j++)
      if (T[i] > T[j])
        res++;

  return res;
}

/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static int fusion(int T[], int inicial, int final, const int U[], const int V[])
{
  int j = 0;
  int k = 0;
  int merges = 0;

  for (int i = inicial; i < final; i++)
  {
    if (U[j] < V[k])
	   T[i] = U[j++];
    else {
	   T[i] = V[k++];
      merges += (final - inicial)/2-inicial-j;
    }
  }

  return merges;
}

static int insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  int merges = 0;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
      merges++;
    }
  }
  return merges;
}


/**
   @brief Calcula número de inversiones con inserción

   @param T: vector de elementos. ES MODIFICADO.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de parejas de elementos que se encuentran
   en una posición invertida respecto de su contenido.
   Aplica una modificación del algoritmo de ordenación por
   inserción, de eficiencia O(n^2).
*/
int preferencias_insercion(int T[], int num_elem) {
  return insercion_lims(T, 0, num_elem);
}

const int UMBRAL_DV = 50;  // Umbral óptimo para Divide y Vencerás

static int mergesort_lims(int T[], int inicial, int final)
{
  int merges = 0;

  if(final - inicial < UMBRAL_DV)
    merges = insercion_lims(T, inicial, final);
  else {
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

    merges =  mergesort_lims(U, 0, k);
    merges += mergesort_lims(V, 0, final - k);
    merges += fusion(T, inicial, final, U, V);
    delete [] U;
    delete [] V;
  }

  return merges;
}

/**
   @brief Calcula número de inversiones usando DyV

   @param T: vector de elementos. ES MODIFICADO.
   @param num_elem: número de elementos. num_elem >= 0.

   Cambia el número de parejas de elementos que se encuentran
   en una posición invertida respecto de su contenido.
   Aplica un algoritmo Divide y Vencerás de eficiencia O(n·log(n))
*/
int preferencias_dyv(int T[], int num_elem) {
  return mergesort_lims(T, 0, num_elem);
}

int ejecutar(int (*f)(int*, int), int n) {
  int* T = new int[n];
  get_preferencias(T, n);

  chrono::steady_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  tantes = chrono::steady_clock::now();
  int inversiones = f(T, n);
  tdespues = chrono::steady_clock::now();

  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
  cout << n << " " << transcurrido.count() << endl;
  delete [] T;

  return 0;
}

int main(int argc, char * argv[])
{
  if (argc != 3 || (argv[2][0] != 't' && argv[2][0] != 'i' && argv[2][0] != 'd'))
  {
    cerr << "Formato " << argv[0] << " <num_elem> t/i/d" << endl;
    return -1;
  }
  srand(time(0));
  int n = atoi(argv[1]);

  if (argv[2][0] == 't')
     return ejecutar(preferencias_trivial, n);
  else if (argv[2][0] == 'i')
     return ejecutar(preferencias_insercion, n);
  else
     return ejecutar(preferencias_dyv, n);
}
