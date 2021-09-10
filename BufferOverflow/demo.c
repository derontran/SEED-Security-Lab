#include <stdio.h>
#include <string.h>

int main()
{

    char buffer[20];
    char shell[] = {
        'A',
        'b', 'c', 'd', 'e','f','g','h','\0'};
    char ret[] = "\xbf\xff\xeb\x60";
    memset(buffer, 'a', sizeof(buffer));
    int start = sizeof(buffer)- sizeof(shell); 
    memcpy(&buffer[5], shell, sizeof(shell));
    // printf("%s %d %d %d", buffer, sizeof(buffer), sizeof(shell),start);
    printf("%x", buffer+75);
    return 1;
}