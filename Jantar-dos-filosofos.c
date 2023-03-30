#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define PENSANDO 2
#define FOME 1
#define COMENDO 0
#define ESQUERDA (phnum + 4) % N
#define DIREITA (phnum + 1) % N

int estado[N];
int fil[N] = {0, 1, 2, 3, 4}; // 5 filósofos

sem_t mutex; // exclusão mútua para evitar deadlock
sem_t S[N];

// verifica se pode ou não pegar os garfos e começar a comer
void tenta_comer(int phnum) {
  if (estado[phnum] == FOME && estado[ESQUERDA] != COMENDO &&
      estado[DIREITA] != COMENDO) {

    // estado COMENDO
    estado[phnum] = COMENDO;

    sleep(2);

    printf("Filósofo %d pega os garfos %d e %d\n", phnum + 1, ESQUERDA + 1,
           phnum + 1);

    printf("Filósofo %d está comendo\n\n", phnum + 1);

    // libera o semáforo para o filósofo que está comendo
    sem_post(&S[phnum]);
  }
}

void pega_garfo(int phnum) {

  // bloqueia o semáforo para evitar compartilhamento de recurso
  sem_wait(&mutex);

  // muda o estado para fome
  estado[phnum] = FOME;

  printf("Filósofo %d está com fome\n\n", phnum + 1);

  // come se os vizinhos não estão comendo
  tenta_comer(phnum);

  // libera o semáforo
  sem_post(&mutex);

  // se não for possível comer espera até ser sinalizado
  sem_wait(&S[phnum]);

  sleep(1);
}

void solta_garfo(int phnum) {

  // bloqueia o semáforo para evitar compartilhamento de recurso como garfo
  sem_wait(&mutex);

  // muda o estado para pensando e solta os garfos
  estado[phnum] = PENSANDO;

  printf("Filósofo %d solta os garfos %d e %d\n", phnum + 1, ESQUERDA + 1,
         phnum + 1);
  printf("Filósofo %d está pensando\n\n", phnum + 1);

  tenta_comer(ESQUERDA); // verifica se o filósofo da esquerda pode comer
  tenta_comer(DIREITA);  // verifica se o filósofo da direita pode comer

  // desbloqueia o semáforo para os outros filósofos usarem os recursos
  // compartilhados
  sem_post(&mutex);
}

void *filosofo(void *num) {

  while (1) {

    int *i = num;

    sleep(1);
    pega_garfo(*i);
    sleep(1);
    solta_garfo(*i);
  }
}

int main() {
  int i;
  pthread_t thread_id[N]; // array de N threads, uma para cada filósofo

  // inicia os semáforos
  sem_init(&mutex, 0, 1);

  for (i = 0; i < N; i++)
    sem_init(&S[i], 0, 0);

  for (i = 0; i < N; i++) {
    // cria thread para cada filósofo
    pthread_create(&thread_id[i], NULL, filosofo, &fil[i]);

    printf("Filósofo %d está pensando\n", i + 1);
  }
  printf("\n");
  // espera a finalização de todas as threads antes de terminar a execução do
  // programa
  for (i = 0; i < N; i++)
    pthread_join(thread_id[i], NULL);
}