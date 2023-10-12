#include "Richardson.h"
#include <fstream>
#include <string>

using namespace std;

double* primeraExtrapolacion(double* v, double* w, int size_w)
{
    double* ext = new double[size_w];

    for (int i = 0; i < size_w; i++)
    {
        ext[i] = (4*v[i*2] - w[i])/3;
    }

    return ext;
}

double* segundaExtrapolacion(double* v, double* w, int size_w)
{
    double* ext = new double[size_w];

    for (int i = 0; i < size_w; i++)
    {
        ext[i] = (16*v[i] - w[i])/15;
    }

    return ext;
}

//Para estimar el resultado real, se ajustan las extrapolaciones anteriores a una recta.
//To estimate the real result, previous extrapolations are fitted to a straight line.
double* extrapolacionCero(double h, double* v, double* w, int size_w)
{
    double* ext = new double[size_w];
    double a;

    for (int i = 0; i < size_w; i++)
    {
        a = (w[i]-v[i])/(h - h/2);
        ext[i] = w[i] - a*h;
    }

    return ext;
}