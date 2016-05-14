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
   const Grafo<peso_t> distancias;
   Grafo<double> feromonas;
   static const double ALPHA, BETA, RHO, XI, C, P, I;

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
      vector<double> prob_acumulada(1,0);
      while(!disponibles.empty()) {
         int siguiente_pos;
         if (uniforme() < P) {
            prob_acumulada.resize(1);
            for (vector<int>::iterator it = disponibles.begin(); it != disponibles.end() && !std::isinf(prob_acumulada.back()); ++it)
               prob_acumulada.push_back(prob_acumulada.back() + probabilidad(actual, *it));

            if (std::isinf(prob_acumulada.back()))   // Ocurre si dos nodos están a distancia 0
               siguiente_pos = prob_acumulada.size()-1;
            else {
               double aleatorio = uniforme()*prob_acumulada.back();
               vector<double>::iterator sig = upper_bound(prob_acumulada.begin(), prob_acumulada.end(), aleatorio);
               siguiente_pos = sig-prob_acumulada.begin()-1;
            }
         } else {
            int mejor = 0;
            double prob, mejor_prob = probabilidad(actual, disponibles.front());
            for (int i = 1; i < disponibles.size(); i++) {
               prob = probabilidad(actual, disponibles[i]);
               if (prob > mejor_prob) {
                  mejor = i;
                  mejor_prob = prob;
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
            feromonas.setPeso(i, j, I);
   }

   Colonia(const Colonia& otra) :distancias(otra.distancias), feromonas(otra.feromonas) { };

   // Itera y devuelve el mejor camino encontrado
   vector<int> itera(int iteraciones) {
      list<vector<int> > trayectos;
      for (int i = 0; i < iteraciones; i++)
         trayectos.push_back(un_trayecto());

      double mayor_suma = -1;
      list<vector<int> >::const_iterator mejor_camino, t;
      for (t = trayectos.cbegin(); t != trayectos.cend(); ++t) {
         double suma = C/longitud(*t, distancias);
         if (suma > mayor_suma) {
            mayor_suma = suma;
            mejor_camino = t;
         }

         for (int i = 1; i < (*t).size(); i++)
            feromonas.setPeso((*t)[i-1], (*t)[i], (1-XI)*feromonas.peso((*t)[i-1], (*t)[i])+XI*I);

         feromonas.setPeso((*t).front(), (*t).back(), (1-XI)*feromonas.peso((*t).front(), (*t).back())+XI*I);
      }
      for (int i = 1; i < (*mejor_camino).size(); i++)
         feromonas.setPeso((*mejor_camino)[i-1], (*mejor_camino)[i], (1-RHO)*feromonas.peso((*mejor_camino)[i-1], (*mejor_camino)[i])+RHO*mayor_suma);

      feromonas.setPeso((*mejor_camino).front(), (*mejor_camino).back(), (1-RHO)*feromonas.peso((*mejor_camino).front(), (*mejor_camino).back())+RHO*mayor_suma);
      return *mejor_camino;
   }
};

const double Colonia::ALPHA = 1, Colonia::BETA = 6, Colonia::RHO = 0.1, Colonia::XI = 0.02, Colonia::C = 2, Colonia::P = 0.1 , Colonia::I = 0.00001;

#endif
