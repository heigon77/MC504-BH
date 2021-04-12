# mc504-aplicacao-multithread

Este projeto visou o desenvolvimento de uma primeira aplicação utilizando Pthreads, com escolha de tema livre, sem necessidade do uso de mecanismos de sincronização. É necessário indicar o tema, a estrutura de dados principal e a estratégia de divisão de trabalho entre as threads. Também devem ser indicados links para o código e para o vídeo. A postagem do link do vídeo no mural é opcional.

## Natal e três filhas

Uma mãe pode comprar até cinco presentes de Natal para suas filhas Bruna, Letícia e Natasha.

As filhas têm uma lista de cinco presentes que querem, cada uma. 

A mãe alterna entre Bruna, Letícia e Natasha jogando uma moeda. Se cair cara, a filha diz qual presente ela quer e a mãe adiciona na lista de presentes. Se cair coroa, pula para a próxima filha. Assim se repete até a lista com cinco presentes estar cheia.

## Implementação

A mãe e as filhas são implementadas como três pthreads.

A mãe gerencia o acesso das filhas a lista de presente e faz a contagem da lista até ficar cheia. Quando cheia, a lista é esvaziada.

## Compilação

`gcc src/* -o build/main -lpthread`

## Vídeo

[TEM QUE FAZER UM VÍDEO APARENTEMENTE]

