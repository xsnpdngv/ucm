#define CODETIME(Time, Code) ({struct timeval s,e;\
                               gettimeofday(&s, NULL);\
                                   Code \
                               gettimeofday(&e, NULL);\
                               Time += (e.tv_usec-s.tv_usec) + 1000000*(e.tv_sec-s.tv_sec);})
