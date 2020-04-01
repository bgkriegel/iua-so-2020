#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

void sigmanager(int sig_num, void (*manager)());

void capture_int_signal()
{
  printf("\n\n*** Captured SIGINT signal (Interrupt). Keep executing the process... ***\n");
  sigmanager(SIGINT, capture_int_signal);
}

void capture_tstp_signal()
{
  printf("\n\n*** Captured SIGTSTP signal (Suspend). Finishing process execution... ***\n");
  exit(0);
}

void capture_int_signal_father()
{
  /* Envio la señal de INT del proceso padre al hijo */
  sigmanager(SIGINT, capture_int_signal);
}

void capture_tstp_signal_father()
{
  /* Envio la señal de TSTP del proceso padre al hijo */
  sigmanager(SIGTSTP, capture_tstp_signal);
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
  pid_t pid;
  int status;

  pid = fork();

  if (pid == 0)
  {
    // Proceso hijo (Nuevo proceso creado)
    printf("Soy el proceso hijo. Mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());

    sigmanager(SIGINT, capture_int_signal);
    sigmanager(SIGTSTP, capture_tstp_signal);

    while (1)
    {
      printf("\nEsperando que llegue una señal para capturarla (Presione Ctrl+C or Ctrl+Z)...");
      sleep(2);
    }
  }
  else
  {
    // Proceso padre (Proceso que creo el nuevo proceso)

    // Capturo las señales desde el proceso padre y se las envio al hijo
    sigmanager(SIGINT, capture_int_signal_father);
    sigmanager(SIGTSTP, capture_tstp_signal_father);

    // Espero que el hijo termine su ejecucion
    wait(&status);

    if (WIFEXITED(status))
    {
      printf("\nPrograma terminado con normalidad.\n");
    }
  }

  return 0;
}