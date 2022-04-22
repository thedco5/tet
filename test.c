#include <stdio.h>
#include "tetlib.h"

int main()
{   
    FILE *stream = fopen("stream", "w");
    fprintf(stream, "%s", fconvstr("address_file.txt"));
    fclose(stream);
    stream = fopen("stream", "r");
    int number;
    fscanf(stream, "%d", &number);
    //char number[1024];
    //fscanf(stream, "%s", number);
    /*if (number <= 0) 
        printf("  there are no files ! \n");
    else if (number == 1)
        printf("  there is 1 file: \n");
    else 
        printf("  there is/are %d file(s): \n", number);
    char first[1024], second[1024];
    for(int i = 0; i < number / 2; i++) {
        fscanf(stream, "%s %s", first, second);
        printf("   - \'%s\' at %s\n", first, second);
    }*/
    fclose(stream);
    return 0;
}