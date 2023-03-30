# Jantar-dos-Filósofos

Integrantes
- Heitor Jody
- Rafael Yun

Nesse código usamos semáforos para garantir a exclusão mútua e evitar a ocorrência de deadlock. 
Cada filósofo é modelado como um processo separado, que tenta pegar os garfos (representados pelos semáforos S) à sua esquerda e à sua direita antes de começar a comer. 
Se um filósofo não consegue pegar ambos os garfos, ele libera o garfo que pegou e espera por um sinal para tentar novamente.


Referência:
- https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/
