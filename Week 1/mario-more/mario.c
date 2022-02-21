#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    while (height < 1 || height > 8)
    {
        height = get_int("How high? :");
    }

   const int gap = 2;
    //set row
   for (int i=1; i<=height;i++)
   {
       int j = 1;
       // set column
       while (j<=height*2+gap)
       {
           // conditionals for first triangle
           if (j<=height)
           {
               // where to place a space
               if (j<=(height-i))
               {
                   printf(" ");
               }
               else
               {
                   printf("#");
               }
           }
           // conditional for gap
           else if (j<=height+gap)
           {
               printf(" ");
           }
           // condition for second triangle
           else
           {
               // conditional for placing #
               if (j<=height+gap+i)
               {
                   printf("#");
               }
               else
               {
                   break;
               }
           }
           j++;
       }
        printf("\n");
   }
}