// estudo baseado em: https://www.youtube.com/watch?v=xoXzp4B8aQk&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=5

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 
int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 100000; i++){// se vc colocar 1 milhão, era pra as duas thread colocarem 1 milhão,
    // mas uma atropela o funcionamento da outra, e isso causa um valor final diferente e menor do 
    // que 2 milhões ... isso é o data_racing
        pthread_mutex_lock(&mutex); // protege contra outras threads acessarem ao mesmo tempo
        mails++;
        pthread_mutex_unlock(&mutex); // retira a proteção
    }
}

int main(int argc, char **argv)
{
    pthread_t th[4];
    int i;
    pthread_mutex_init(&mutex, NULL); // serve como um semáforo para evitar que duas threads acessem a mesma variável e modifiquem essa variável ao mesmo tempo
    for (i = 0; i < 4; i++)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0) // converimos de a criação da thread funcionou
        {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 4; i++)
    {
        if (pthread_join(th[i], NULL) != 0) // conferimos se o nosso "wait" funcionou
            return 2;
        printf("Thread %d has finish execution\n", i);
    }
    pthread_mutex_destroy(&mutex); // desaloca a memória usada pelo mutex
    printf("Number of mails: %d\n", mails);
    return (0);
}
