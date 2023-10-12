class DiferenciasFinitas
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

    //Variables auxiliares para el algoritmo de Crout.
    //Helping varaibles for Crout's algorithm.
    double* a;
    /*Tendría que haber dos arrays aquí, b y c para la implementación del algoritmo de Crout.
    Dada la forma particular del problema a resolver, b=c=-1, por lo que sólo hace falta un
    escalar.
    */
    /*In order to implement Crout's algorithm, we should need two arrays, b and c.
    Given our particular problem to solve, b=c=-1, so we only need a scalar.
    */
    double b = -1.0;
    double* d;
    double* l;
    double* u;
    double* z;
public:
    DiferenciasFinitas(int N, double boundLeft, double boundRight);
    ~DiferenciasFinitas();
    void Solve();
    double* GetX();
    double* GetSolution();
    void WriteSolution();
};