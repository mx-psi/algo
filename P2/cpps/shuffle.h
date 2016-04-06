#include <ctime>
#include <cstdlib>
#include <climits>

//generador de ejemplos para el problema de la comparación de preferencias. Simplemente se genera una permutación aleatoria del vector 0,1,2,...,n-2,n-1

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
