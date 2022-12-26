# Tarefa 1

Realizar a leitura do texto T03, disponível no MATERIAL DE APOIO. 

Realizar testes com
os arquivos de código-fonte disponibilizados na aba COD.
Elaborar um programa, em Linguagem C++, com utilização da biblioteca OpenCV, para ler
um imagem em cores RGB. 

A seguir, converter esta imagem para os espaços de cores:
GRAY (256 tons de cinza), HSV e YCrCb. Exibir as quatro imagens, incluindo a imagem
original RGB, em uma única janela gráfica OpenCV, em uma matriz de imagens 2x2.

---

## Como rodar
```BASH
g++ task1.cpp -o task1.out `pkg-config --cflags --libs opencv4`
```
```BASH
./task1.out
```

---
Enviar o arquivo da atividade (atv-03.cpp) e o arquivo da imagem utilizada (imagem.jpg),
para glaucius@pelotas.ifsul.edu.br.