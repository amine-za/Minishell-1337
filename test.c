#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    while (1)
    {
        system("leaks minishell");
        sleep(1);
    }
    return (0);
}
