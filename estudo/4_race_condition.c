// estudo baseado em: https://www.youtube.com/watch?v=FY9livorrJI&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=3

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 
int mails = 0;

void *routine()
{
    for (int i = 0; i < 10000000; i++) // se vc colocar 1 milhão, era pra as duas thread colocarem 1 milhão,
    // mas uma atropela o funcionamento da outra, e isso causa um valor final diferente e menor do 
    // que 2 milhões ... isso é o data_racing
        mails++;
}

int main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;
    if (pthread_create(&t1, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 2;
    if (pthread_join(t1, NULL)) // conferimos se o nosso "wait" funcionou
        return 3;
    if (pthread_join(t2, NULL)) // conferimos se o nosso "wait" funcionou
        return 4;
    printf("Number of mails: %d\n", mails);
    return (0);
}
