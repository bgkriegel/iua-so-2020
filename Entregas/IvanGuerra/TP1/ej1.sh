#!/bin/bash
echo "\nComando #1 => 'ps aux'"
echo "Este comando nos permite obtener información sobre todos los procesos en ejecución en el SO"
echo "-------------------------------------------------------------------------------------------\n"

ps aux

echo "\nComando #2 => 'ps al'"
echo "Este comando nos permite obtener información sobre los procesos en su jerarquía padre-hijo"
echo "-------------------------------------------------------------------------------------------\n"

ps al

echo "\nComando #3 => 'kill <signal> PID'"
echo "Este comando nos permite enviar una señal a un proceso determinado."
echo "En este caso, enviaremos la señal SIGKILL (-9) al proceso donde estamos editando este script (Editor VS Code) para forzar su detencion."
echo "Para ello: \n 1) Ejecuto el comando 'ps aux' para listar todos los procesos \n 2) filtro la salida generada buscando por el nombre del proceso y solo obteniendo el primer resultado que genere dicho filtro. \n 3) Proceso el resultado de la salida del comando anterior, obteniendo solo la segunda columna del resultado. En este caso es el valor de PID del proceso. \n 4) Obtengo la salida del comando anterior y se lo envio como parametro al final del comando señalado luego de xargs."
echo "---------------------------------------------------------------------------------------------------------------------\n"

ps aux | grep /usr/share/code/code -m 1 | awk '{print $2}' | xargs kill -9

echo "La señal fue enviada al proceso con exito."