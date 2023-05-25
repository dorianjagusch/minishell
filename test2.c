
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int result;

    result = access("src/utils/ft_error.c", F_OK);
    printf("%d\n", result);
    return(0);
}