# Jantar-dos-Filósofos

Integrantes
- Heitor Jody
- Rafael Yun

Nesse código usamos semáforos para garantir a exclusão mútua e evitar a ocorrência de deadlock. 
Cada filósofo é modelado como um processo separado, que tenta pegar os garfos (representados pelos semáforos S) à sua esquerda e à sua direita antes de começar a comer. 
Se um filósofo não consegue pegar ambos os garfos, ele libera o garfo que pegou e espera por um sinal para tentar novamente.


Referência:
- https://medium.com/swlh/the-dining-philosophers-problem-solution-in-c-90e2593f64e8#:~:text=The%20dining%20philosopher's%20problem%20is,sharing%20problem%20in%20operating%20systems.&text=Let%20us%20first%20understand%20what,access%20to%20a%20shared%20resource

- https://www.thecrazyprogrammer.com/2017/06/dining-philosophers-problem-c-c.html
