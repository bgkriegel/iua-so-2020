/**************************************************************\
 Autor: Leonel Pacha
 Practico: 4
 Objetivo: Finalizar un programa dependiendo del contenido de un 
 archivo, que es controlado por otro proceso.
 Fecha: 20/04/2020
\**************************************************************/

/*Intercambio de mensajes entre dos procesos utilizando un archivo
Sean dos procesos, A y B, los cuales van a 'hablar'
A crea un archivo, ej. comunicador.txt, y escribe dentro de el un mensaje.
Luego lee periodicamente el archivo y espera que el mensaje 'cambie',
cuando descubre que ha cambiado termina.

B verifica que exista el archivo anterior, cuando lo encuentra lo lee,
luego lo sobre-escribe con un mensaje de respuesta, cierra el archivo
y termina.
*/

