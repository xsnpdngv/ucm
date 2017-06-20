/**
 * @file    ucm.h
 * @brief   useful C macros
 * @author  Tamas Dezso <dezso.t.tamas@gmail.com>
 */

/* overload for function-like macros with various number of named arguments */
#define OVERLOAD(Func, .../* Arg1[, Arg2[, Arg3]] */) \
        FUNC_SEL(__VA_ARGS__, Func##3, Func##2, Func##1, x)(__VA_ARGS__)

#define FUNC_SEL(Arg1, Arg2, Arg3, Func, ...) Func
#define FUNC(/* arg1[, arg2[, arg3]] */ ...) OVERLOAD(FUNC, __VA_ARGS__)
#define FUNC2(arg1, arg2) arg1
#define FUNC3(arg1, arg2, arg3) arg1#arg2

/* type safe, side effect free minimum */
#define MIN(x, y)                                                             \
({                                                                            \
        __typeof__ (x) _x = (x);                                              \
        __typeof__ (y) _y = (y);                                              \
        (void)(&_x == &_y);                                                   \
        _x < _y ? _x : _y;                                                    \
})

/* offset of member within structure */
#define OFFSETOF(struct_t, member) ((size_t)&(((struct_t *)0)->member))

/* fake structure member instead of real one to use for types instead
 * of variables */
#define FAKEMBR(struct_t, member) ((struct_t *)0)->member

/* size of fake structure member */
#define SIZEOF(struct_t, member) sizeof(FAKEMBR(struct_t, member))

/* type of fake structure member */
#define TYPEOF(struct_t, member) __typeof(FAKEMBR(struct_t, member))

/* ensures that v is a valid identifier name */
#define VARIABLE(v) { enum v { }; }

/* safely assigns value to a variable */
#define ASSIGN(variable, value)                                               \
{                                                                             \
        VARIABLE(variable)                                                    \
        variable = value;                                                     \
}

/* ensures v is numeric constant */
#define CONST_INT(v) { enum { E = v }; }

/* safely declares variable */
#define DECLARE(type, variable, value)                                        \
{                                                                             \
        VARIABLE(variable)                                                    \
        CONST_INT(value)                                                      \
        type variable = value;                                                \
}

/* ensures that the list of identifiers only contains unique ids */
#define UNIQUE(is...) { enum { is }; } /* UNIQUE(name1, name2, name3) */

/* compile time checks to produce compile error in case of failure */
#define IS_TRUE(a) { struct _ { int d0[!(a)]; int d1[-!(a)]; }; }
#define LESS_THAN(a, b) IS_TRUE(a < b)
#define EQUAL(a, b) IS_TRUE(a == b)
#define SMALL_TYPE(t) IS_TRUE(sizeof(t) < 8)

/* checks whether var is a variable of type type (compile time error if not) */
/* NOTE: macros like ({expr;}) won't work in global variable's initializer
         but can be used in main for same goal */
#define TYPE_CHECK(type, x)                                                   \
({                                                                            \
        type _x;                                                              \
        __typeof__ (x) _y;                                                    \
        (void)(&_x == &_y);                                                   \
        3;                                                                    \
})

/* checks whether var is character pointer (compile time error if not) */
/* NOTE: macros like ({expr;}) won't work in global variable's initializer
         but can be used in main for same goal */
#define STR_CHECK(x)                                                          \
({                                                                            \
        char *_x;                                                             \
        __typeof__ (x) _y;                                                    \
        (void)(_x == _y);                                                     \
        6;                                                                    \
})
