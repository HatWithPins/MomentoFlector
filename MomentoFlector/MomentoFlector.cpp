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

	if (argc != expectedArguments)
	{
		cout << "Error, expected " << expectedArguments - 1 << ", but received " << argc - 1 << endl;
		return -1;
	}


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
	
	return 0;
}
