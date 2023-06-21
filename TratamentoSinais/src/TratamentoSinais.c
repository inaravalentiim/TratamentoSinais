#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define URL_MAX_TAM 256

void abrirFirefox(char* url) {
	char comando[URL_MAX_TAM + 10];
	sprintf(comando, "firefox %s", url);
	system(comando);
}

void handleSignal(int signal) {
	if(signal == SIGUSR2){
		char url[URL_MAX_TAM];
		printf("Digite a URL que deseja abrir no Firefox: ");
		scanf("%s", url);
		abrirFirefox(url);
	}
}

int main() {
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handleSignal;
	sigaction(SIGUSR2, &sa, NULL);

	printf("Esperando sinal SIGUSR2...\n");

	pid_t pid = getpid();

	kill(pid, SIGUSR2);


	while(1) {
		sleep(1);
	}

	return 0;

}
