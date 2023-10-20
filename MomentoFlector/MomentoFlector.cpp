#include "MomentoFlector.h"

using namespace std;

//Función para generar las tablas en formato LaTeX.
//Function to generate LaTeX tables.
void ToLatex(int N, double* x, double* df, double* orden2, double* orden4, double* w)
{
	double h = 2.0 / N;
	ofstream file{ "results/agregados-h-" + to_string(h) + ".txt" };

	file << "\\begin{table}[!h]\n";
	file << "\\centering\n";
	file << "\\begin{tabular}{||cccccccc||}\n";
	file << "\\hline\n";
	file << "$\\xi_{i}$& DF & $\\Delta w_{i}$ & Disparo orden 2 & $\\Delta w_{i}$ & Disparo orden 4 & $\\Delta w_{i}$ & $w_{0}$\\\\\n";
	file << "\\hline\\hline\n";

	for (int i = 0; i < N + 1; i++)
	{
		file << to_string(x[i]);
		file << "&" + to_string(df[i]) + "&" + to_string(abs(df[i] - w[i]));
		file << "&" + to_string(orden2[i]) + "&" + to_string(abs(orden2[i] - w[i]));
		file << "&" + to_string(orden4[i]) + "&" + to_string(abs(orden4[i] - w[i]));
		file << "&" + to_string(w[i]) + "\\\\\n";
		file << "\\hline\\hline\n";

	}

	file << "\\end{tabular}\n";
	file << "\\caption{Resultados num\\'ericos para $h=" + to_string(h) + "$}\n";
	file << "\\label{tab:combinado}\n";
	file << "\\end{table}\n";

	file.close();
}
//Función que llama a las clases para hacer los cálculos.
//Function to instantiate classes and do the calculations.
int Solve(int N, double boundLeft, double boundRight)
{
	try
	{
		DiferenciasFinitas diferenciasFinitasH(N, boundLeft, boundRight);
		diferenciasFinitasH.Solve();
		diferenciasFinitasH.WriteSolution();

		DiferenciasFinitas diferenciasFinitasH2(2 * N, boundLeft, boundRight);
		diferenciasFinitasH2.Solve();
		diferenciasFinitasH2.WriteSolution();

		DiferenciasFinitas diferenciasFinitasH4(4 * N, boundLeft, boundRight);
		diferenciasFinitasH4.Solve();
		diferenciasFinitasH4.WriteSolution();

		double* w1 = primeraExtrapolacion(diferenciasFinitasH2.GetSolution(), diferenciasFinitasH.GetSolution(), N + 1);
		double* w2 = primeraExtrapolacion(diferenciasFinitasH4.GetSolution(), diferenciasFinitasH2.GetSolution(), 2 * N + 1);
		double* w3 = segundaExtrapolacion(w2, w1, N + 1);
		double* w0 = extrapolacionCero(2.0 / N, w2, w3, N + 1);

		writeResults(w1, w2, w3, w0, N);

		Disparo disparoOrden4(N, boundLeft, boundRight);
		disparoOrden4.Solve(true);
		disparoOrden4.WriteSolution(4);

		Disparo disparoOrden2(N, boundLeft, boundRight);
		disparoOrden2.Solve(false);
		disparoOrden2.WriteSolution(2);

		ToLatex(N, diferenciasFinitasH.GetX(), diferenciasFinitasH.GetSolution(), disparoOrden2.GetSolution(), disparoOrden4.GetSolution(), w0);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}

int main(int argc, char** argv)
{
	string argument;
	size_t pos;
	size_t check;
	double boundLeft;
	double boundRight;
	int N;
	int expectedArguments = 4;
	vector<string> expectedArgumentsList = {"bound_left=", "bound_right=", "N="};
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

	return Solve(N, boundLeft, boundRight);
}
