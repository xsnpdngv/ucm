#include <stdio.h>
#include "ucm.h"

#define AAA(ggg)  { 1, ({2;}), TYPE_CHECK(int, ggg) }

typedef struct
{
    int a,b,c;

} asdf_t;

int main()
{
    int a = 5;
    int b = 2;
    char x;
    char y[19];
    int c[] = { MIN(1,2), TYPE_CHECK(int, a), ({9;}), STR_CHECK(y) };
    asdf_t i[] = { { 1, ({2;}), 3 }, { 4, 4, 4 } };
    asdf_t j[] = { AAA(3), AAA(x) };

    TYPE_CHECK(int, a);
    STR_CHECK(y);

    printf("min: %d\nc[0]: %d\nc[1]: %d\nc[2]: %d\n", MIN(a, b), c[0], c[1], c[2]);
    printf("j[0].a: %d\nj[0].b: %d\nj[0].c: %d\n", j[0].a, j[0].b, j[0].c);
}
