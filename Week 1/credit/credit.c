#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int checksum(long number, int length);
int isTrue(long number, int length, int target, char *company);
char validInvalid(int truth, char *company);

int main(void)
{
    // find number length
    long number = get_long("What is the card number?: ");
    int length = floor(log10(labs(number))) + 1;

    // check card validity
    // American Express
    if (length == 15)
    {
        char * company= "AMEX";
        if (
        isTrue(number, length, 34, company) ||
        isTrue(number, length, 37, company))
        {
            int truth = checksum(number, length);
            validInvalid(truth, company);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // Visa
    else if ((length == 13 || length == 16) && floor(number/((10*pow(10, length-2)))) == 4)
    {
        char * company= "VISA";
        if (isTrue(number, length, 4, company) )
        {
            int truth = checksum(number, length);
            validInvalid(truth, company);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // Mastercard
    else if (length == 16)
    {
        char * company= "MASTERCARD";
        if (
        isTrue(number, length, 51, company) ||
        isTrue(number, length, 52, company) ||
        isTrue(number, length, 53, company) ||
        isTrue(number, length, 54, company) ||
        isTrue(number, length, 55, company))
        {
            int truth = checksum(number, length);
            validInvalid(truth, company);
        }
        else
        {
            printf("%i\n", isTrue(number, length, 51, "MASTERCARD"));
            printf("INVALID\n");
        }
    }
    // invalid
    else
    {
        printf("Number: %li\n", number);
        printf("INVALID\n");
    }
}

int checksum(long number, int length)
{
    int total = 0;
    int digit;
    int not2 = 0;
    for (int i=1; i<=length; i++)
    {
        if (i%2 == 0)
        {
            // finding digits
            digit = number%10;
            number = number/10;
            // multiply digit by 2 then add to total
            int product = digit*2;
            int len = floor(log10(labs(product))) + 1;
            if (len == 1)
            {
                total += product;
            }
            else
            {
                for (int j=1; j<=len;j++)
                {
                    total += product % 10;
                    product = product/10;
                }
            }
        }
        else
        {
            // finding digits
            digit = number%10;
            number = number/10;
            // add up not multiplied by 2
            not2 += digit;
        }
    }
    return total + not2;
}

int isTrue(long number, int length, int target, char* company)
{
    if (strcmp(company, "VISA") != 0)
    {
        return floor(number/((10*pow(10, length-3))))==target;
    }
    else
    {
        return floor(number/((10*pow(10, length-2))))==target;
    }

}

char validInvalid(int truth, char* company)
{
    if (truth%10 == 0)
            {
                printf("%s\n", company);
            }
            else
            {
                printf("INVALID\n");
            }
    return 1;
}