// estudo baseado em: https://www.youtube.com/watch?v=oq29KUy29iQ&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=4

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 
int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 10000000; i++){// se vc colocar 1 milhão, era pra as duas thread colocarem 1 milhão,
    // mas uma atropela o funcionamento da outra, e isso causa um valor final diferente e menor do 
    // que 2 milhões ... isso é o data_racing
        pthread_mutex_lock(&mutex); // protege contra outras threads acessarem ao mesmo tempo
        mails++;
        pthread_mutex_unlock(&mutex); // retira a proteção
    }
}

int main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;
    pthread_mutex_init(&mutex, NULL); // serve como um semáforo para evitar que duas threads acessem a mesma variável e modifiquem essa variável ao mesmo tempo
    if (pthread_create(&t1, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 2;
    if (pthread_create(&t3, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 3;
    if (pthread_create(&t4, NULL, &routine, NULL)) // converimos de a criação da thread funcionou
        return 4;
    if (pthread_join(t1, NULL)) // conferimos se o nosso "wait" funcionou
        return 5;
    if (pthread_join(t2, NULL)) // conferimos se o nosso "wait" funcionou
        return 6;
    if (pthread_join(t3, NULL)) // conferimos se o nosso "wait" funcionou
        return 7;
    if (pthread_join(t4, NULL)) // conferimos se o nosso "wait" funcionou
        return 8;
    pthread_mutex_destroy(&mutex); // desaloca a memória usada pelo mutex
    printf("Number of mails: %d\n", mails);
    return (0);
}
