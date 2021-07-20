#include "complex.h"
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#define EMPTY SCHAR_MIN
#define EMPTY_NUM 1

/*determine which function has  been  inserted and determine which kind of variable(complex number
 * /numbers the function needs*/
int which_func(const char *func, int *number_of_comp , int* number_of_args)
{
	int which_function = no_function; /*initialize the variable to "no_function"*/

	if(!strcmp(func, "read_comp"))
    {
        which_function = read;
        *number_of_comp = 1;
        *number_of_args = 2;
    }
	else if(!strcmp(func, "print_comp"))
    {
        which_function = print;
        *number_of_comp = 1;
    }
    else if(!strcmp(func, "add_comp"))
    {
        which_function = add;
        *number_of_comp = 2;
    }
    else if(!strcmp(func, "sub_comp"))
    {
        which_function = sub;
        *number_of_comp = 2;
    }
    else if(!strcmp(func, "mult_comp_real"))
    {
        which_function = mult_real;
        *number_of_comp = 1;
        *number_of_args = 1;
    }
    else if(!strcmp(func, "mult_comp_img"))
    {
        which_function = mult_img;
        *number_of_comp = 1;
        *number_of_args = 1;
    }
    else if(!strcmp(func, "mult_comp_comp"))
    {
        which_function = mult_comp;
        *number_of_comp = 2;
    }
    else if(!strcmp(func, "abs_comp"))
    {
        which_function = abs_f;
        *number_of_comp = 1;
	}
	else if(!strcmp(func, "stop"))
        which_function = stop;
	else if(func[0] == '\0')
        which_function = EMPTY;

	return which_function;
}

/*check if the variable is valid ,empty ,or a comma */
int valid_var(char var, function **func , int *err){
    int valid = FALSE;

    *err = TRUE;
    if(var>=0 && var<6)
    {
        valid =  TRUE;
        *err = FALSE;
    }
    else
    if (var == ',')
        (*(*func)).which_error = illegal_comma; /* illegal comma*/
    else if (var == EMPTY)
        (*(*func)).which_error = missing_parameter;
    else
        (*(*func)).which_error = undefined_variable; /* undefined variable*/
    return valid;
}

/*get complex variable, if is empty returns EMPTY*/
char get_var(char *input)
{
	char variable;
	int i = 0;
	while(isspace(input[(i)]))
	{
		if(input[i] == '\n')
			variable = EMPTY;
		(i)++;
	}	
	if(variable!=EMPTY && input[i] == '\0')
		variable = ',';
	else if(isalpha(input[i]))
	{
		variable = input[i] -'A';
	}
	return variable ;
}


/*check if the string is a valid number, and empty number*/	
int valid_num(const char *str , int *err ,function **func)
{
	int flag = FALSE;
	int number = FALSE;
	int i = 0;
	char extra = '\0';

	while(isspace(str[i]))
		i++;
	if(str[i] == '-' || str[i] == '+')
		i++;
	while((str[i] == '.' && !flag) || isdigit((int)str[i]) )
	{
		number =TRUE;
		if(str[i] == '.')
			flag = TRUE;
		i++;
	}
	extra = str[i];	
	if(!isspace(extra) && extra !='\0')
	{
		*err = TRUE;
        (*(*func)).which_error = invalid_number;
		return FALSE;
	}
	return number + EMPTY_NUM;
}

/*check if number parameter isempty*/
void not_empty (int param , function **func , int *err)
{
	if (param == EMPTY_NUM)
	{
        (*func)->which_error = missing_parameter;
		*err = TRUE;
	}
	return;
}

/* check  there is extra text after the command*/
int extra_text(int error ,const char *str , int num_comma , function **func ,const char *mark)
{
	int flag = FALSE;
	int i =0;
	
	if(error)
		flag =TRUE;
	if(mark && !flag)
	{
		flag = TRUE;
	
        (*(*func)).which_error = text_overflow;
	}
			
	if(str && !flag)
	{
			if(num_comma != 0 )
			{
				flag = TRUE;
                (*(*func)).which_error = illegal_comma; /*illegal comma*/
			}
			else
			    {
				while(isspace(str[i]) && str[i] != '\0')
					i++;	
				while(!isspace(str[i]) && str[i] != '\0')
					i++;
				while(isspace(str[i]) && str[i] != '\0')
					i++;	
				if(str[i] != '\0' && str[i] != ' ' )
				{
                    (*(*func)).which_error =text_overflow; /*extra text*/
					flag =  TRUE;	
				}
			}
	}
	return flag;
}

