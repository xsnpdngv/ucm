/* overload for function-like macros with various number of named arguments */
#define OVERLOAD(Func, .../* Arg1[, Arg2[, Arg3]] */) \
                            FUNC_SEL(__VA_ARGS__, \
                                     Func##3, Func##2, Func##1, x)(__VA_ARGS__)
#define FUNC_SEL(Arg1, Arg2, Arg3, Func, ...) Func

#define FUNC(/* arg1[, arg2[, arg3]] */ ...) \
                            OVERLOAD(FUNC, __VA_ARGS__)
#define FUNC2(arg1, arg2)    arg1
#define FUNC3(arg1, arg2, arg3) \
                            arg1#arg2

#define offsetof(st, m) ((size_t)&(((st *)0)->m))

/* fake member of structure instead of real instance */
#define FAKEMBR(struct_t, member) ((struct_t *)0)->member

/* size of fake structure member */
#define SIZEOF(struct_t, member) sizeof(FAKEMBR(struct_t, member))
                              /* SIZEOF(msg_t, par.db.key) */

/* type of fake structure member */
#define TYPEOF(struct_t, member) __typeof(FAKEMBR(struct_t, member))

/* check whether var is a variable of type type (compile time error if not) */
#define TYPE_CHECK(type, x)  ({type _x; \
                               __typeof__ (x) _y; \
                               (void)(&_x == &_y); \
                               3;})

/* check whether var is character pointer (compile time error if not) */
#define STR_CHECK(x)         ({char *_x; \
                               __typeof__ (x) _y; \
                               (void)(_x == _y); \
                               6;})

/* ensures that v is a valid identifier name */
#define VARIABLE(v) { enum v { }; }

/* safely assigns value to a variable */
#define ASSIGN(variable, value) \
VARIABLE(variable) \
variable = value;

/* ensures v is numeric constant */
#define CONST_INT(v) { enum { E = v }; }

/* safely declares variable */
#define DECLARE(type, variable, value) \
                    VARIABLE(variable) \
                    CONST_INT(value) \
                    type variable = value;

/* ensures that the list of identifiers only contains unique ids */
#define UNIQUE(is...) { enum { is }; }
                    /* UNIQUE(name1, name2, name3) */

#define IS_TRUE(a) { struct _ { int d0[!(a)]; int d1[-!(a)]; }; }
#define LESS_THAN(a, b) IS_TRUE(a < b)
#define EQUAL(a, b) IS_TRUE(a == b)
#define SMALL_TYPE(t) IS_TRUE(sizeof(t) < 8)
