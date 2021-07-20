#include "complex.h"
#include <stdlib.h>

void free_complex(complex ***arr);

/*print the error*/
void error(int err)
{
	switch(err)
	{
        case invalid_number:
            printf("\nInvalid parameter - not a number\n");
            break;
        case missing_parameter:
            printf("\nMissing parameter\n");
            break;
        case text_overflow:
            printf("\nExtraneous text after end of command\n");
            break;
        case multiple_commas:
            printf("\nMultiple consecutive commas\n");
            break;
        case missing_comma:
            printf("\nMissing comma\n");
            break;
        case illegal_comma:
            printf("\nIllegal comma\n");
            break;
        case undefined_command:
		    printf("\nUndefined command name\n");
		    break;
	    case undefined_variable:
		    printf("\nUndefined complex variable\n");
		    break;
	    case no_input:
		    printf("\ninsert command please\n");
		    break;
	    default:;
	}
}
/*executing the right function*/
void exe(function *func, complex **arr)
{
	int var1 = (int)(*func).var[0];
	int var2 = (int)(*func).var[1];
	
	switch((*func).which_func)
	{
	    case read:
            read_comp ((arr[var1]) ,  func->num[0],  func->num[1]);
            break;
        case print:
            print_comp(*arr[var1]);
            break;
        case add:
            add_comp (*arr[var1], *arr[var2]);
            break;
        case sub:
            sub_comp (*arr[var1] , *arr[var2]);
            break;
        case mult_real:
            mult_comp_real (*arr[var1], (*func).num[0]);
            break;
        case mult_img :
            mult_comp_img (*arr[var1],  (*func).num[0]);
            break;
        case mult_comp:
            mult_comp_comp (*arr[var1] , *arr[var2]);
            break;
        case abs_f:
            abs_comp (*arr[var1]);
            break;
	    case stop:
	    {
		    free_complex(&arr);
		    exit(0);
		}
	    default:;
	}
}
void initiate(complex ***arr) /*initializing the array of variables to value with 0*/
{
	int flag = FALSE;
	int i;
	*arr = (complex**)malloc(NUM_VAR*sizeof(complex*));
	if(*arr == NULL)
		flag = TRUE;
		
	for(i=0; i< NUM_VAR &&(!flag); i++) /*loop for all the 6 variables*/
	{
		(*arr)[i] = (complex*)malloc(sizeof(complex));
		if((*arr)[i] == NULL)
			flag = TRUE;
		else
		    read_comp((*arr)[i],0,0);
	}
	if(flag)
	{
		printf("allocation failed");
		free_complex(arr);
		exit(0);
	}
	return;

}

void clean_input(char* input)
{
    int i;
    for (i=0; i < strlen(input) ; i++)
        input[i] = '\0';
    return;
}
void free_complex(complex ***arr)
{
	int i;

	for(i=0; i< NUM_VAR; i++)
		free((*arr)[i]);
	free(*arr);
	return;
}
int main()
{
	char input[MAX_INPUT]; /*max of input - 50 chars*/
	complex **arr; /*pointer to pointer that representing 6 variables of complex (A,B,C,D,E,F)*/
	function f1;
	function *func = &f1;
	printf("\nHello! please insert commands, if you want to to exit from the "
        "program you can insert the word \"stop\" \n");
	initiate(&arr); /*initiate the complex number to 0+0i*/
	while(FOREVER) /*until the user insert the word "stop"*/
        {
	    printf(">> ");
		fgets(input,MAX_INPUT,stdin); /*getting input, max size og input - 500*/
		printf("%s", input);
		analyze_input(input,&func);
				
		if((*func).which_error)
			error((*func).which_error);
		else
			exe(func, arr);
		clean_input(input);
	}
return 0;
}
