#include "DiferenciasFinitas.h"
#include <fstream>
#include <string>

using namespace std;

//Constructor de la clase. Define los parámetros conocidos.
//Class constructor. Defines known parameters.
DiferenciasFinitas::DiferenciasFinitas(int N, double boundLeft, double boundRight)
{
    _N = N;
    _boundLeft = boundLeft;
    _boundRight = boundRight;
    h = 2.0/_N;
    x = new double[_N + 1];
    w = new double[_N + 1];

    a = new double[_N - 1];
    d = new double[_N - 1];
    l = new double[_N - 1];
    u = new double[_N - 1];
    z = new double[_N - 1];


    for (int i = 0; i < _N + 1; i++)
    {
        x[i] = -1 + i*h;
    }

    a[0] = 2.0 + h*h*(1 + x[1]*x[1]);
    d[0] = h*h + _boundLeft;

    //Si N = 2, a y d sólo tienen un elemento.
    //If N = 2, a and d only have one element. 
    if (_N > 2)
    {
        a[_N - 2] = 2.0 + h*h*(1 + x[_N - 1]*x[_N - 1]);
        d[_N - 2] = h*h + _boundRight;

        for (int i = 1; i < _N - 2; i++)
        {
            a[i] = 2 + h*h*(1 + x[i + 1]*x[i + 1]);
            d[i] = h*h;
        }
    }
}

//Destructor de la clase.
//Class destructor.
DiferenciasFinitas::~DiferenciasFinitas()
{
    delete[] x;
    delete[] w;

    delete[] a;
    delete[] d;
    delete[] l;
    delete[] u;
    delete[] z;
}

//Como el constructor ya plantea la ecuación matricial, este método es la implementación del algoritmo de Crout.
//Because the constructor already states the matrix equation, this method actually implements Crout's algorithm.
void DiferenciasFinitas::Solve()
{
    l[0] = a[0];
    u[0] = b/a[0];
    z[0] = d[0]/l[0];

    for (int i = 1; i < _N - 2; i++)
    {
        l[i] = a[i] - b*u[i-1];
        u[i] = b/l[i];
        z[i] = (d[i] - b*z[i - 1])/l[i];
    }

    if (_N > 2)
    {
        l[_N - 2] = a[_N - 2] - b*u[_N - 3];
        z[_N - 2] = (d[_N - 2] - b*z[_N - 3])/l[_N - 2];
    }

    w[0] = _boundLeft;
    w[_N] = _boundRight;
    w[_N - 1] = z[_N - 2];
    
    for (int i = _N - 2; i > 0; i--)
    {
        w[i] = z[i - 1] - u[i - 1]*w[i + 1];
    }
}

//Método para recuperar los puntos de x.
//Method to get x values.
double* DiferenciasFinitas::GetX()
{
    return x;
}

//Método que devuelve la solución calculada.
//Method to get the calculated solution.
double* DiferenciasFinitas::GetSolution()
{
    return w;
}

//Método para escribir los resultados en un CSV.
//Method to export the results to a CSV.
void DiferenciasFinitas::WriteSolution()
{
    ofstream file{ "results/diferencias_finitas-" + to_string(h) + ".csv"};

    file << "x_i,w_i\n";

    for (int i = 0; i < _N + 1; i++)
    {
        file << to_string(x[i]) + "," + to_string(w[i]) + "\n";
    }

    file.close();
}