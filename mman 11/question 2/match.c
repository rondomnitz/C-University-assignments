#include <stdio.h>
#include <string.h>
#include <limits.h>
# define MAX_PATTERN 20 /*max length for input of pattern*/
# define MAX_TXT 50  /*max length for input of text*/

int match(char*, char*); /*mention for the main function to recognize this function*/

int main()
{
   char txt[MAX_TXT];
   char pattern[MAX_PATTERN];
   int position=0;
   printf("\n Please Enter any String-Pattern: \n"); 
   fgets(pattern,MAX_PATTERN, stdin); /*input method*/
   printf("\n Please Enter any Text: \n");
   fgets(txt,MAX_TXT, stdin); /*input method*/
   printf("\n Your String-Pattern is %s and your text is %s\n",pattern,txt);
   position=match(pattern,txt);
   printf("\n The Best position for the string and the text is %d\n",position);
     
return 0;
}
int match(char* pattern, char* txt)
{
/* This function get 2 parmeters (pattern and text), and return integer number that represent the best position of the discrepancy in the text.*/
   int i,j;
   int discrepancy =0;
   int indx_min_position;
   int min_position = INT_MAX;
   if((strlen(txt))<(strlen(pattern))) /*if the pattern longest then the txt*/
	return -1;
   else for(i =0; i<= strlen(txt) - strlen(pattern); i++)
   {
      int k;
      discrepancy=0;
      for(j=0, k=i; pattern[j]; j++, k++)   
      { 
         if(pattern[j]!=txt[k])
             discrepancy++; /*counter for the discrepancy*/
      }
      if(discrepancy<min_position) /*for saving the best(min) discrepancy in a variable*/
      {
	min_position=discrepancy;
        indx_min_position=i;  /*for saving the best(min) index of discrepancy in a variable*/     
      }
   }
return indx_min_position;
}
