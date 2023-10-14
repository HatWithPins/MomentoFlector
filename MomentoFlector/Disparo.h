class Disparo
{
    private:
        //Las variables del problema.
        //Variables of the problem.
        int _N;
        double _boundLeft;
	    double _boundRight;
        double h;
        double* x;
        double* w;

        double* RungeKutta(bool isSolvingY1, bool isOrder4);
    public:
        Disparo(int N, double boundLeft, double boundRight);
        ~Disparo();
        void Solve(bool isOrder4);
        double* GetX();
        double* GetSolution();
        void WriteSolution(int order);
};