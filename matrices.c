#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void *funcion(void *p ){
  int *v;
  v = (int *)malloc(3*sizeof(int));
  int *hilo;
  hilo = (int *)p;

    

  pthread_exit(hilo);
}


void rellenamatriz( int m[3][3]){
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      m[i][j] = rand()%10;
    }
  }
}

void rellenavector(int v[3]){
  for (size_t i = 0; i < 3; i++) {
    v[i] = rand()%10;
  }
}

int main(){
  int m[3][3];
  int v[3];
  srand(time(NULL));

  rellenamatriz(m);
  rellenavector(v);

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      printf("%d\t", m[i][j] );
    }
    printf("\n");
  }

printf("\n");

  for (size_t i = 0; i < 3; i++) {
    printf("v[%d] = %d\n", i , v[i] );
  }



  pthread_t hilos[3];

for (int i = 0; i < 3; i++) {
    pthread_create(&hilos[i] , NULL , (void *)funcion , (void *)i );
}

int valor[3];

  for (size_t i = 0; i < 3; i++) {
    pthread_join(hilos[i] , (void **)&valor[i]);
    printf("\n");
    printf("%d\n", valor[i] );
  }

  return 0;
}
