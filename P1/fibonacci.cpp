/**
   @file Cálculo de la sucesión de Fibonacci
*/

   
#include <iostream>
#include <chrono>
using namespace std::chrono;


/**
   @brief Calcula el término n-ésimo de la sucesión de Fibonacci.

   @param n: número de orden del término buscado. n >= 1.

   @return: término n-ésimo de la sucesión de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main()
{

  int n;
  int f;
  steady_clock::time_point tantes, tdespues;
  duration<double> transcurrido;
 
  //std::cout << "¿Número del término: ";
  std::cin >> n;

  tantes =  steady_clock::now();
  f = fibo(n);
  tdespues =  steady_clock::now();
  transcurrido = duration_cast<duration<double>>(tdespues - tantes);

  std::cout << n << ' ' << transcurrido.count() << std::endl;
  //std::cout << "El término " << n << "-ésimo es: " << f << std::endl;

  return 0;
}
 
