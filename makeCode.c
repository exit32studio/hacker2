/**
 *
 * makeCode.c
 * 
 * J. Bobula
 * contact@exit32studio.com
 *
 * This takes user input and creates a DES encrypted word.
 *
 * Used for testing crack.c - brute force crack program.
 *
 */
 
#define _XOPEN_SOURCE
#include <cs50.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
    //Only proceed if the correct number of arguments was received
    if (argc != 2)
    {
        printf("Incorrect number of arguments");
        return 1;
    }
    else
    {
        char *salt = "50";
        char *word = argv[1];
        char *cryptResult = crypt(word, salt);
        printf("%s\n", cryptResult);
        return 0;
    }
    
}


