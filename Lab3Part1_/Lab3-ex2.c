#include <stdio.h>

int main(void)
{
    char p[] = "Mizzou";
    p[3] = 'P';
    printf("%s",p);
    fflush(stdout);
    return 0;
}
