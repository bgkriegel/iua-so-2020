#/**************************************************************\
#Autor: Eliana Cano
# Practico: 1
#Objetivo: Practicar el uso de ps y kill.
# Fecha: 22/03/2020
#\**************************************************************/

echo "**************************Procesos de todos los usuarios: ******************************"

ps aux
echo " "

echo "*************************Procesos en su jerarquia padre-hijo: **************************"

ps al
echo " "

echo "******Al usar el comando ps, este se muestra como un proceso más en la lista de procesos******"
echo "Por eso, si quisiera matar al proceso ps con el comando kill, debería filtrarlo, obtener su segunda columna (que es su PID) y pasarla como argumento al comando kill: "
echo " "

ps aux | grep aux -m 1 | awk '{print $2}' | xargs kill #Uso awk para mostrar solo la segunda columna del proceso, y el modificador -m para mostrar solo el primer resultado de grep
echo " "

echo "*******Pero luego de ejecutarse el comando ps, este finaliza, y kill ya no puede enviarle una señal*******."

