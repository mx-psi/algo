/*
   @file Grafo no dirigido para el problema del viajante de comercio
*/
#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <cmath>  // sqrt
#include <vector>

typedef int peso_t;

peso_t dist(double p1[2], double p2[2]) {
   return round(sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1])));
}

template<class T>
class Grafo {
   unsigned int nodos;
   T* lados;

public:
   Grafo(int n) :nodos(n) {
      lados = new T[n*n];   // Nota: no inicializa a 0 los pesos
   }

   ~Grafo() {
      delete [] lados;
   }

   Grafo(const Grafo& otro) :nodos(otro.nodos) {
      lados = new T[nodos*nodos];
      for (int i = 1; i < nodos; i++)
         for (int j = 0; j < i; j++)
            setPeso(i, j, otro.peso(i, j));
   }

   inline unsigned int numNodos() const { return nodos; }

   void setPeso(int n1, int n2, T peso) {
      lados[n1*nodos + n2] = lados[n2*nodos + n1] = peso;
   }

   T peso(int n1, int n2) const {
      return lados[n1*nodos+n2];
   }

   void pesosDesdeCoordenadas(double c[][2]) {
      for (int i = 0; i < nodos-1; i++)
         for (int j = i+1; j < nodos; j++)
            setPeso(i, j, dist(c[i],c[j]));
   }
};

peso_t longitud(const std::vector<int>& ids, const Grafo<peso_t>& g) {
  peso_t l = g.peso(ids.back(), ids.front());
  for (int i = 1; i < ids.size(); i++)
    l += g.peso(ids[i], ids[i-1]);
  return l;
}

#endif