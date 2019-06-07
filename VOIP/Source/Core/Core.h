#ifdef VOIP_PLATFORM_WINDOWS
	#define FORCEINLINE __forceinline
	#define FORCENOINLINE __declspec(noinline)
#else	
	#define FORCEINLINE inline __attribute__ ((always_inline))
	#define FORCENOINLINE __attribute__((noinline))
#endif


#if __cplusplus >= 201402L
	#define DEPRECATED(msg) [[ deprecated(msg) ]]
#elif defined(__GNUC__)
	#define DEPRECATED(msg) __attribute__ ((deprecated(msg)))
#elif defined(_MSC_VER)
	#define DEPRECATED(msg) __declspec(deprecated(msg))
#else
	#define DEPRECATED(msg) 
#endif