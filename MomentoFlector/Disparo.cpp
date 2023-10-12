#include "Disparo.h"
#include <fstream>
#include <string>

using namespace std;

Disparo::Disparo(int N, double boundLeft, double boundRight)
{
    _N = N;
    _boundLeft = boundLeft;
    _boundRight = boundRight;
    h = 2.0/_N;
    x = new double[_N];
    w = new double[_N];

    for (int i = 0; i < _N; i++)
    {
        x[i] = -1 + i*h;
    }
}

Disparo::~Disparo()
{
    delete[] x;
    delete[] w;
}

void Disparo::Solve()
{
}

double* Disparo::GetX()
{
    return x;
}

double* Disparo::GetSolution()
{
    return w;
}

void Disparo::WriteSolution()
{
    ofstream file{ "results/disparo-" + to_string(h) + ".csv"};

    file << "x_i,w_i\n";

    for (int i = 0; i < _N; i++)
    {
        file << to_string(x[i]) + "," + to_string(w[i]) + "\n";
    }

    file.close();
}