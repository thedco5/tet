#include <stdio.h>
#include <string.h>
#include "tetlib.h"

void start();   // starts the interpreter's console
void help();    // returns a list with all key words
void info();    // returns some information about the interpreter
void save();    // adds a new code location name
void clear();   // clears the list with code location names
void dlt();     // deletes a code location name
void dlt_cln(); // called only from delete();
void list();    // lists all code location names
void run();     // runs a code
void print();   // prints a code

void error(char error[]); // returns an error message but continues the program

int main()
{
    printf(" > === VERSION 1.0 === <\ntype 'help' etc.\n");
    start(); // only necessary line of code (for now?) in main
    return 0;
}

void start()
{
    char in[1024];
    printf(" >< ");
    scanf("%s", in); // reads the prompt and chooses a method
    if (strcmp(in, "end") == 0)
        goto end;
    else if (strcmp(in, "help") == 0)
        help();
    else if (strcmp(in, "info") == 0)
        info();
    else if (strcmp(in, "save") == 0)
        save();
    else if (strcmp(in, "clear") == 0)
        clear();
    else if (strcmp(in, "delete") == 0)
        dlt();
    else if (strcmp(in, "list") == 0)
        list();
    else if (strcmp(in, "cancel") == 0 || strcmp(in, "skip") == 0)
        goto end;
    else if (strcmp(in, "escape") == 0)
        start();
    else
        error("incorrect command");
end:
}
void error(char error[])
{
    printf("error :: %s !\n", error);
    start();
}
void help()
{
    printf("  end - closes interpreter\n");
    printf("  help - prints help menu\n");
    printf("  info - shows information panel\n");
    printf("  save - saves a code location\n");
    printf("  list - lists all code locations\n");
    printf("  clear - deletes all code locations\n");
    printf("  delete - delete a code location\n");
    printf("  cancel / skip - cancels current command\n");
    printf("  escape - escapes all commands till start\n");
    start();
}
void info()
{
    printf("  (i) current version - v. 1.0 DEMO\n");
    printf("   | property of Thedco (c) 2005 - 2022\n");
    printf("   | not to be distributed !\n");
    printf("   ' interpreter of the .tet language\n");
    start();
}
void save()
{
    FILE *address_file;
    address_file = fopen("address_file.txt", "a");
    printf("   >[name] [address]< ");
    char code_name[1024], code_address[1024];
    scanf("%s", code_name);
    if (strcmp(code_name, "end") == 0)
        goto end;
    else if (strcmp(code_name, "cancel") == 0 || strcmp(code_name, "skip") == 0)
        start();
    else if (strcmp(code_name, "escape") == 0)
        start();
    else {
        scanf("%s", code_address);
        if (strcmp(code_address, "end") == 0)
            goto end;
        else if (strcmp(code_address, "cancel") == 0 || strcmp(code_address, "skip") == 0)
            start();
        else if (strcmp(code_address, "escape") == 0)
            start();
        else {
            fprintf(address_file, "%s %s\n", code_name, code_address);
            start();
        }
    }
    
end:
}
void clear()
{
    FILE *address_file;
    address_file = fopen("address_file.txt", "w");
    fclose(address_file);
    start();
}
void dlt()
{
    printf("   >[name]< ");
    char code_name[1024];
    scanf("%s", code_name);
    if (strcmp(code_name, "end") == 0)
        goto end;
    else if (strcmp(code_name, "cancel") == 0 || strcmp(code_name, "skip") == 0)
        start();
    else if (strcmp(code_name, "escape") == 0)
        start();
    else
    {
        printf("     >[Y/n]< sure? ");
        char in[1024];
        scanf("%s", in);
        if (strcmp(in, "Y") == 0)
            dlt_cln(code_name);
        else if (strcmp(in, "n") == 0)
            start();
        else if (strcmp(in, "end") == 0)
            goto end;
        else if (strcmp(in, "cancel") == 0 || strcmp(in, "skip") == 0)
            dlt();
        else if (strcmp(in, "escape") == 0)
            start();
        else
            error("incorrect answer");
    }
end:
}
void dlt_cln(char name[])
{
    FILE *stream, *file;
    stream = fopen("stream", "w");
    fprintf(stream, "%s", fconvstr("address_file.txt"));
    fclose(stream);
    stream = fopen("stream", "r");
    int count;
    fscanf(stream, "%d", &count);
    char new[1024], first[1024], second[1024];
    strcpy(new, "");
    for(int i = 0; i < count / 2; i++) {
        fscanf(stream, "%s %s", first, second);
        if(strcmp(first, name) != 0) {
            strcat(first, " ");                                     
            strcat(new, first);
            strcat(second, "\n");
            strcat(new, second);
        }
    }
    file = fopen("address_file.txt", "w");
    fprintf(file, "%s", new);
    fclose(file);
    fclose(stream);
    stream = fopen("stream", "w");
    fclose(stream);
    start();
}
void list()
{
    char files[1024], first[1024], second[1024];
    FILE *stream = fopen("stream", "w");
    fprintf(stream, "%s", fconvstr("address_file.txt"));
    fclose(stream);
    stream = fopen("stream", "r");
    int number;
    fscanf(stream, "%d", &number);
    number /= 2;
    if (number <= 0) 
        printf("  there are no files ! \n");
    else if (number == 1)
        printf("  there is 1 file: \n");
    else 
        printf("  there are %d files: \n", number);
    for(int i = 0; i < number; i++) {
        fscanf(stream, "%s %s", first, second);
        printf("   - \'%s\' at %s\n", first, second);
    }
    fclose(stream);
    stream = fopen("stream", "w");
    fclose(stream);
    start();
}