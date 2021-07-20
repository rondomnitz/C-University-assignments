#include "complex.h"
/*"read_comp" is a function that make a placing of complex number in a variable*/
void read_comp (complex *num, float real, float img)
{ 
    (*num).real = real;
    (*num).img = img;
}
/*"print_comp" is a function print a complex number*/
void print_comp (complex num)
{
	printf("%.2f + (%.2f)i\n", num.real,num.img); /*print with 2 decimal points: x.xx + (x.xx)i*/
	printf("\n");
}
/*"add_comp" is a function that get 2 complex numbers num1, num2 and return the value of both of num1+num2 */
void add_comp (complex num1, complex num2)
{
	complex result;
	float real, img;
	
	real = num1.real + num2.real;
	img = num1.img + num2.img;
	
	read_comp(&result , real, img);
	print_comp(result);
}
/*"sub_comp" is a function that get 2 complex numbers num1, num2, return the value of num1-num2 */
void sub_comp (complex num1, complex num2)
{
	complex result;
	float real, img;
	
	real = num1.real - num2.real;
	img = num1.img - num2.img;
	
	read_comp(&result , real, img);
	print_comp(result);
}
/*"mult_comp_real" is a function that get complex number cmp,
 * and real number "real" return the value of cmp * real*/
void mult_comp_real (complex num, float mul)
{
	complex result;
	float real, img;
	
	real = num.real * mul;
	img = num.img * mul;
	
	read_comp(&result , real, img);
	print_comp(result);
}
/*"mult_comp_img" is a function that get complex number cmp, and real number "img" that represent
 * the number img*i return the value of cmp * img * i */
void mult_comp_img (complex num, float mul)
{
	complex result;
	float real, img;
	
	img = num.real * mul;
	real = num.img * (-mul);
	
	read_comp(&result , real, img);
	print_comp(result);
} 
	
		
/*"mult_comp_comp" is a function that get 2 complex numbers var1, var2, return the value of num1*num2 */
void mult_comp_comp(complex num1, complex num2)
{
	complex result;
	float real, img;
	
	real = num1.real * num2.real - (num1.img * num2.img); /*ac -bd)*/
	img = num1.real * num2.img + ( num1.img * num2.real);
	
	read_comp(&result , real, img);
	print_comp(result);
} 
	
/*Given a complex number num return the value of |num| */
void abs_comp (complex num)
{
	float result;
	result = sqrt(pow(num.real, 2) + pow(num.img , 2));
	printf("%.2f\n", result);
}