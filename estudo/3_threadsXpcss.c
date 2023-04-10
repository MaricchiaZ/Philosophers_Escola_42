// estudo baseado em: https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 
// alternando o valor de x em uma thread, todas as outras threads do mesmo processo "veem" a alteração
// já que as threads compartilham entre si a mesma memória

int x = 2;

void *routine()
{
    x++;
    sleep(2);
    printf("Value of x: %d\n", x);
}

void *routine2()
{
    sleep(2);
    printf("Value of x: %d\n", x);
}

int main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;
    if (pthread_create(&t1, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 1;
    if (pthread_create(&t2, NULL, &routine2, NULL)) // converimos de a criação da thread funcionou
        return 2;
    if (pthread_join(t1, NULL)) // conferimos se o nosso "wait" funcionou
        return 3;
    if (pthread_join(t2, NULL)) // conferimos se o nosso "wait" funcionou
        return 4;
    return (0);
}
