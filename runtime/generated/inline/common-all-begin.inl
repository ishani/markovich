// included by generated code; configure the default optimisation and storage macros for the mk- code

#if defined(_MSC_VER) && !defined(__CLANG__)

// not definitive but on earlier msvc compilers, the vast switch statements
// would cause compilation to explode while being optimised
# if _MSC_VER < 1920
#  pragma optimize( "", off )
#  pragma optimize( "wat", on )
#  define MKV_DISABLED_MSVC_OPT
# endif

#define MKV_DISABLE_OPT
#else
#define MKV_DISABLE_OPT [[clang::optnone]]
#endif    // !_MSC_VER

#define MKV_DATA const
