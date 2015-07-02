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
 
 
 /**
  * ASCII values for upper case and lower case letters
  */
 #define START_OF_UPPER_CASE    65
 #define START_OF_LOWER_CASE    97
 #define END_OF_LOWER_CASE      122
 
 
 /**
  * Function that does the work
  */
 void printInitials(char* name);
 
 int main (void)
 {
    //Ask user for their name
    //Take input and return the users initials
    char* name = GetString();
    
    //Print the first letter of each word
    printInitials(name);  
 }
 
 
 /**
  * Function uses recursion to loop through a passed string array
  * Recursion exits when the string is empty and prints a carriage return
  * Recursion increments the pointer to the beginning of the string as it moves deeper
  */
 void printInitials(char* name)
 {
    //If not at the end of the string, either print the first character or skip a space
    if (strlen(name))
    {
        if (name[0] == ' ')
        {
            name++;
        }
        else
        {
            //Print the first initial and then loop until a space is found
            //Convert lower case letters to upper case
            if ((name[0] >= START_OF_LOWER_CASE) && (name[0] <= END_OF_LOWER_CASE))
            {
                name[0] -= (START_OF_LOWER_CASE - START_OF_UPPER_CASE);
            }
            printf("%c",name[0]);
            while ((name[0] != ' ') &&(strlen(name)))
            {
                name++;
            }
        }
        //Use recursion to work through the string
        printInitials(name);
    }
    else
    {
        //done working through string
        printf("\n");
    }
 }
