#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigmanager(int sig_num, void (*manager)());

void capture_int_signal()
{
  printf("\n *** Captured SIGINT signal (Interrupt): %d ***\n\n", SIGINT);
  sigmanager(SIGINT, capture_int_signal);
}

void capture_tstp_signal()
{
  printf("\n *** Captured SIGTSTP signal (Suspend): %d ***\n\n", SIGTSTP);
  printf("Finishing process...\n");
  /* Finalizar proceso */
  exit(0);
}

void sigmanager(int sig_num, void (*manager)())
{
  /* Reasignar la señal */
  signal(sig_num, manager);
  /* Limpiar buffer del teclado */
  fflush(stdout);
}

int main()
{
  sigmanager(SIGINT, capture_int_signal);
  sigmanager(SIGTSTP, capture_tstp_signal);

  while (1)
  {
    printf("Esperando que llegue una señal para capturarla...\n");
    sleep(2);
  }

  return 0;
}