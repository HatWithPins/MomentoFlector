# MomentoFlector

:es: \
Implementación del método del disparo y de las diferencias finitas para resolver el problema de una barra unidimensional que flexa. Usa CMake para la compilación.

Para compilar en la línea de comandos:

`cmake` \
`cmake --build <carpeta-de-salida> --target MomentoFlector`

Si se usa un IDE tipo Visual Studio, abre la carpeta como un proyecto y compila como cualquier otro proyecto. Asegúrate de que tienes la extensión para CMake.

Una vez se ha compilado, hay que pasarle las condiciones de contorno, el número de particiones y si ejecutará los métodos en paralelo o no.

`MomentoFlector bound_left=0 bound_right=0 N=5`

Si no recibe los argumentos que espera o si tienen algún problema, devuelve error.

## Estructura de los archivos.
- MomentoFlector contiene el main y las comprobaciones de los argumentos.
- DiferenciasFinitas contiene la clase que implementa el método, incluyendo el método de Crout para resolver la ecuación matricial.
- Richardson contiene las funciones de extrapolación para mejorar el error de los elementos finitos.
- Disparo contiene la clase que implementa el método del disparo y Runge-Kutta de orden 2 y 4.

:uk: \
Implementation of shooting and finite differences method for solving the unidimensional bending bar problem. Builds using cmake.

To build using command line:

`cmake` \
`cmake --build <output-folder> --target MomentoFlector`

In case you use and IDE like Visual Studio, open the folder as a project and build it like any other project. Ensure that your IDE has the extensions for CMake.

Once is built, it needs the boundary conditions, number of partitions and if both methods will run on parallel or not.

`MomentoFlector bound_left=0 bound_right=0 N=5`

If the program doesn't receive the expected arguments or if they have any issue, program will return an error.

## Folder structure.
- MomentoFlector contains the main function and is in charge of checking parsed arguments.
- DiferenciasFinitas contains the class which implements the finite differences method and the Crout method for solving the matrix equation.
- Richardson contains the extrapolation functions to enhance the error from finite differences.
- Disparo contains the class which implements the shooting method and Runge-Kutta for orders 2 and 4.