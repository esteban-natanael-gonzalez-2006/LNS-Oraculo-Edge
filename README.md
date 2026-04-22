# LNS-Oraculo-Edge: Zero-Trust Vector Search Engine on ARM64

## Abstract
Este repositorio implementa un motor de inferencia y recuperación vectorial (Retrieval-Augmented Generation - RAG) escrito en C++ puro con intrínsecos ARM NEON. Está diseñado para operar en entornos *Air-Gapped* (desconectados) de alta confidencialidad (Firmas Legales, Contabilidad). Utiliza Sistemas Numéricos Logarítmicos (LNS) para erradicar la dependencia de la Unidad de Coma Flotante (FPU), ejecutando inferencia sobre tensores INT8 en dispositivos de bajísimos recursos.

## Rendimiento Empírico (Benchmark)
- **Hardware Target:** Cortex-A53 (Android 11 / Termux).
- **Carga de Datos:** 100,000 vectores simulados de 768 dimensiones.
- **Latencia Demostrada:** ~98.86 ms por Query.
- **Ventaja Arquitectónica:** Bypass absoluto de bibliotecas pesadas (ej. FAISS). Consumo térmico, de batería y RAM reducidos a un nivel apto para Edge Computing.

## Guía de Reproducibilidad
Para compilar y verificar la latencia en cualquier dispositivo ARM64 con entorno Linux/Termux:

1. **Compilar el Núcleo (Silicio Dinámico):**
   `clang++ -O3 -march=armv8-a -fPIC -shared -o liblnsindex.so lns_index.cpp`

2. **Ejecutar el Benchmark en Python:**
   `python search_lns.py`

## Licencia
Este proyecto está bajo la Licencia **GNU GPLv3**. El código es abierto, pero cualquier uso comercial o integración en software privativo exige la publicación de dicho código derivado bajo los mismos términos, o la adquisición de una Licencia Comercial Exclusiva por parte del autor.

## Contacto & Citación
**Autor:** Esteban Natanael Gonzalez - Arquitecto de Sistemas & Edge AI.

Si utiliza este motor para investigación científica, por favor cite:
@software{Gonzalez_LNS_Oraculo_2026,
author = {Gonzalez, Esteban Natanael},
title = {LNS-Oraculo-Edge: Zero-Trust Vector Search Engine on ARM64},
year = {2026},
publisher = {GitHub},
howpublished = {\url{https://github.com/TU_USUARIO_REAL/LNS-Oraculo-Edge}}
}
