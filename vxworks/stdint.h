#ifndef VXWORKS_STDINT_H_
#define VXWORKS_STDINT_H_

/* Exact integral types. */

/* Signed.  */
typedef signed char   int8_t;
typedef short int     int16_t;
typedef int           int32_t;
typedef long long int int64_t;

/* Unsigned.  */
typedef unsigned char          uint8_t;
typedef unsigned short int     uint16_t;
typedef unsigned int           uint32_t;
typedef unsigned long long int uint64_t;

/* Small types.  */

/* Signed.  */
typedef signed char   int_least8_t;
typedef short int     int_least16_t;
typedef int           int_least32_t;
typedef long long int int_least64_t;

/* Unsigned.  */
typedef unsigned char          uint_least8_t;
typedef unsigned short int     uint_least16_t;
typedef unsigned int           uint_least32_t;
typedef unsigned long long int uint_least64_t;

/* Fast types.  */

/* Signed.  */
typedef signed char    int_fast8_t;
typedef int            int_fast16_t;
typedef int            int_fast32_t;
typedef long long int  int_fast64_t;

/* Unsigned.  */
typedef unsigned char          uint_fast8_t;
typedef unsigned int           uint_fast16_t;
typedef unsigned int           uint_fast32_t;
typedef unsigned long long int uint_fast64_t;

/* Types for `void *' pointers.  */
typedef int          intptr_t;
typedef unsigned int uintptr_t;

/* Largest integral types.  */
typedef long long int          intmax_t;
typedef unsigned long long int uintmax_t;

/* Limits of integral types.  */

/* Minimum of signed integral types.  */
#define INT8_MIN        (-128)
#define INT16_MIN       (-32767-1)
#define INT32_MIN       (-2147483647-1)
#define INT64_MIN       (-__INT64_C(9223372036854775807)-1)

/* Maximum of signed integral types.  */
#define INT8_MAX        (127)
#define INT16_MAX       (32767)
#define INT32_MAX       (2147483647)
#define INT64_MAX       (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
#define UINT8_MAX        (255)
#define UINT16_MAX       (65535)
#define UINT32_MAX       (4294967295U)
#define UINT64_MAX       (__UINT64_C(18446744073709551615))

/* Minimum of signed integral types having a minimum size.  */
#define INT_LEAST8_MIN     (-128)
#define INT_LEAST16_MIN    (-32767-1)
#define INT_LEAST32_MIN    (-2147483647-1)
#define INT_LEAST64_MIN    (-__INT64_C(9223372036854775807)-1)

/* Maximum of signed integral types having a minimum size.  */
#define INT_LEAST8_MAX     (127)
#define INT_LEAST16_MAX    (32767)
#define INT_LEAST32_MAX    (2147483647)
#define INT_LEAST64_MAX    (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types having a minimum size.  */
#define UINT_LEAST8_MAX    (255)
#define UINT_LEAST16_MAX   (65535)
#define UINT_LEAST32_MAX   (4294967295U)
#define UINT_LEAST64_MAX   (__UINT64_C(18446744073709551615))

/* Minimum of fast signed integral types having a minimum size.  */
#define INT_FAST8_MIN     (-128)
#define INT_FAST16_MIN    (-2147483647-1)
#define INT_FAST32_MIN    (-2147483647-1)
#define INT_FAST64_MIN        (-__INT64_C(9223372036854775807)-1)

/* Maximum of fast signed integral types having a minimum size.  */
#define INT_FAST8_MAX     (127)
#define INT_FAST16_MAX    (2147483647)
#define INT_FAST32_MAX    (2147483647)
#define INT_FAST64_MAX    (__INT64_C(9223372036854775807))

/* Maximum of fast unsigned integral types having a minimum size.  */
#define UINT_FAST8_MAX     (255)
#define UINT_FAST16_MAX    (4294967295U)
#define UINT_FAST32_MAX    (4294967295U)
#define UINT_FAST64_MAX    (__UINT64_C(18446744073709551615))

/* Values to test for integral types holding `void *' pointer.  */
#define INTPTR_MIN        (-2147483647-1)
#define INTPTR_MAX        (2147483647)
#define UINTPTR_MAX       (4294967295U)

/* Minimum for largest signed integral type.  */
#define INTMAX_MIN        (-__INT64_C(9223372036854775807)-1)

/* Maximum for largest signed integral type.  */
#define INTMAX_MAX        (__INT64_C(9223372036854775807))

/* Maximum for largest unsigned integral type.  */
#define UINTMAX_MAX       (__UINT64_C(18446744073709551615))

/* Limits of other integer types.  */

/* Limits of `ptrdiff_t' type.  */
#define PTRDIFF_MIN        (-2147483647-1)
#define PTRDIFF_MAX        (2147483647)

/* Limits of `sig_atomic_t'.  */
#define SIG_ATOMIC_MIN        (-2147483647-1)
#define SIG_ATOMIC_MAX        (2147483647)

/* Limit of `size_t' type.  */
#define SIZE_MAX        (4294967295U)

#endif /* VXWORKS_STDINT_H_ */
