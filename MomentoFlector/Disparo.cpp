#include "Disparo.h"
#include <fstream>
#include <string>

using namespace std;

//Constructor de la clase. Define los parámetros conocidos.
//Class constructor. Defines known parameters.
Disparo::Disparo(int N, double boundLeft, double boundRight)
{
    _N = N;
    _boundLeft = boundLeft;
    _boundRight = boundRight;
    h = 2.0/_N;
    x = new double[_N + 1];
    w = new double[_N + 1];

    for (int i = 0; i < _N + 1; i++)
    {
        x[i] = -1 + i*h;
    }
}

//Destructor de la clase.
//Class destructor.
Disparo::~Disparo()
{
    delete[] x;
    delete[] w;
}

double* Disparo::RungeKutta(bool isSolvingY1, bool isOrder4)
{
    //Variables para resolver las dos ecuaciones del sistema usando Runge-Kutta.
    //Variables to solve both equations from the system using Runge-Kutta.
    double* u_1 = new double[_N + 1];
    double* u_2 = new double[_N + 1];
    //Dependiendo de si resolvemos para y_1 o y_2, las ecuaciones del método del disparo, cambian las condiciones iniciales.
    //Depending on if we are solving for y_1 or y_2,  the equations from shooting method, initial conditions change.
    u_1[0] = isSolvingY1*_boundLeft;
    u_2[0] = !isSolvingY1;
    //k almacena los términos de Runge-Kutta. Como el máximo orden es 4 y es para dos ecuaciones, sólo necesita 8 huecos.
    //k[2n] almacena los términos para u_1. k[2n + 1] los almacena para u_2.
    //k stores Runge-Kutta terms. Becase maximum order is 4 for the two equations, it only needs size 8.
    double k[8];

    for (int i = 0; i < _N + 1; i++)
    {
        k[0] = h*u_2[i];
        k[1] = h*((1 + x[i]*x[i])*u_1[i] - isSolvingY1);
        for (int j = 2; j < 7; j += 2)
        {
            k[j] = h * (u_2[i] + 0.5 * k[ j - 1]);
            k[j + 1] = h * ((1 + (x[i] + h / 2) * (x[i] + h / 2)) * (u_1[i] + 0.5 * k[j - 2]) - isSolvingY1);
        }

        //Dependiendo del orden de aproximación, suma unos términos u otros.
        //Depending on the order, it adds the needed terms.
        u_1[i + 1] = u_1[i] + 1.0/6*(k[0] + 2*k[2] + 2*k[4] + k[6])*isOrder4 + k[2]*!isOrder4;
        u_2[i + 1] = u_2[i] + 1.0/6*(k[1] + 2*k[3] + 2*k[5] + k[7])*isOrder4 + k[3]*!isOrder4;
    }

    return u_1;
}

void Disparo::Solve(bool isOrder4)
{
    //Variables auxiliares para Runge-Kutta. Tenemos dos sistemas de dos ecuaciones, u_1 contiene la solución numérica del sistema y_1, v_1 el de y_2.
    //Helping varaibles for Runge-Kutta. There are two systems of two equations, u_1 contains the numeric solution for y_1, v_1 is for y_2.
    double* u_1 = RungeKutta(true, isOrder4);
    double* v_1 = RungeKutta(false, isOrder4);

    w[0] = _boundLeft;
    double w_2 = (_boundRight - u_1[_N])/v_1[_N];

    for (int i = 1; i < _N + 1; i++)
    {
        w[i] = u_1[i] + w_2*v_1[i];
    }
}

//Método para recuperar los puntos de x.
//Method to get x values.
double* Disparo::GetX()
{
    return x;
}

//Método que devuelve la solución calculada.
//Method to get the calculated solution.
double* Disparo::GetSolution()
{
    return w;
}

//Método para escribir los resultados en un CSV.
//Method to export the results to a CSV.
void Disparo::WriteSolution(int order)
{
    ofstream file{ "results/disparo-orden-" + to_string(order) + "-h-" + to_string(h) + ".csv"};

    file << "x_i,w_i\n";

    for (int i = 0; i < _N + 1; i++)
    {
        file << to_string(x[i]) + "," + to_string(w[i]) + "\n";
    }

    file.close();
}