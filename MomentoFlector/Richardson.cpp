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
        ext[i] = (16*v[2*i] - w[i])/15;
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
        a = (w[i]-v[2*i])/(h - h/2);
        ext[i] = w[i] - a*h;
    }

    return ext;
}

void writeResults(double* w1, double* w2, double* w3, double* w0, int N)
{
	ofstream file{ "results/richardson.csv"};

    file << "w_1,w_2,w_3,w_0\n";

    for (int i = 0; i < N + 1; i++)
    {
        file << to_string(w1[i]) + "," + to_string(w2[2*i]) + "," + to_string(w3[i]) + "," + to_string(w0[i]) + "\n";
    }

    file.close();
}