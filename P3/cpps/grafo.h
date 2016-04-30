/*
   @file Grafo no dirigido para el problema del viajante de comercio
*/
#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <cmath>  // sqrt
#include <vector>

typedef double peso_t;

peso_t dist(peso_t p1[2], peso_t p2[2]) {
   return sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]));
}

class Grafo {
   unsigned int nodos;
   peso_t* lados;

public:
   Grafo(int n) :nodos(n) {
      lados = new peso_t[n*n];   // Nota: no inicializa a 0 los pesos
   }

   ~Grafo() {
      delete [] lados;
   }

   Grafo(const Grafo& otro) :nodos(otro.nodos) {
      lados = new peso_t[nodos*nodos];
      for (int i = 1; i < nodos; i++)
         for (int j = 0; j < i; j++)
            setPeso(i, j, otro.peso(i, j));
   }

   inline unsigned int numNodos() const { return nodos; }

   void setPeso(int n1, int n2, peso_t peso) {
      lados[n1*nodos + n2] = lados[n2*nodos + n1] = peso;
   }

   peso_t peso(int n1, int n2) const {
      return lados[n1*nodos+n2];
   }

   void pesosDesdeCoordenadas(peso_t c[][2]) {
      for (int i = 0; i < nodos-1; i++)
         for (int j = i+1; j < nodos; j++)
            setPeso(i, j, dist(c[i],c[j]));
   }
};

peso_t longitud(const std::vector<int>& ids, const Grafo& g) {
  peso_t l = g.peso(ids.back(), ids.front());
  for (int i = 1; i < ids.size(); i++)
    l += g.peso(ids[i], ids[i-1]);
  return l;
}

#endif