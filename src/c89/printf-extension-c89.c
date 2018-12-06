/*
// @(#) printf-extension-complex.c
//
// Usage:  %K - for Komplex :)  zZ and cC are already used in some way,
//	eg	(1.000,2.000)	= 1.0 + 2.9*I
//
//	%<width>.<prec>K	- uses %g format  
//	%<width>.<prec>k 	- uses %f format
//
//	width	- total width for the number
//	prec	- significant digits of each number
//		eg (1.0,1.0) from %9.1K  
//
//	%LK	- long_double_complex
//	%hK	- float_complex
//	%K, or %lK 	- [double] complex
//	%-12.1K	- left adjust the whole (x,y)
//	%+K	- print sign eg (+1.0,+1.0)
//	
*/

# include	<stdio.h>
# include	<stdlib.h>
# include	<printf.h>
# include	<values.h>

typedef	struct	{
	double	x;
	double	y;
}	double_complex;

typedef	struct	{
	float	x;
	float	y;
}	float_complex;

typedef	struct	{
	long	double	x;
	long	double	y;
}	long_double_complex;
	
# define	creal(z)	(z).x
# define	cimag(z)	(z).y

/*
// Register_printf_type () will used the free slots >= PA_LAST and return it;
// We use this global to pass it to arginfo function: print_complex_arginfo 

// We register each type variant (is there a better way?)
*/
static	int	dcomplex_type	= -1; /* [double] complex */
static	int	fcomplex_type	= -1; /* float_complex */
static	int	lcomplex_type	= -1; /* long_double_complex */

/*
// Function for each variant to copy from va_list to mem
*/
static	void	lcomplex_va_arg_function (void* mem, va_list* ap) {
	long_double_complex	z	= va_arg(*ap, long_double_complex);
	*(long_double_complex*) mem	= z;
}
static	void	dcomplex_va_arg_function (void* mem, va_list* ap) {
	double_complex	z	= va_arg(*ap, double_complex);
	*(double_complex*) mem	= z;
}
static	void	fcomplex_va_arg_function (void* mem, va_list* ap) {
	float_complex	z	= va_arg(*ap, float_complex);
	*(float_complex*) mem	= z;
}

/*
// Depending on the print modifier 'L', ['l'], 'h'
// specify the type (==> copy function) and size
*/
static	int	print_complex_arginfo (const struct printf_info* info, size_t n,
                      int* argtypes, int* size)
{
	if (n == 1) {
		if (info->is_long_double) {		
			argtypes [0]	= lcomplex_type;
			size [0]	= sizeof (long_double_complex);
		}
		else if (info->is_short) {
			argtypes [0]	= fcomplex_type;
			size [0]	= sizeof (float_complex);
		}
		else {
			argtypes [0]	= dcomplex_type;
			size [0]	= sizeof (double_complex);
		}
	}
	return 1;
}

/* The actual printing routine - digits = ceil (bits_per_type * log(2))  */
# define	DISPLAY_WIDTH(t)	\
	(((sizeof(t)*CHAR_BIT)*3010)+5000)/10000 

static int	print_complex (
		FILE* stream,
		const struct printf_info* info,
		const void* const* args)
{
	char	buffer [2*DISPLAY_WIDTH(long double)+info->width + 1];
	char	fmt [15 + 2*DISPLAY_WIDTH(int) + 1];	

	char	modifier[2]	= {'\0', '\0'};
	char	showsign[2]	= {'\0', '\0'};
	char	altflag[2]	= {'\0', '\0'};
	char	fltspec[2]	= { info->spec == 'k' ? 'f' : 'g', '\0'};

	int	len	= 0;

	if (info->is_long_double) {
		*modifier	= 'L';
	}
	else if (info->is_short) {
		*modifier	= 'h';
	}

	if (info->showsign) {
		*showsign	= '+';
	}
	if (info->alt) {
		*altflag	= '#';
	}
/* Calculate the size of the format string which we construct
//
// (%+#.<int>Lg,%+#.<int>Lg)	=  2*(7+disp(int))+1  ~ 15 + 2*20 +1 
// 12345 ^   67^2345  ^  671
*/
	len	= snprintf (fmt, sizeof(fmt), "(%%%1$s%2$s.%3$d%4$s%5$s,%%%1$s%2$s.%3$d%4$s%5$s)",
			/*%1$*/ showsign, /*%2$*/ altflag, /*%3$*/ info->prec,
			/*%4$*/ modifier, /*%5$*/ fltspec);
	if (len == -1)
		return	len;
	if (info->is_long_double) {
		long_double_complex	z = ***(long_double_complex***)(args);
		len	= snprintf (buffer, sizeof(buffer), fmt, creal(z),cimag(z));
	}
	else if (info->is_short) {
		float_complex	z	= ***(float_complex***)(args);
		len	= snprintf (buffer, sizeof(buffer), fmt, creal(z),cimag(z));
	}
	else	{
		double_complex	z	= ***(double_complex***)(args);
		len	= snprintf (buffer, sizeof(buffer), fmt, creal(z),cimag(z));
	}
			
	if (len != -1) {
		len = fprintf (stream, "%*s",
			(info->left ? -info->width : info->width), buffer);
	}
	return len;
}


void __attribute__((constructor, visibility("hidden"))) complex_printf_fmt (void) {

	dcomplex_type	= register_printf_type (dcomplex_va_arg_function);
	fcomplex_type	= register_printf_type (fcomplex_va_arg_function);
	lcomplex_type	= register_printf_type (lcomplex_va_arg_function);

	register_printf_specifier ('K', print_complex, print_complex_arginfo);
	register_printf_specifier ('k', print_complex, print_complex_arginfo);
}
