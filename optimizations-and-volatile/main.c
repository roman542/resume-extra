#include <unistd.h>
#include <pthread.h>

// Linux only, but cygwin should be able to run it.
// It's short of 1 keyword to be fully correct.

// uncomment the next line to fix this program.
// volatile 
int turn;

#define S(X) X, sizeof(X)

void *thread1(void *a) {
	while (1) {
		while(!turn);
		write(1, S("|"));
		sleep(1);
		turn = 0;
	}
}

void *thread2(void *a) {
	while (1) {
		while(turn);
		write(1, S("."));
		sleep(1);
		turn = 1;
	}
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, 0, &thread1, 0);
	pthread_create(&t2, 0, &thread2, 0);
	pthread_join(t1, 0);
}
