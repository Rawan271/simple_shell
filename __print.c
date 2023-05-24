#include "shell.h"
/**
 * print_number -Print Unsigned Int Putchar
 * @n: Unisigned Integer
 * Return: Void
 */
void print_number(unsigned int n)
{
	unsigned int xx = n;

	if ((xx / 10) > 0)
		print_number(xx / 10);

	_putchar(xx % 10 + '0');
}
/**
 * print_number_in -Print Number Putchar
 * @n:Integer
 * Return: void
 */
void print_number_in(int n)
{
	unsigned int xx = n;

	if (n < 0)
	{
		_putchar('-');
		xx = -xx;
	}
	if ((xx / 10) > 0)
		print_number(xx / 10);

	_putchar(xx % 10 + '0');
}
