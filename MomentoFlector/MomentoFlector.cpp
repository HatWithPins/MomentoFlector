#include "MomentoFlector.h"

using namespace std;

int main(int argc, char** argv)
{
	string argument;
	size_t pos;
	size_t check;
	double boundLeft;
	double boundRight;
	int N;
	bool multithread;
	int expectedArguments = 5;
	vector<string> expectedArgumentsList = {"bound_left=", "bound_right=", "N=", "multithread="};
	vector<string> receivedArguments;

	//Se comprueba el número de parámetros recibidos. 
	//Checking the number of received parameters.
	if (argc != expectedArguments)
	{
		cout << "Error, expected " << expectedArguments - 1 << ", but received " << argc - 1 << endl;
		return -1;
	}

	//Se comprueban los nombres de los parámetros.
	//Checking if parameter names are correct.
	try 
	{
		for (int i = 1; i < argc; i++)
		{
			argument = argv[i];
			check = argument.find(expectedArgumentsList[i - 1]);
			if (check < 0 || check > argument.size())
			{
			    vector<string> exceptionVector = {argument, expectedArgumentsList[i - 1]};
				throw(exceptionVector);
			}
			pos = argument.find("=");
			receivedArguments.push_back(argument.substr(pos + 1));
		}
	}
	catch (vector<string> errorVector)
	{
		cout << "Error, expected " << errorVector[1] << "something, but received " << errorVector[0] << endl;
		return -1;
	}

	//Se castean los parámetros a sus respectivas variables.
	//Casting parameters to their variables.
	try
	{
		boundLeft = stod(receivedArguments[0]);
		boundRight = stod(receivedArguments[1]);
		N = stoi(receivedArguments[2]);
		multithread = stoi(receivedArguments[3]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	//La implementación de los métodos requiere que se usen al menos dos. Si N es menor que 2, se devuelve un error.
	//Implemented methods require at least two points hence, if N is less than 2, code will return an error.
	if (N < 2) 
	{
		cout << "Error, N must be greater or equal to 2, received N " << N << endl;
		return -1;
	}

	DiferenciasFinitas test(N, boundLeft, boundRight);
	test.Solve();
	test.WriteSolution();

	DiferenciasFinitas test2(2*N, boundLeft, boundRight);
	test2.Solve();
	test2.WriteSolution();

	DiferenciasFinitas test3(4*N, boundLeft, boundRight);
	test3.Solve();
	test3.WriteSolution();

	double* w1 = primeraExtrapolacion(test2.GetSolution(), test.GetSolution(), N + 1);
	double* w2 = primeraExtrapolacion(test3.GetSolution(), test2.GetSolution(), 2*N + 1);
	double* w3 = segundaExtrapolacion(w2, w1, N + 1);
	double* w0 = extrapolacionCero(2.0/N, w2, w3, N + 1);

	writeResults(w1, w2, w3, w0, N);

	return 0;
}
