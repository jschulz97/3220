 
#include<stdio.h>
#include<string.h>
int main(void)
{
    int i=0;
    char arr1[15] = "Trumantiger";
    char arr2[15];
    while(i<15){
        arr2[i] = 'A';
        ++i;
    }
    strcpy(arr1, arr2);
    printf("%s",arr1);
    return 0;
}
