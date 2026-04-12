/* config.h - Cross-platform configuration for qrencode */
/* Generated manually for NBaseUiKit project */

/* Major version number */
#define MAJOR_VERSION 3

/* Micro version number */
#define MICRO_VERSION 3

/* Minor version number */
#define MINOR_VERSION 4

/* Version number of package */
#define VERSION "3.4.3"

/* Define to 'static' if no test programs will be compiled. */
#define __STATIC static

/* Platform-specific configurations */
#ifdef _WIN32
    /* Windows specific configuration */
    #define HAVE_STDLIB_H 1
    #define HAVE_STRING_H 1
    #define HAVE_MEMORY_H 1
    #define STDC_HEADERS 1
    #define HAVE_STRDUP 1
    
    /* Windows doesn't have unistd.h or pthread by default */
    /* #undef HAVE_UNISTD_H */
    /* #undef HAVE_LIBPTHREAD */
    /* #undef HAVE_DLFCN_H */
    /* #undef HAVE_SYS_STAT_H */
    /* #undef HAVE_SYS_TYPES_H */
    
    /* Use MSVC inline */
    #ifndef __cplusplus
        #define inline __inline
    #endif
#else
    /* Linux/Unix specific configuration */
    #define HAVE_DLFCN_H 1
    #define HAVE_INTTYPES_H 1
    #define HAVE_LIBPTHREAD 1
    #define HAVE_MEMORY_H 1
    #define HAVE_STDINT_H 1
    #define HAVE_STDLIB_H 1
    #define HAVE_STRDUP 1
    #define HAVE_STRINGS_H 1
    #define HAVE_STRING_H 1
    #define HAVE_SYS_STAT_H 1
    #define HAVE_SYS_TYPES_H 1
    #define HAVE_UNISTD_H 1
    #define STDC_HEADERS 1
    
    /* Standard inline for C */
    #ifndef __cplusplus
        #define inline inline
    #endif
#endif