/*check if between 2 variables there is a exactly 1 comma*/
int check_commas(const char* str , int num_comp, int num_args, function** func)
{
	int i = 0;
	int flag = FALSE;
	if(num_args+num_comp != 0)
	{
		while(isspace(str[i]))
			i++;
		if(str[i] =='\0')
		{
            (*(*func)).which_error = multiple_commas;
			flag = TRUE;
		}
		else
		{
			while(!isspace(str[i]) && str[i] !='\0')
				i++;
			while(isspace(str[i]))
				i++;
			if(str[i] !='\0')
		    {
                (*(*func)).which_error = missing_comma;
				flag =  TRUE;
				i++;
		    }
			i++;
			while(isspace(str[i]) && !flag)
				i++;
			if(str[i] == ',')
			{
				flag = TRUE;
                (*(*func)).which_error = multiple_commas;
			}
		}
	}	
	return flag;
	}
		
/*check errors for missing parameters*/
int check_param(int err, int left_param ,function** func){
	int flag = FALSE;
	
	if(err)	
		flag = TRUE;
	else				
		if(left_param != 0)
		{
			flag = TRUE;
            (*(*func)).which_error = missing_parameter;	/* missing parameters*/
		}
	return flag;				
}

/*parsing the input after getting the function*/
function * parsing_variables (char* input, int index ,int number_of_comp, int number_of_args)
{
	int num_of_commas = number_of_comp + number_of_args , i = 0 , flag_err = FALSE; 	 /*expected number of commas +1*/
	char comma[] = ",", *mark;
	function func , *pfunc = &func;

	if(!num_of_commas) 	/*stop cammand*/
		 flag_err = extra_text(flag_err, input, num_of_commas ,&pfunc,NULL);
    else
    {
        (*pfunc).err_buf = mark = strtok((input+index),comma);
		while(number_of_comp && mark && !flag_err)
		{
            (*pfunc).err_buf = mark;
            (*pfunc).var[i] =  get_var(mark);
			if(valid_var((*pfunc).var[i++] ,&pfunc , &flag_err ))
			{
				number_of_comp--;
				flag_err = check_commas(mark,number_of_comp,number_of_args,&pfunc);
				mark = strtok(NULL, comma);
				num_of_commas--;
			}
		}
		i=0;
		while(number_of_args && mark && !flag_err)
		{
			int parameter;
            (*pfunc).err_buf = mark;
			if((parameter = valid_num(mark , &flag_err ,&pfunc )))
			{
                (*pfunc).num[i++] =  atof(mark);
				number_of_args --;
				flag_err = check_commas(mark,number_of_comp,number_of_args,&pfunc);
				mark = strtok(NULL, comma);
				num_of_commas--;
			}
			not_empty (parameter ,&pfunc , &flag_err);
		}
		flag_err = check_param(flag_err, number_of_comp + number_of_args ,&pfunc);
		flag_err = extra_text(flag_err, pfunc->err_buf,num_of_commas,&pfunc,mark);
	}
	if(!flag_err)
	{
        (*pfunc).err_buf = NULL;
        (*pfunc).which_error = correct;
	}
	return pfunc;
}
/*parsing the input line by parameters*/
void analyze_input(char input[], function **func){
    int i = 0, j=0, func_type;
    char function[MAX_FUN]={0}; /*An array for save the characters of the function*/
    int number_of_comp =0 ,number_of_args = 0;
    int comma = FALSE;

    while(isspace(input[i])) /*checks whether a character is a white-space character or not*/
        i++;
    while(!isspace(input[i]) && j < MAX_FUN)
    {
        if(input[i] == ',')
            comma =TRUE;     /*there is a comma after cammand name*/
        function[j++] = input[i++]; /*fills the array char by char*/
    }
    switch(func_type = which_func(function, &number_of_comp, &number_of_args )) {
        case no_function:
        {
            if (comma)
                (*(*func)).which_error = illegal_comma;
            else
                (*(*func)).which_error = undefined_command;
            break;
        }
        case stop:
        {
            *func = parsing_variables(input, i , number_of_comp, number_of_comp);
            if((*(*func)).err_buf)
                (*(*func)).which_error = text_overflow;
            break;
        }
        case EMPTY :
            (*(*func)).which_error = no_input;
            break;
        default:
            *func = parsing_variables (input, i , number_of_comp, number_of_args); /*after we know which func requested
                                                                      we need to parsing the variables*/
    }
    (*(*func)).which_func = func_type;
    return;
}
