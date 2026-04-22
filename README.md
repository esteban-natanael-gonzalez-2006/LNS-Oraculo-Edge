# LNS-Oraculo-Edge: Motor de Búsqueda Vectorial Zero-Trust
Este repositorio contiene un motor de inferencia y recuperación vectorial (RAG) escrito en C++ puro con intrínsecos ARM NEON. 

## Arquitectura
Utiliza Sistemas Numéricos Logarítmicos (LNS) para erradicar el uso de la Unidad de Coma Flotante (FPU), permitiendo realizar búsquedas de similitud sobre tensores INT8 en dispositivos de recursos limitados (Smartphones, SBCs) con latencias de milisegundos.

## Rendimiento Empírico
- **Hardware:** Cortex-A53 (Android / Termux).
- **Carga:** 100,000 vectores de 768 dimensiones.
- **Latencia:** ~102 ms.
- **Ventaja:** Bypass absoluto de bibliotecas pesadas como FAISS. Consumo térmico y de RAM minimizado.
