/*
*------------------------------------------
* Laboratorio 3.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
/*
*------------------------------------------
* Laboratorio 3.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
* CC3086 - Programacion de Microprocesadores
* Fabian Juárez 21440
*------------------------------------------
* Descripción: Programa el cual se encargara de realizar un calculo
 * del valor de la convergencia para la serie geométrica.
 * La escogida por mi persona fue la opcion a
*------------------------------------------
*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sstream>

using namespace std;
pthread_mutex_t bloquear = PTHREAD_MUTEX_INITIALIZER;
long exponente;
double resultSUM;
void *output;
//Creacion de la serie geometrica con la cual se obtendra el valor de cada thread por separado
void *serieGeometrica(void *arg){
    long exponente ;
    exponente = (long) arg;
    double numero = 2;
    double numerador = 3;
    double potencia;
    
    pthread_mutex_lock(&bloquear);//se bloqueara para que solo un thread acceda y permita ejecutarse de manera de espera
    potencia = pow(numero,exponente);    //calcular el resultado de 2^n
    //calculara el dato de 3/2^n y lo guardara en el resultado para ser enviado al total
    double* resultado = (double*) malloc(sizeof(double));
    *resultado =  (numerador/potencia) ;
    cout << "\n El valor de n: " << exponente << " resultado: " << *resultado << endl;
    pthread_mutex_unlock(&bloquear);
    return (void *) resultado;
}
int main() {
    cout << "Ingresar el valor de n: " << endl;//Ingreso de usuario
    cin >> exponente;
    pthread_t threads[exponente]; // cantidad de threads a implementar en un arrya de ellos
    // Creacion y union de los threads para poderlos utilizar y encontrar el valor de la serie geometrica
    for (int i = 0; i <= exponente; i++) {
        pthread_create(&threads[i], NULL, serieGeometrica, (void *) i);
        pthread_join(threads[i], &output);
        double result = *(double *) output;
        resultSUM += result;
    }
    cout << "\n--------------------------------------------------------------" << endl;
    cout << "\nresultado final posterior a la sumatoria de todos los resultados: " << resultSUM << endl;
    return 0;
}