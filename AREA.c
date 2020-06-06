#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

int kolo = 0, kwadrat = 0; //przyjmuje r=1
pthread_mutex_t sygnalizacja = PTHREAD_MUTEX_INITIALIZER;

void* losowanko() {
	double x, y;
	//Metoda Monte Carlo
	for (int i = 0; i < 5; ++i) {
		x = (double)rand() / (RAND_MAX + 2.0);
		y = (double)rand() / (RAND_MAX + 2.0);
		printf("x = %f  y = %f\n", x, y);
		if ((x * x + y * y) < 1) {
			pthread_mutex_lock(&sygnalizacja);
			kolo = kolo + 1;
			pthread_mutex_unlock(&sygnalizacja);
		}
		else {
			pthread_mutex_lock(&sygnalizacja);
			kwadrat = kwadrat + 1;
			pthread_mutex_unlock(&sygnalizacja);
		}
	}
	return;
}

void error(char* msg)
{
	fprintf(stderr, "%s:%s\n", msg, strerror(errno));
	exit(1);
}


void main() {
	int zarodek;
	time_t tt;
	zarodek = time(&tt);
	srand(zarodek);


	pthread_t t0;
	pthread_t t1;

	if (pthread_create(&t0, NULL, losowanko, NULL) == -1)
		error("Nie mozna utworzyc watku t0");
	if (pthread_create(&t1, NULL, losowanko, NULL) == -1)
		error("Nie mozna utworzyc watku t1");


	void* result;
	if (pthread_join(t0, &result) == -1)
		error("Blad oczekiwania na zakonczenie watku t0");
	if (pthread_join(t1, &result) == -1)
		error("Blad oczekiwania na zakonczenie watku t0");
	double wyn = (double)4.0 * kolo / ;
	printf(" pi = %f", wyn);
	return 0;
}

