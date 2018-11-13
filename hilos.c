#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

double counter = 0;
#define ITER	50
#define NHILOS	4


int eligiendo[NHILOS];
int numero[NHILOS];

  int max(int *num){
    int max_num = 0;

    for (size_t i = 0; i < NHILOS; i++) {
      if(num[i] > max_num){
        max_num = num[i];
      }
    }
    return max_num;
  }

  void seccion_critica(int *id){
    int a;
    a = (*id);

    for (int i = 0; i < NHILOS; i++) {
      eligiendo[a] = true;
      numero[a] = 1 + max(numero);
      eligiendo[a] = false;

      for (int j = 0; j < NHILOS; j++) {
        while(eligiendo[j]){ }
        while((numero[j] != 0)  && ((numero[j], j)  < (numero[a], a))){ }
      }//for
    }//for principal
  }

void fin_seccion(int *id){
  numero[*id] = 0;
}




int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    void *adder(void *);
    double *r_value;

    for (size_t i = 0; i < NHILOS; i++) {
      eligiendo[i] = false;
      numero[i] = 0;
    }


    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))//adder debe ser funcion void* // v[i] son los argumentos que se le pasan (hacer casting void*)
	    exit(status);
    }

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

void *adder(void *p)
{
    double l, *to_return;
    extern double counter;
    int *id, i;

    id = (int *) p;

    for (i = 0; i < ITER; i++) {//incrementa la variable counter
      seccion_critica(id);
	l = counter;
	l++;
	counter = l;//counter esta compartida entre todos los hilos
  fin_seccion(id);
    }

    to_return = malloc(sizeof(double));//reservo memoria porque al hacer pthread exit se pierde el valor, entonces puedo devolverla y la recojo en el join

    *to_return = counter;//se iguala para ver hasta donde llega cada hilo

    pthread_exit((void *) to_return);
}
