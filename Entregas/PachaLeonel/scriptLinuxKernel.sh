echo "Extrayendo con xz"

xz -d linux-5.5.13.tar.xz

echo "Descomprimiendo tar"

tar xvf linux-5.5.13.tar

echo "Finalizado"

cd linux-5.5.13

echo "Entré a la carpeta descomprimida"

pwd

echo "Cantidad de archivos 'contando ocultos y directorios' en " | pwd

ls -a | wc -l