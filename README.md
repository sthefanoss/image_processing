# Repositório para disciplina de Processamento de Imagens

É isso aí.

## Referências:
- https://www.youtube.com/watch?v=mqVMUKX_hPE
- http://www2.pelotas.ifsul.edu.br/glaucius/pid/index.html

## Como rodar
```BASH
g++ exemplo.cpp -o exemplo.out `pkg-config --cflags --libs opencv4`
```
```BASH
./exemplo.out
```

## Substituições para o OpenCV 4
- CV_LOAD_IMAGE_COLOR -> IMREAD_COLOR
- CV_WINDOW_AUTOSIZE -> WINDOW_AUTOSIZE
- CV_IMWRITE_PNG_COMPRESSION -> IMWRITE_PNG_COMPRESSION
- CV_RGB2YCrCb -> COLOR_RGB2YCrCb
- CV_BGR2GRAY -> COLOR_BGR2GRAY