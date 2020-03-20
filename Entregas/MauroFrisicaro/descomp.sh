#!/bin/bash
wget -q cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.5.9.tar.xz
cd /home/$USER/Downloads
tar -xf linux-5.5.9.tar.xz
echo "La cantidad de archivos es: " $(find linux-5.5.9 -type f | wc -l)
