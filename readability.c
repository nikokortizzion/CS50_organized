#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float c_h_index(string text);

int main(void)
{
    string text;
    text = get_string("Text: ");
    float indx = c_h_index(text);
    if (indx < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (indx > 16.0)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", indx);
    }
}

int count_letters(string text)
// Count only letters from text
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha((int)text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
// Count words separated by spaces
{
    int count = 0;
    if (strlen(text) < 1)
    {
        return count;
    }
    else
    {
        count++;
    }
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
// Count sentences separated by '.', '?', '!'
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    if (count == 0 && strlen(text) > 1)
    {
        return 1;
    }
    return count;
}

float c_h_index(string text)
/** Return Coleman-Liau index.
 * The formula is:
 * index = 0.0588 * L - 0.296 * S - 15.8
 * L is the average number of letters per 100 words in the text
 * S is the average number of sentences per 100 words in the text.
*/
{
    float letters = (float)count_letters(text);
    float words = (float)count_words(text);
    float sentences = (float)count_sentences(text);
    if (words != 0)
    {
        float indx = 0.0588 * (100 * letters / words) - 0.296 * (100 * sentences / words) - 15.8;
        return round(indx);
    }
    else
    {
        return 0;
    }
}
