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
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sstream>
using namespace std;
pthread_mutex_t bloquear = PTHREAD_MUTEX_INITIALIZER;
long exponente;
double resultSUM;
void *output;
void *serieGeometrica(void *arg){
    long exponente ;
    exponente = (long) arg;
    double numero = 2;
    double numerador = 3;
    double potencia;
    //calcular el resultado de 2^n
        potencia = pow(numero,exponente);

    //calcular 3/2^n
    double* resultado = (double*) malloc(sizeof(double));
    *resultado =  (numerador/potencia) ;
    pthread_mutex_lock(&bloquear);
    cout << "\n El valor de n: " << exponente << " resultado: " << *resultado << endl;
    pthread_mutex_unlock(&bloquear);
    return (void *) resultado;
}
int main() {
    cout << "Ingresar el valor de n: " << endl;
    cin >> exponente;
    pthread_t threads[exponente+1];
    for (int i = 0; i <= exponente; i++) {
        pthread_create(&threads[i], NULL, serieGeometrica, (void *) i);
    }
    for(int i = 0; i <= exponente; i++){
        pthread_join(threads[i], &output);
        double result = *(double *) output;
        resultSUM += result;
    }
    cout << "--------------------------------------------------------------" << endl;
    cout << "\nresultado final posterior a la sumatoria de todos los resultados: " << resultSUM << endl;
    return 0;
}