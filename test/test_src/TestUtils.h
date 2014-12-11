
#ifndef TESTUTILS_H
#define	TESTUTILS_H

#define TEST_FAIL(x)      do { fprintf(stderr, "Failed at line %d\n", __LINE__); exit(x); } while(0)
#define TEST_RESULT(x)    do { if( x ) { /* Nothing */ } else { TEST_FAIL(1); } } while(0) 

#define UNUSED(x)         (void)(x)

#endif	/* TESTUTILS_H */

