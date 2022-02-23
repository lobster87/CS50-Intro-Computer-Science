#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // get string
    string stringIn = get_string("Text: ");

    float characters = 0;
    float sentences = 0;
    float spaces = 0;
    float words;

    // itterate through string to find characters, !.? and spaces
    for (int i=0; i<strlen(stringIn); i++)
    {
        char letter = stringIn[i];
        if ((letter >= 97 && letter <= 122) || (letter >= 65 && letter <= 90))
        {
            characters++;
        }
        else if (letter == 33 || letter == 46 || letter == 63)
        {
            sentences++;
        }
        else if (letter == 32)
        {
            spaces++;
        }
    }

    words = spaces + 1;

    // calculate L and S for Coleman-Liau index formula
    float L = (characters/words)*100;
    float S = (sentences/words)*100;

    // Coleman-Liau index formula
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}