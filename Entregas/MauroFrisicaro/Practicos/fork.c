/* 2. Escriba un programa (en C) que utilice la llamada fork() para 
   crear un nuevo proceso. Es necesario que cada proceso escriba un 
   mensaje diferente en pantalla.
*/


int main() {
	int pid;
	...
	pid = fork();
	if (pid == 0) {
		/* hijo */
		...
	} else {
	/* padre */
		...
	}
	return 0;
}
