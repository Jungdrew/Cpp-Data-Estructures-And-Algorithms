#include <iostream>
#include <math.h>
using namespace std;

// Verificar que no sobrepase los limites establecidos
int VerificarRango(int var, int rangoX, int rangoY)
{
    while (var < rangoX || var > rangoY)
    {
        cout << "El tamaño de esté dato de entrada debe estar entre [" << rangoX << " - " << rangoY << "] : ";
        cin >> var;
    }
    return var;
}

char VerificarDireccion(char var)
{
    while (var != 's' && var != 'S' && var != 'N' && var != 'n' && var != 'E' && var != 'e' && var != 'O' && var != 'o')
    {
        cout << "La dirección ingresada no es válida (N - S - O -E ) : ";
        cin >> var;
    }
    return var;
}

int main()
{
    // Definir variables
    int GallineroX, GallineroY, Pollitos;
    int pasos, F, C, TempStep = 0, k = 1, n = 1, formula;
    char dir = 'N';

    // Entrada de el tamaño del gallinero.
    cout << "Ingrese tamaño norte-sur del gallinero (1 - 50) : ";
    cin >> GallineroX;
    GallineroX = VerificarRango(GallineroX, 1, 50);

    cout << "Ingrese tamaño oeste-este del gallinero (1 - 50) : ";
    cin >> GallineroY;
    GallineroY = VerificarRango(GallineroY, 1, 50);

    // Ingrese la cantidad de pollitos
    cout << "Ingrese la cantidad de pollos (1 - 10) : ";
    cin >> Pollitos;
    Pollitos = VerificarRango(Pollitos, 1, 10);

    // Llenar array principal
    int MainMatriz[GallineroX][GallineroY], TempMatriz[GallineroX][GallineroY];

    /// Llenar matriz principal
    for (int i = 0; i < GallineroX; i++)
    {
        for (int j = 0; j < GallineroY; j++)
        {
            MainMatriz[i][j] = 0;
        }
    }

    // Pedir datos de cada pollito
    for (int i = 0; i < Pollitos; i++)
    {
        //Reinicia valores para ejecución del while
        TempStep = 0, k = 1, n = 1;

        // Vaciar matriz temporal
        for (int i = 0; i < GallineroX; i++)
        {
            for (int j = 0; j < GallineroY; j++)
            {
                TempMatriz[i][j] = 0;
            }
        }

        cout << "Ingrese posición norte-sur del pollito[" << i + 1 << "] (0-" << GallineroY - 1 << ") : ";
        cin >> F;
        F = VerificarRango(F, 0, GallineroX - 1);

        cout << "Ingrese posición oeste-este del pollito[" << i + 1 << "] (0-" << GallineroY - 1 << ") : ";
        cin >> C;
        C = VerificarRango(C, 0, GallineroY - 1);

        cout << "Ingrese dirección del pollito[" << i << "] (N - S - E - O) : ";
        cin >> dir;
        dir = VerificarDireccion(dir);

        cout << "Ingrese máxima cantidad de pasos del pollito : ";
        cin >> pasos;

        // Crea la espiral 
        while(TempStep < pasos){
            
            // Punto f c, del pollito
            if(TempStep == 0 && (dir == 'N' || dir == 'n' ) ){
                TempMatriz[F][C] = 1;
                F--;
                TempMatriz[F][C] = 1;
                dir = 'E';
                TempStep = 2;
            }else if(TempStep == 0 && (dir == 'S' || dir == 's' ) ){
                TempMatriz[F][C] = 1;
                F++;
                TempMatriz[F][C] = 1;
                dir = 'O';
                TempStep = 2;
            }else if(TempStep == 0 && (dir == 'E' || dir == 'e' ) ){
                TempMatriz[F][C] = 1;
                C++;
                TempMatriz[F][C] = 1;
                dir = 'S';
                TempStep = 2;
            }else if(TempStep == 0 && (dir == 'O' || dir == 'o' ) ){
                TempMatriz[F][C] = 1;
                C--;
                TempMatriz[F][C] = 1;
                dir = 'N';
                TempStep = 2;
            }
            
            // Espiral xD
            for(int i = 1; i <= k ; i++ ){
                if(TempStep == pasos){
                    break;				
                }else if(dir == 'N'){
                    F--;
                    TempMatriz[F][C] = 1;
                    TempStep ++;
                }else if(dir == 'S' ){
                    F++;
                    TempMatriz[F][C] = 1;
                    TempStep ++;
                }else if(dir == 'E' ){
                    C++;
                    TempMatriz[F][C] = 1;
                    TempStep ++;
                }else if(dir == 'O' ){
                    C--;
                    TempMatriz[F][C] = 1;
                    TempStep ++;
                }
                
                if(i == k){
                    if(dir == 'N') dir = 'E';
                    else if(dir == 'S') dir = 'O';
                    else if(dir == 'E') dir = 'S';
                    else if(dir == 'O') dir = 'N';
                }
            }

            formula = pow(n, 2) + 3*n + 3; 
            if(k == 1){
                k++;
            }else if(TempStep % formula == 0){
                k++;
                n++;
            }
            
        }

        /// Está línea de código muestra la matriz temporar [ ! Testing ]
        // for (int i = 0; i < GallineroX; i++)
        // {
        //     for (int j = 0; j < GallineroY; j++)
        //     {
        //         cout << TempMatriz[i][j] << " \t";
        //     }
        //     cout << endl;
        // }


        // suma matriz temporal en la principal
        for (int i = 0; i < GallineroX; i++)
        {
            for (int j = 0; j < GallineroY; j++)
            {
                MainMatriz[i][j] += TempMatriz[i][j];
            }
        }


    }

    for (int i = 0; i < GallineroX; i++)
    {
        for (int j = 0; j < GallineroY; j++)
        {
            cout << MainMatriz[i][j] << " \t";
        }
        cout << endl;
    }
}