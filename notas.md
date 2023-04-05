## O Jantar dos Filósofos

### O Problema

Aqui estão as coisas que precisa de saber se quiser ter sucesso nesta tarefa:
- Um ou mais filósofos se reuniram para filosofar numa mesa redonda, cada um trouxe o seu garfo.
Há uma grande tigela de esparguete no meio da mesa, mas o macarrao tem tanto molho e está tão escorregadio que só é possível comer com dois garfos. Cada filósofo pega o garfo a sua direita e o garfo a sua esquerda para comer, um em cada mão.
- Os filósofos comem, pensam, ou dormem alternadamente. E só podem fazer uma tarefa por vez, isto é, enquanto fazem uma das tarefas não podem fazer as outras duas ao mesmo tempo.

Quando um filósofo acaba de comer, volta a pôr os garfos na mesa e começar a dormir. Uma vez acordados, começam de novo a pensar. A simulação pára quando um filósofo morre de fome.

- Todos os filósofos precisam de comer e nunca devem morrer de fome.
- Os filósofos não falam uns com os outros.
- Os filósofos não sabem se outro filósofo está prestes a morrer.
- Não há necessidade de dizer que os filósofos devem evitar a morte... :)

### Processos

Um processo pode ser visto como um container de recursos utilizado por uma ou mais tarefas do sistema.

Cada processo é isolado entre si e NÃO compartilham memória. Assim possuem níveis de operação e quais chamadas do sistema podem executar. As tarefas acessam os recursos dos processos aos quais elas estão abribuídas e não podem acessar os recursos de outros processos. 

O Kernel (núcleo do sistema operacional) possuem descritores de processos PCB - proccess control block - de todos os processos ativos, e cada processo possui um PID - proccess identifier. As tarefas de um mesmo processo podem trocar infos com facilidade, já que compartilham a mesma memória. Já as tarefas de processos diferentes só podem se comunicar por ipc, pelo kernel, inter-proccess-comunication.

Um processo é composto por diversas THREADS.
Uma thread é uma linha de execussão dentro de um processo. Cada thread tem seu próprio estado de processamento e sua própria pilha, mas compartilham memória com as treads irmãs, filhas de um mesmo processo. As threads são linhas de execussões de um processo que podem rodar concomitantemente.

PROBLEMAS: 

    Deadlock - bloqueio - quando 2 processos tentam acessar o mesmo recurso... um processo acaba bloqueando o outro, ou seja, um processo tem que esperar o outro acabar para poder acessar aquele recurso. Impede a execussão dos comandos e a fluidez do sistema.

    STARVATION - uma thread nunca é executada pois espera a resposta de outra, que morreu ou está bloqueada - virando uma thread zumbi. 

Soluções:

    Ativar e desativar as interrupções. Um processo ativa interrupções ao entrar em uma zona crítica e as desativa quando sair dela.

    Variáveis de bloqueio - var = 1 (região de bloqueio está ocupada) e var = 0 (região de bloqueio não está ocupada).

    Alternância estrita - turn = 1 ; processo A executa o que precisa depois faz turn = 0; qnd turn = 0 processo B comeca a execussão, e assim vão alternando.

A interação e execussão podem ser manipuladas por Paralelismo e Concorrência aumentando o desempenho do programa, aumentando a quantidade de tarefas que podem ser executadas num período de tempo.

### Estrutura

Cada Filósofo representa uma thread e cada garfo é um semáforo;
Pegar o garfo - aciona a operação wait no semárofo, e quando larga, aciona o signal nesse mesmo semáforo.

Os semáforos controlam o acesso aos recursos compartilhados em um ambiente multitarefas.
Semáforos:  - inicialização
            - operação wait
            - operação signal
Enquanto um processo estiver realizando operações em um semáforo, nenhum outro pode realizar, devendo esperar que o primeiro encerre ela.

Um semáforo binário, ou princípio de exculsão mútua, é um MUTEX, podendo assumir o valor de wait = 0, ou de signal = 1. É usado em programação concorrente, para evitar que dois processos ou threads tenham acesso simultâneo a um recurso partilhado.