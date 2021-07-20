#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX_INPUT 500
#define NUM_VAR 6
#define MAX_FUN 15
#define FOREVER 1
#define TRUE 1
#define FALSE 0

typedef struct complex /*data structures that holds complex number*/
{
	float real; /*represent the real part of the complex number*/
	float img;  /*represent the image part of the complex number*/
} complex;

typedef struct func /*data structures that holds function*/
{
	int which_func; /*decide which function to run*/
	char var[2] ; /*2 variables or less ('A','B'...'F')*/
	float num[2]; /*2 float numbers or less*/
	char *err_buf;
	int which_error;  /*decide which error occurs*/
} function;

/*deceleration of all the program functions*/
void read_comp (complex *, float, float);
void print_comp (complex);
void add_comp (complex, complex);
void sub_comp (complex , complex);
void mult_comp_real (complex , float);
void mult_comp_img (complex , float);
void mult_comp_comp (complex , complex);
void abs_comp (complex);
void error(int err);
void analyze_input(char input[], function **func);
function *parsing_variables(char* input, int index ,int num_comp, int num_args);

enum which_error{
    correct,
    invalid_number,
    missing_parameter,
    text_overflow,
    multiple_commas,
    missing_comma,
    illegal_comma,
    undefined_command,
    undefined_variable ,
    no_input};
enum which_func {read, print , add , sub , mult_real , mult_img, mult_comp, abs_f ,stop, no_function};