#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // validate key
    // check number of arguments
    if (argc < 2 || argc > 2)
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    // check length
    int length = strlen(argv[1]);
    int range = 26;
    if (length < range || length > range)
    {
        printf("too small\n");
        return 1;
    }

    // check for non alphabetic and repeated characters
    for (int i=0;i<length;i++)
    {
        char letter = argv[1][i];
        if ((letter < 65 || letter > 90) && (letter < 97 || letter > 122))
        {
            printf("not a letter\n");
            return 1;
        }
        else
        {
            for (int j=i+1; j<length;j++)
            {
                if (tolower(argv[1][i]) == tolower(argv[1][j]) && argv[1][i] != 32)
                {
                    printf("repeated character\n");
                    return 1;
                }
            }
        }
    }

    // take word to change
    string word = get_string("plaintext: ");

    // change word
    for (int i=0;i<strlen(word);i++)
    {
        if (isupper(word[i]))
        {
            word[i] = toupper(argv[1][word[i] - 'A']);
        }
        else if (islower(word[i]))
        {
            word[i] = tolower(argv[1][word[i] - 'a']);
        }
    }
    printf("ciphertext: %s\n", word);

    return 0;
}