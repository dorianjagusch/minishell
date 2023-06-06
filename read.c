#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd;
    int i = 0;

    if (fd = open("test_gnl/test.txt", O_RDONLY))
        return (1);
    while (i++ < 50)
       read(fd, NULL, 234285)
    if (close(fd)< 0)
        return 2;
    return 0;
}