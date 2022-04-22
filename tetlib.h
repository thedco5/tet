#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *conv_hex(char c);            // converts a character to its hexadecimal value
char rev_hex(char str[]);          // reverting a character from its hexadecimal value
char *read_file(char file_name[]); // returns a string full of everything in a file

char *conv_hex(char c)
{
    static char hex[] = "x00";
    int decimal = c + 128;
    int first = decimal % 16;
    decimal /= 16;
    int second = decimal % 16;
    switch (first)
    {
    case 10:
        hex[2] = 'A';
        break;
    case 11:
        hex[2] = 'B';
        break;
    case 12:
        hex[2] = 'C';
        break;
    case 13:
        hex[2] = 'D';
        break;
    case 14:
        hex[2] = 'E';
        break;
    case 15:
        hex[2] = 'F';
        break;
    default:
        hex[2] = '0' + first;
        break;
    }
    switch (second)
    {
    case 10:
        hex[1] = 'A';
        break;
    case 11:
        hex[1] = 'B';
        break;
    case 12:
        hex[1] = 'C';
        break;
    case 13:
        hex[1] = 'D';
        break;
    case 14:
        hex[1] = 'E';
        break;
    case 15:
        hex[1] = 'F';
        break;
    default:
        hex[1] = '0' + second;
        break;
    }
    return hex;
}
char rev_hex(char str[])
{
    int hex = -128;
    switch (str[2])
    {
    case 'A':
        hex += 10;
        break;
    case 'B':
        hex += 11;
        break;
    case 'C':
        hex += 12;
        break;
    case 'D':
        hex += 13;
        break;
    case 'E':
        hex += 14;
        break;
    case 'F':
        hex += 15;
        break;
    default:
        hex += str[2] - '0';
        break;
    }
    switch (str[1])
    {
    case 'A':
        hex += 10 * 16;
        break;
    case 'B':
        hex += 11 * 16;
        break;
    case 'C':
        hex += 12 * 16;
        break;
    case 'D':
        hex += 13 * 16;
        break;
    case 'E':
        hex += 14 * 16;
        break;
    case 'F':
        hex += 15 * 16;
        break;
    default:
        hex += (str[1] - '0') * 16;
        break;
    }
    return (char)hex;
}
char *fconvstr(char file_name[])
{
     // const
    FILE *file;
    file = fopen(file_name, "r"); // boolean reduvatschka!!!!
    int count = 0;
    while(feof(file) == false)
    {
        char c;
        fscanf(file, "%c", &c);
        if(c == ' ' || c == '\n')  {
            count += 1;
        }
    }
    fclose(file); 
    file = fopen(file_name, "r");
    count--;
    static char file_string[1024];
    sprintf(file_string, "%d ", count);
    for(int i = 0; i < count; i++) {
        char str[1024];
        fscanf(file, "%s", str);
        strcat(file_string, strcat(str, " "));
    }
    fclose(file);
    return file_string;
}