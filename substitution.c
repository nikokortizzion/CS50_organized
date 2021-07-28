#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    // Check if key are given
    if (argc == 2 && strlen(argv[1]) == 26)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                // Stop with error if key has not only letters
                printf("Key must consit of letters only!\n");
                return 1;
            }
        }

        // Check if key not containing each letter exactly once
        int count = 0;
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            for (int k = i; k < n; k++)
            {
                if (argv[1][i] == argv[1][k])
                {
                    count += 1;
                }
            }
            if (count > 1)
            {
                printf("Key must consist of unique elements!\n");
                return 1;
            }
            else
            {
                count = 0;
            }
        }

        // Get text to cipher
        string plain_text = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0, n = strlen(plain_text); i < n; i++)
        {
            // Using position of letter in key and ABCs for substitution
            if (plain_text[i] >= 'A' && plain_text[i] <= 'Z')
            {
                int index = (int)plain_text[i];
                char letter = argv[1][index - 65];
                // Switch case of letter if needed
                printf("%c", toupper(letter));
            }

            else if (plain_text[i] >= 'a' && plain_text[i] <= 'z')
            {
                int index = (int)plain_text[i];
                // Switch case of letter if needed
                printf("%c", tolower(argv[1][index - 97]));
            }

            else
            {
                printf("%c", plain_text[i]);
            }
        }
        printf("\n");
        return 0;
    }

    else if (argc == 2 && strlen(argv[1]) < 26)
    {
        // When key too short
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else
    {
        // When key not given or get too many arguments
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
