/*
   @file Grafo no dirigido para el problema del viajante de comercio
*/
#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <cmath>  // sqrt

typedef double peso_t;

peso_t dist(peso_t[2] p1, peso_t[2] p2) {
   return sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]));
}

class Grafo {
   unsigned int nodos;
   peso_t** lados;

   Grafo(int n) :nodos(n) {
      lados = new peso_t[n*n];
   }
   
   ~Grafo() {
      delete [] lados;
   }
   
   Grafo(const Grafo* otro) :nodos(otro.nodos) {
      lados = new peso_t[nodos*nodos];
      for (int i = 0; i < n; i++)
         for (int j = 0; j < n; j++)
            lados[i*nodos+j] = otro.lados[i*nodos+j];
   }
   
   unsigned int numNodos() { return nodos; }
   
   void setPeso(int n1, int n2, peso_t peso) {
      lados[n1*nodos + n2] = lados[n2*nodos + n1] = peso;
   }
   
   peso_t peso(int n1, int n2) {
      return lados[n1*nodos+n2];
   }
   
   void pesosDesdeCoordenadas(peso_t[][2] c) {
      for (int i = 0; i < n-1; i++)
         for (int j = i+1; j < n; j++)
            setPeso(i, j, dist(c[i],c[j]));
   }
};

#endif