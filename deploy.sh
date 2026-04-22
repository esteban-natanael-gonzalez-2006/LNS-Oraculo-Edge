#!/bin/bash
# LNS-Oraculo-Edge: Auto-Despliegue y Benchmark

echo "[+] Inicializando protocolo de despliegue LNS (Zero-Trust Edge AI)..."

# 1. Instalación de dependencias (Silenciosa)
echo "[*] Verificando compiladores y transductores..."
pkg update -y -q
pkg install clang python git -y -q

# 2. Clonación o actualización del núcleo
if [ ! -d "LNS-Oraculo-Edge" ]; then
    echo "[*] Extrayendo arquitectura desde el repositorio base..."
    git clone https://github.com/TU_USUARIO_REAL/LNS-Oraculo-Edge.git
fi
cd LNS-Oraculo-Edge || exit

# 3. Forja del Silicio
echo "[*] Compilando motor vectorial C++ (Bypass FPU -> INT8)..."
clang++ -O3 -march=armv8-a -fPIC -shared -o liblnsindex.so lns_index.cpp

# 4. Detonación del Benchmark
echo "[+] Forja completada. Iniciando prueba de estrés en 100,000 tensores..."
sleep 1
python search_lns.py
