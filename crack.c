/**
 *
 * crack.c
 * 
 * J. Bobula
 * contact@exit32studio.com
 *
 * Takes an encrypted password from the command line and tries to crack the key
 *
 * The program will try to match the password against a dictionary of predetermined words
 * prior to attempting a brute force attack.
 */

#define _XOPEN_SOURCE
#include <cs50.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 4
#define MIN_ASCII_CHARACTER 48
#define MAX_ASCII_CHARACTER 122
#define MAX_WORD_LENGTH 128

//Global variables are generally gross, however it makes sense to use one here.
const char *DICTIONARY_PATH = "/usr/share/dict/words";

//Make an array of possible characters (faster than ASCII because it doesn't have extra characters)
//const char *CHAR_ARRAY = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
const char *CHAR_ARRAY = "abcdefghijklmnopqrstuvwxyz";

/**
 * Runs through a predetermined dictionary of words and tries to brute force through the encryption
 */
bool dictionaryAttack(char *password, char *salt);

/**
 * Tries a true brute force attack using recursion
 */
bool bruteForce(char *password, char *salt, char *testWord, int position, bool *success);

/**
 * Runs "testWord" through the crypt function, using "salt".  Then compares to the password we're trying to crack
 */
bool tryPassword(char *password, char *salt, char *testWord);

int main (int argc, char *argv[])
{
    //Only proceed if 2 arguments are received
    if (argc != 2)
    {
        printf ("Incorrect number of arguments\n");
        return 1;
    }
    else
    {
        //First pull the salt out of the cipher text
        char *salt = malloc(3 * sizeof(char));
        strncpy(salt,argv[1],2);
        salt[2] = '\0';
        
        //Attempt to use a dictionary of common words to find the keys
        if (dictionaryAttack(argv[1], salt))
        {
            printf("Dictionary attack success\n");
        }
        else
        {
            printf("Dictionary attack failed\n");
            printf("Attempting brute force attack (may take a long time)...\n");
            
            //Start off with all null termination characters
            char *testWord = malloc((MAX_PASSWORD_LENGTH + 1) * sizeof(char));
            for (int i = 0; i <= MAX_PASSWORD_LENGTH; i++)
            {
                testWord[i] = '\0';
            }
            
            //Try brute force starting at the most signifigant character
            int position = MAX_PASSWORD_LENGTH - 1;
            //Create a bool for testing success (default to fail)
            bool success = false;
            success = bruteForce(argv[1], salt, testWord, position, &success);
            if (!success)
            {
                printf("Brute force failed\n");
            }
            free(testWord);
        }
        
    }
}

/**
 * Runs through a predetermined dictionary of words and tries to brute force through the encryption
 */
bool dictionaryAttack(char *password, char *salt)
{
    //Prepare a connection to the dictionary
    FILE *dict;
    dict = fopen(DICTIONARY_PATH,"r");
    
    if (!dict)
    {
        printf("Could not open dictionary file!\n");
        return false;
    }
    else
    {
        char currentWord[MAX_WORD_LENGTH];
        //Loop through the dictionary, trying every word against the password
        while (fgets(currentWord, MAX_WORD_LENGTH, dict))
        {
            //Swap out the last character in the current word for "/0"
            currentWord[strlen(currentWord) - 1] = '\0';
            
            //Try the current word
            if (tryPassword(password, salt, currentWord))
            {
                //Break from the current loop when the word is found
                return true;
            }
        }
        //If the loop ends without finding a match for the password, then return false
        return false;
    }
}


/**
 * Tries a true brute force attack
 */
bool bruteForce(char *password, char *salt, char *testWord, int position, bool *success)
{
    int length = strlen(CHAR_ARRAY);
    //Only run the loop while success is false
    for (int j = 0; !*success && j < length; j++)
    {        
        if (position > 0)
        {
            int deeperPosition = position - 1;
            *success = bruteForce(password, salt, testWord, deeperPosition, success);
        }
        
        //Check if successful coming out of recursion
        //Only step in if not successful
        if (*success)
        {
            break;
        }
        testWord[position] = CHAR_ARRAY[j];
        *success = tryPassword(password, salt, testWord);
    }
    return *success;
}

/**
 * Runs "testWord" through the crypt function, using "salt".  Then compares to the password we're trying to crack
 */
bool tryPassword(char *password, char *salt, char *testWord)
{
    //use crypt on the test word.  If the result matches the password, then we figured it out
    char *cryptResult = crypt(testWord, salt);
    
    if (!strcmp(cryptResult, password))
    {
        printf("Success - password is %s\n", testWord);
        return true;
    }
    else
    {
        return false;
    }  
}

