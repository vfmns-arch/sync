Sincronização de Passageiros e Carros

Este projeto implementa um mecanismo de sincronização entre passageiros e carros utilizando threads em C e a biblioteca POSIX Threads (pthread).

O objetivo é garantir que os passageiros embarquem corretamente, respeitando a quantidade de assentos disponíveis, e que o carro aguarde até que todos os passageiros previstos tenham embarcado.

Arquivos

* sync_car.c: Implementa as funções de sincronização da estação:
    * station_init(): Inicializa as estruturas de sincronização e as variáveis da estação.
    * station_load_car(): Gerencia a chegada do carro e aguarda o embarque dos passageiros.
    * station_wait_for_car(): Gerencia a espera e o embarque dos passageiros.
    * station_on_board(): Registra o embarque de um passageiro e notifica as demais threads.
* sync_car-runner.c: Contém o programa principal e os testes da implementação. Cria threads para simular passageiros e carros, verifica o funcionamento da sincronização e utiliza limites de tempo para identificar possíveis deadlocks.
* sync_car.h: Declara a estrutura station e as funções utilizadas pela implementação e pelo programa de testes.
* Makefile: Automatiza a compilação e a limpeza dos arquivos gerados.

Requisitos

* GCC
* GNU Make
* Biblioteca POSIX Threads (pthread)
* Sistema operacional Linux ou WSL.

Compilação

Clone o repositório e entre na pasta do projeto:

git clone https://github.com/vfmns-arch/sync.git
cd sync

Compile utilizando o Makefile:

make

Alternativamente, compile diretamente com GCC:

gcc -Wall -Wextra -pthread -o sync_car sync_car.c sync_car-runner.c

Execução

Após a compilação, execute o programa:

./sync_car

Testes

O próprio arquivo sync_car-runner.c funciona como um programa de testes automatizados.

Ele simula o embarque de 100 passageiros em diferentes carros, com quantidades aleatórias de assentos disponíveis, verificando se:

* O carro não espera quando não existem passageiros para embarcar.
* O carro aguarda até que todos os passageiros previstos tenham embarcado.
* A sincronização não apresenta deadlocks ou atrasos excessivos.

Se todos os testes forem concluídos corretamente, será exibida a mensagem:

Looks good!

Limpeza:

Para remover o executável gerado:

make clean
