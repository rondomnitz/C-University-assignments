#include <stdio.h>
#include <stdlib.h>
#define MAX_ARGS 3
#define SINGLE_ARGS 2

/* Function that get the number and convert it to a word */
void convert_numbers(int num, FILE *output)
{
    char *single_digits[] = {"", "one", "two", "three", "four","five", "six", "seven", "eight", "nine"};
    char *two_digits[] = {"ten", "eleven", "twelve", "thirteen", "fourteen","fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens_multiple[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    switch(num / 10)
    {
        case 0:
            break;
        case 1:
            fprintf(output, "%s\n", two_digits[num % 10]);
            return;
        default:
            fprintf(output, "%s ", tens_multiple[num / 10]);
    }
    fprintf(output, "%s\n", (num) ? single_digits[num % 10] : "zero");
}
/* Function that get the input according to what the user decided to choose:
 * 1. Input file and output file
 * 2. Only input file
 * 3. None of them
 */
int get_input(int argc, char *argv[])
{
    int number;
    FILE *input;
    FILE *output;
    if(argc==MAX_ARGS)
    {
        input=fopen(argv[1], "r");
        output=fopen(argv[2], "w");
    }
    else if(argc==SINGLE_ARGS)
    {
        input=fopen(argv[1], "r");
        output=stdout;
    }
    else
    {
        input=stdin;
        output=stdout;
    }
    if(!input||!output) /*if the files not open for some reason*/
    {
        fprintf(stderr, "ERROR - the file dose not exist or we can't open it. Please check again.\n");
        exit(0);
    }
    while(fscanf(input, "%d", &number) > 0)
              convert_numbers(number, output);
    return 0;
}
/* Function that prints given number in English words */
int main(int argc, char *argv[])
{
    if(argc > MAX_ARGS)
        printf("Too many arguments supplied. Pleas try again.\n");
    return get_input(argc, argv);
}
