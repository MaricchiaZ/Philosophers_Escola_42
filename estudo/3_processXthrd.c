// estudo baseado em: https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// alterando o valor de x em um processo, o outro processo não "vê" essa alteração, já que cada um dos 
// processos tem sua própria memória
int main(int arhc, char **argv)
{
    int x = 2;
    int pid = fork();
    if (pid == -1)
        return 1; // erro se o pid der errado
    if (pid == 0)
        x++;
    sleep (2);
    printf("Value of x: %d\n", x);
    if (pid != 0)
        wait (NULL);
    return (0);
}
