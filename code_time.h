#define TIME(sum, code) ({struct timeval s,e;\
                          gettimeofday(&s, NULL);\
                              code;\
                          gettimeofday(&e, NULL);\
                          sum += (e.tv_usec-s.tv_usec) + 1000000*(e.tv_sec-s.tv_sec);})
