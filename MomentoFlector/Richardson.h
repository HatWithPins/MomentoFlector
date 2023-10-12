#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

//Extrapolación del orden de h^2
//Extrapolation of order h^2
double* primeraExtrapolacion(double* v, double* w, int size_w);
//Extrapolación del orden de h^4
//Extrapolation of order h^4
double* segundaExtrapolacion(double* v, double* w, int size_w);
//Estimación del resultado real cuando h->0.
//Estimation of real result when h->0.
double* extrapolacionCero(double h, double* v, double* w, int size_w);

 #endif