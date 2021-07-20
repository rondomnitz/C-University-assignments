#include <stdio.h> 
#include <string.h>
# define MAX_STR 101 /*101 and not 100 because thr /n (ENTER) for the last char*/

void f_sequence(char*); /*mention for the main function to recognize this function*/

int main()
{
   char str[MAX_STR];
   printf("\nPlease Enter Any String:\n");
   scanf("%s", str);
   f_sequence(str);
	
   return 0;
}
void f_sequence(char* string)
{
/* This function calculate the String that get from the user by check if every charecter (ANSCII display) is bigger/small or same.
There are five option:
1. If every charecter is bigger than the previous one- THE STRING IS A STRICTLY ASCENDING SEQUENCE.
2.If every charecter is bigger than the previous one and there is same charecter - THE STRING IS A ASCENDING SEQUENCE.
4. If every charecter is the same  - THE STRING IS A ASCENDING SEQUENCE.
3.If every charecter is smaller than the previous one - THE STRING IS A STRICTLY DESCENDING SEQUENCE.
5. If there is no Fixed order - THE STRING IS WITHOUT CONSTANT SEQUENCE.
*/

int i;
int up, down, equal;
up = down = equal = 0;

for(i=1; string[i]; i++)
{
   if(string[i-1]<string[i])
      up++;	
   else if(string[i-1]>string[i])	     
      down++;
   else if (string[i-1]==string[i])
      equal++;	
}

if(up!=0 && equal==0 && down==0)
   printf("\nThe '%s' is a strictly ascending sequence\n", string);
else if((up!=0 && equal!=0 && down==0)||(up==0 && equal!=0 && down==0))
   printf("\nThe '%s' is a ascending sequence\n", string);
else if(up==0 && equal==0 && down!=0)	
   printf("\nthe '%s' is a strictly descending sequence\n", string);
else if(up==0 && equal!=0 && down!=0) 
   printf("\nThe '%s' is a descending sequence\n", string);
else if ((up!=0 && equal!=0 && down!=0)||(up!=0 && equal==0 && down!=0))
   printf("\nThe '%s' is without constant sequence\n", string);
else 
   printf("\nThe '%s' is a strictly ascending sequence\n", string); 

return;
}

