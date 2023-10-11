#include "DiferenciasFinitas.h"
#include <fstream>
#include <string>

using namespace std;

DiferenciasFinitas::DiferenciasFinitas(int N, double boundLeft, double boundRight)
{
    _N = N;
    _boundLeft = boundLeft;
    _boundRight = boundRight;
    h = 2/_N;
    x = new double[_N];
    w = new double[_N];

    for (int i = 0; i < _N; i++)
    {
        x[i] = -1 + i*h;
    }
}

DiferenciasFinitas::~DiferenciasFinitas()
{
    delete[] x;
    delete[] w;
}

void DiferenciasFinitas::Solve()
{
}

double* DiferenciasFinitas::GetX()
{
    return x;
}

double* DiferenciasFinitas::GetSolution()
{
    return w;
}

void DiferenciasFinitas::WriteSolution()
{
    ofstream file{ "results/diferencias_finitas-" + to_string(h) + ".csv"};

    file << "x_i,w_i\n";

    for (int i = 0; i < _N; i++)
    {
        file << to_string(x[i]) + "," + to_string(w[i]) + "\n";
    }

    file.close();
}