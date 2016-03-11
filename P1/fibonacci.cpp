/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
#include <chrono>
using namespace std::chrono;


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
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
 
  //std::cout << "�N�mero del t�rmino: ";
  std::cin >> n;

  tantes =  steady_clock::now();
  f = fibo(n);
  tdespues =  steady_clock::now();
  transcurrido = duration_cast<duration<double>>(tdespues - tantes);

  std::cout << n << ' ' << transcurrido.count() << std::endl;
  //std::cout << "El t�rmino " << n << "-�simo es: " << f << std::endl;

  return 0;
}
 
