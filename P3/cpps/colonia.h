#ifndef __COLONIA_H__
#define __COLONIA_H__

#include <algorithm>
#include "grafo.h"
using namespace std;

double uniforme(){
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

class Colonia {
   Grafo<peso_t> distancias;
   Grafo<double> feromonas;
   static const double ALPHA, BETA, EVAPORACION, C, P;

   inline int nodos() const { return distancias.numNodos(); }

   double probabilidad(int n1, int n2) const {
      return pow(1.0/distancias.peso(n1, n2), BETA) * pow(feromonas.peso(n1, n2), ALPHA);
   }

   vector<int> un_trayecto() const {
      int inicial = uniforme()*nodos();
      vector<int> trayecto(1, inicial);
      vector<int> disponibles;
      for (int i = 0; i < inicial; i++)
         disponibles.push_back(i);
      for (int i = inicial+1; i < nodos(); i++)
         disponibles.push_back(i);

      int actual = inicial;
      while(!disponibles.empty()) {
         int siguiente_pos;
         if (uniforme() < P) {
            vector<double> prob_acumulada(1, 0);
            for (vector<int>::iterator it = disponibles.begin(); it != disponibles.end() && !isinf(prob_acumulada.back()); ++it)
               prob_acumulada.push_back(prob_acumulada.back() + probabilidad(actual, *it));

            if (isinf(prob_acumulada.back()))   // Ocurre si dos nodos están a distancia 0
               siguiente_pos = prob_acumulada.size()-1;
            else {
               double aleatorio = uniforme()*prob_acumulada.back();
               vector<double>::iterator sig = upper_bound(prob_acumulada.begin(), prob_acumulada.end(), aleatorio);
               siguiente_pos = sig-prob_acumulada.begin()-1;
            }
         } else {
            int mejor = 0;
            peso_t mejor_lng = distancias.peso(actual, disponibles.front());
            for (int i = 1; i < disponibles.size(); i++) {
               peso_t lng = distancias.peso(actual, disponibles[i]);
               if (lng < mejor_lng) {
                  mejor = i;
                  mejor_lng = lng;
               }
            }
            siguiente_pos = mejor;
         }
         actual = disponibles[siguiente_pos];
         swap(disponibles[siguiente_pos], disponibles.back());
         disponibles.pop_back();  // Para eliminar el nodo siguiente_pos-ésimo en O(1)
         trayecto.push_back(actual);
      }
      
      return trayecto;
   }

public:
   Colonia(const Grafo<peso_t>& g) :distancias(g), feromonas(g.numNodos()) {
      for (int i = 1; i < nodos(); i++)
         for (int j = 0; j < i; j++)
            feromonas.setPeso(i, j, 1.0); // Arbitrario, pero no puede ser 0
   }

   Colonia(const Colonia& otra) :distancias(otra.distancias), feromonas(otra.feromonas) { };
   
   // Itera y devuelve el mejor camino encontrado
   vector<int> itera(int iteraciones) {
      list<vector<int> > trayectos;
      for (int i = 0; i < iteraciones; i++)
         trayectos.push_back(un_trayecto());
      
      for (int i = 1; i < nodos(); i++)
         for (int j = 0; j < i; j++)
            feromonas.setPeso(i, j, feromonas.peso(i, j)*EVAPORACION);
      
      double mayor_suma = -1;
      list<vector<int> >::const_iterator mejor_camino, t;
      for (t = trayectos.cbegin(); t != trayectos.cend(); ++t) {
         double suma = C/longitud(*t, distancias);
         if (suma > mayor_suma) {
            mayor_suma = suma;
            mejor_camino = t;
         }
         
         for (int i = 1; i < (*t).size(); i++)
            feromonas.setPeso((*t)[i-1], (*t)[i], feromonas.peso((*t)[i-1], (*t)[i])+suma);
            
         feromonas.setPeso((*t).front(), (*t).back(), feromonas.peso((*t).front(), (*t).back())+suma);
      }
      
      return *mejor_camino;
   }
};

const double Colonia::ALPHA = 1, Colonia::BETA = 6, Colonia::EVAPORACION = 0.7, Colonia::C = 4, Colonia::P = 0.2;

#endif