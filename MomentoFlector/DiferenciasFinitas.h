class DiferenciasFinitas
{
private:
    int _N;
    double _boundLeft;
    double _boundRight;
    double h;
    double* x;
    double* w;
public:
    DiferenciasFinitas(int N, double boundLeft, double boundRight);
    ~DiferenciasFinitas();
    void Solve();
    double* GetX();
    double* GetSolution();
    void WriteSolution();
};