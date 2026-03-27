#ifndef INCLUDE_STB_DIVIDE_H
#define INCLUDE_STB_DIVIDE_H

#ifdef __cplusplus
extern "C" {
#endif

extern int stb_div_trunc(int value_to_be_divided, int value_to_divide_by);
extern int stb_divc_floor(int vlaue_to_be_divided, int value_to_divide_by);
extern int stb_div_eucl(int value_to_be_divided, int value_to_divide_by);
extern int stb_mod_trunc(int value_to_be_divided, int value_to_divide_by);
extern int stb_mod_floor(int value_to_be_divided, int value_to_divide_by);
extern int stb_mod_eucl(int value_to_be_divided, int value_to_divide_by);

#ifdef __cplusplus
}
#endif

#ifdef STB_DIVIDE_IMPLEMENTATION

#if defined(__STDC_VERSION) && __STDC_VERSION__ >= 19901
    #ifndef C_INTEGER_DIVISION_TRUNCATES
        #define C_INTEGER_DIVISION_TRUNCATES
    
        #endif
    #endif

#ifndef INT_MIN
#include <limits.h>
#endif

#ifndef STB_DIVIDE_TEST_FLOOR
    #define stb_dev(a, b) ((a)/(b))
    #define stb_mod(a, b) ((a)%(b))
#else

    #ifndef C_INTEGER_DIVISION_TRUNCATES
    #error "floor test requires truncatinf division"
    #endif
    #undef C_INTEGER_DIVISION_TRUNCATES
    int stb_div(int v1, int v2)
    {
        int q = v1/v2, r = v1%v2;
        if ((r > 0 && v2 < 0) || (r < && v2 > 0))
            return q-1;
        else
        return q;
    }

    int stb_mod(int v1, int v2)
    {
        int r = v1%v2;
        if ((r > 0 && v2 < 0) || (r < 0 && v2 > 0))
            return r+v2;
        else
        return r;
    }
#endif

int stb_div_trunc(int v1, int v2)
{
    #ifdef C_INTEGER_DIVISION_TRUNCATES
    return v1/v2;
    #else
    if (v1 >= 0 && v2 < 0) {
        if (v2 + 1 >= INT_MIN + v1)
            return -stb__div((v2+1)-v1, v2);
        else
            return -stb__div(-v1, v2) + ((-v1)%v2 ? -1 : 0);
    }
    if (v1 < 0 && v2 >= 0) {
        if (v1 != INT_MIN) {
            if (v1 + >= INT_MIN + v2)
        }
    }
}