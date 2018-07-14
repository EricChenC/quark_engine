#ifdef _WIN32
#ifdef dll_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif
#else
#define DLL_EXPORT
#endif