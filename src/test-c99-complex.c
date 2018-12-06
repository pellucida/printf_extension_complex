# include	<complex.h>
# include	<stdio.h>

main() {

	complex	dz			= 1.234502843923442473297429E45 + 5.43212324324243034*I;
	float	complex	fz		= 8888 + 7777*I;
	long double	complex	lz	= .0001 + .0009*I;
	printf ("   [double] complex %-12.6K\n", dz);
	printf ("   [double] complex %-12.6k\n", dz);
	printf ("      float complex %#+9.6hK\n", fz);
	printf ("      float complex %#+9.6hk\n", fz);
	printf ("long double complex %9.6LK\n", lz);
	printf ("long double complex %9.6Lk\n", lz);
}
