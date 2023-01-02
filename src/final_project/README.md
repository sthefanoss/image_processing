# Projeto final

Este projeto é um experimento de detecção de fundo verde.


---

## Como rodar
```BASH
g++ final_project.cpp -o final_project.out `pkg-config --cflags --libs opencv4`
```
```BASH
./final_project.out [CAMINHO PARA IMAGEM FOREGROUND] [CAMINHO PARA IMAGEM BACKGROUND]
```
### Exemplo 
```BASH
./final_project.out input.jpg background.jpg
```

https://br.freepik.com/fotos-gratis/closeup-infeliz-feliz-pessoa-problema_1102577.htm

https://br.freepik.com/fotos-gratis/bela-praia-tropical-e-mar-com-coqueiro-na-ilha-paradisiaca_3661759.htm