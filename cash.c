#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    //Get flout number
    float change = 0;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    // Convert to cents
    int cents = round(change * 100);
    int coins = 0;
    while (cents > 0)
    {
        /** Divide cents by 25, 10, 5, 1 to get number of coins
         and save remainder
        **/
        if (cents >= 25) // Number of quarters coins
        {
            coins += cents / 25;
            cents %= 25;
            continue;
        }
        else if (cents >= 10) // number of dimes coins
        {
            coins += cents / 10;
            cents %= 10;
            continue;
        }
        else if (cents >= 5) // number of nickels coins
        {
            coins += cents / 5;
            cents %= 5;
            continue;
        }
        else if (cents >= 1) // number of pennies coins
        {
            coins += cents;
            cents = 0;
            continue;
        }
    }
    printf("%i\n", coins);
}
