#ifndef __GENERADORES_H__
#define __GENERADORES_H__

#include <ctime>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;
double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

/**
   @brief Permuta aleatoriamente un vector

   @param T: vector de elementos. Debe tener n elementos.
             Es MODIFICADO.
   @param n: número de elementos. n >= 0.

   Cambia el orden de los elementos de T al azar usando el
   algoritmo de Knuth.

   @note Debe haberse llamado al menos una vez a srand(time(0)).
*/
void shuffle(int T[], int n)
{
   for (int j=n-1; j>0; j--) {
      double u=uniforme();
      int k=(int)(j*u);
      int tmp=T[j];
      T[j]=T[k];
      T[k]=tmp;
   }
}

/**
   @brief Permutación aleatoria

   @param T: vector de elementos. Debe tener capacidad n.
             Es MODIFICADO.
   @param n: número de elementos. n >= 0.

   Rellena un vector de n componentes con una permutación
   de los n primeros números naturales.

   @note Debe haberse llamado al menos una vez a srand(time(0)).
*/
void get_preferencias(int T[], int n)
{
  for (int i = 0; i < n; i++)
    T[i] = i;

  shuffle(T, n);
}

/**
   @brief Vector ordenado

   @param T: vector de elementos. Debe tener capacidad n.
             Es MODIFICADO.
   @param n: número de elementos. n >= 0.

   Rellena un vector de n componentes con n enteros
   distintos ordenados de forma creciente.

   @note Debe haberse llamado al menos una vez a srand(time(0)).
*/
void get_elementoensuposicion(int T[], int n)
{
  /*He comentado esta versión para no tener que realizar el vector aux y borrarlo en cada ejecución
  int m=2*n-1;
  int * aux = new int[m];

  srand(time(0));
  for (int j=0; j<m; j++)
    aux[j]=j-(n-1);
  random_shuffle(aux, aux+m);
  for (int j=0; j<n; j++)
    T[j]=aux[j];

  delete [] aux;
  std::sort(T, T+n);*/
  int m = 2*n-1;
  for(int j = 0; j < m; j++)
    T[j] = j -(n-1);
  shuffle(T, m);
  sort(T, T+n);

}
/**
   @brief Vector ordenado

   @param T: vector de elementos. Debe tener capacidad n.
             Es MODIFICADO.
   @param n: número de elementos. n >= 0.

   Rellena un vector de n componentes con n enteros ordenados
   (sin tener que se distintos) de forma creciente.

   @note Debe haberse llamado al menos una vez a srand(time(0)).
*/
void get_elementoensuposicion2(int T[], int n)
{
  for(int i = 0; i < n; i++)
    T[i] = (rand() % 2*n) - n/2;
  sort(T, T+n);
}

#endif
