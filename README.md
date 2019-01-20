# printf_extension_complex
## Glibc printf extension to print C99 complex types


```
 Usage:  %K - for Komplex ...  zZ and cC are already used in some way,

 eg      (1.000,2.000)   = 1.0 + 2.9*I

    %[width][.prec]K        - uses %g format  
    %[width][.prec]k        - uses %f format

      width   - total width for the whole complex number
      prec    - significant digits for real and imaginary part
              eg (1.0,1.0) from %9.1K  

      %LK             - long double complex
      %hK             - float complex
      %K, or %lK      - [double] complex
      %-12.1K - left adjust the whole (x,y)
      %+K     - print sign eg (+1.0,+1.0)
      
```
