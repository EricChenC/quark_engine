/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

/// If define _DEBUG, then use DBG_NEW to create new object,
/// will can use _CRTDBG_MAP_ALLOC to check memory allocate leak position,
/// otherwise DBG_NEW just create a normal object.

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#ifdef _WIN32
#ifdef dll_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif
#else
#define DLL_EXPORT
#endif

#define VERIFY(x) assert(x)
