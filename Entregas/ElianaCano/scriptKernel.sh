echo "Se procede a extraer con xz"

xz -d linux-5.5.9.tar.xz

echo "Se procede a extraer con tar"

tar xvf linux-5.5.9.tar

echo "Extraido"

cd linux-5.5.9

echo "Actualmente en: "

pwd

echo "Cantidad de archivos: "

find . | wc -l


