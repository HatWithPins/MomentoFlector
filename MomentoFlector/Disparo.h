class Disparo
{
    private:
        int _N;
        double _boundLeft;
	    double _boundRight;
        double h;
        double* x;
        double* w;
    public:
        Disparo(int N, double boundLeft, double boundRight);
        ~Disparo();
        void Solve();
        double* GetX();
        double* GetSolution();
        void WriteSolution();
};