/**
 *
 * initials.c
 * 
 * J. Bobula
 * contact@exit32studio.com
 *
 * Takes input from the user and returns the first initial of each word
 */
 
 #include <stdio.h>
 #include <cs50.h>
 #include <string.h>
 
 int main (void)
 {
    //Ask user for their name
    //Take input and return the users initials
    printf("What is your name? ");
    char* name = GetString();
    printf("name is %i chars long\n", strlen(name));
 }
