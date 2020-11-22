# UF-Prog2

Disciplina: Progamação 2
Tentativa 2 (ERE) - 2020.2
Prof: Maziero

## Verificador Ortografico

- /tentativa1/VerificadorOrtografico/

- [Especificações do projeto](http://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:verificador_ortografico)

`./ortografia [dicionario] < entrada.txt > saida.txt`

### Entrada

``` txt
Para que o pocessador possa interromper a execução de uma tarefa
e retornar a ela mais tarde, sem corromper seu estado interno,
é necessário definir operações para salvar e restaurrar o
contexto da tarefa.

O ato de salvar os valores do contexto atual em seu TCB e
possivelmente restaurar o contexto de outra tarefa, previamente
salvo em outro TCB, é denominado "troca de contexto".
```

### Saída

``` txt
Para que o [pocessador] possa interromper a execução de uma tarefa
e retornar a ela mais tarde, sem corromper seu estado interno,
é necessário definir operações para salvar e [restaurrar] o
contexto da tarefa.

O ato de salvar os valores do contexto atual em seu [TCB] e
possivelmente restaurar o contexto de outra tarefa, previamente
salvo em outro [TCB], é denominado "troca de contexto".
```

## Fotomosaico

_"Um fotomosaico ou mosaico fotográfico é uma fotografia construída a partir de imagens menores, ou “pastilhas” (do inglês tiles). As pastilhas são escolhidas de forma a reproduzir a cor e intensidade luminosa do bloco da imagem original correspondente, gerando um efeito visual muito interessante."_

- [Especificações do projeto](http://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:fotomosaico)
- [link imagem](https://unsplash.com/photos/MDyyjPovaWA)

`./mosaico -p ./tiles/ -i input.ppm -o output.ppm`

### Imagem fonte

![imagem fonte](./images/fotomosaico1.png)

### Imagem gerada

![imagem processada](./images/fotomosaico2.png)
