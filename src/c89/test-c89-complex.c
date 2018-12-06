/*
//	test-c89-complex.c
*/

# include	<stdio.h>

/* C99 Complex types are apparently implemented in the obvious way
*/
typedef	struct	{
	double	x;
	double	y;
}	complex;

typedef	struct	{
	float	x;
	float	y;
}	float_complex;

typedef	struct	{
	long	double	x;
	long	double	y;
}	long_complex;
	
main() {
	complex		dz	=  { 1.234502843923442473297429E45, 5.43212324324243034 };
	float_complex	fz	=  { 8888, 7777 };
	long_complex	lz	=  { .0001, .0009 };

	printf ("   [double] complex %-12.6K\n", dz);
	printf ("   [double] complex %-12.6k\n", dz);
	printf ("      float complex %#+9.6hK\n", fz);
	printf ("      float complex %#+9.6hk\n", fz);
	printf ("long double complex %9.6LK\n", lz);
	printf ("long double complex %9.6Lk\n", lz);
}
