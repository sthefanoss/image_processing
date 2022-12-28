# Tarefa 2

Realizar a leitura do texto T06, disponível no MATERIAL DE APOIO. 

Realizar testes com
os arquivos de código-fonte disponibilizados na aba COD. Elaborar um programa, em
Linguagem C++, com utilização da biblioteca OpenCV, para ler uma imagem em cores
RGB, com ruído salt-and-pepper. 

A seguir, aplicar os filtros estudados no texto T06,
exibindo as imagens resultantes em uma única janela OpenCV, contendo também a
imagem original ruidosa. 


---

## Como rodar
Este programa espera o caminho para a imagem como parâmetor.
```BASH
g++ task2.cpp -o task2.out `pkg-config --cflags --libs opencv4`
```
```BASH
./task2.out [CAMINHO PARA IMAGEM]
```

### Exemplo 
```BASH
./task2.out balloons_noisy.png 
```
## Como usar
Ao abrir o programa passando o caminho para imagem, duas trackbars estarão disponíveis para a interação.

### Tamanho da janela
A primeira trackbar define o tamanho da janela do filtro, seja para convolução ou para mediana. **Este tamanho precisa ser ímpar**, ou a função que reduz filtro por mediana iria atirar uma exceção. O tratamento do programa simplesmente ignora números pares.

Para janela 3x3 com valor central 1:
```cpp
float[3][3] filtro = {
    1.0/9.0,  1.0/9.0, 1.0/9.0,
    1.0/9.0,  1.0/9.0, 1.0/9.0, 
    1.0/9.0,  1.0/9.0, 1.0/9.0
};
```

Para janela 5x5 com valor central 1:
```cpp
float[5][5] filtro = {
    1.0/25.0,  1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
    1.0/25.0,  1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
    1.0/25.0,  1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
    1.0/25.0,  1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0,
    1.0/25.0,  1.0/25.0, 1.0/25.0, 1.0/25.0, 1.0/25.0
};
```

### Valor central

A segunda trackbar define o valor central da janela de média ponderada.

Para janela 3x3 com valor central 8:
```cpp
float[3][3] filtro = {
    1.0/16.0,  1.0/16.0, 1.0/16.0,
    1.0/16.0,  8.0/16.0, 1.0/16.0, 
    1.0/16.0,  1.0/16.0, 1.0/16.0
};
```

Para janela 5x5 com valor central 8:
```cpp
float[5][5] filtro = {
    1.0/32.0,  1.0/32.0, 1.0/32.0, 1.0/32.0, 1.0/32.0,
    1.0/32.0,  1.0/32.0, 1.0/32.0, 1.0/32.0, 1.0/32.0,
    1.0/32.0,  1.0/32.0, 8.0/32.0, 1.0/32.0, 1.0/32.0,
    1.0/32.0,  1.0/32.0, 1.0/32.0, 1.0/32.0, 1.0/32.0,
    1.0/32.0,  1.0/32.0, 1.0/32.0, 1.0/32.0, 1.0/32.0
};
```
---
Enviar o arquivo da atividade (atv-06.cpp) e o arquivo da imagem
utilizada (imagem.jpg), para glaucius@pelotas.ifsul.edu.br. 