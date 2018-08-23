/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Object class is a base class for all quark engine class.
/// Object have self name.

#pragma once


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


#include <string>
#include <memory>

namespace qe {
    namespace core {
        class DLL_EXPORT Object {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Object"/> class.
            /// </summary>
            Object();

            /// <summary>
            /// Finalizes an instance of the <see cref="Object"/> class.
            /// </summary>
            ~Object();

        // properties
        public:
            /// <summary>
            /// Gets the name.
            /// </summary>
            /// <returns>object name</returns>
            inline auto get_name() const -> const std::string& { return name_; }

            /// <summary>
            /// Sets the name.
            /// </summary>
            /// <param name="name">The string name.</param>
            inline virtual void set_name(const std::string& name){ name_ = name; }

            /// <summary>
            /// Sets the name.
            /// </summary>
            /// <param name="name">The char* name.</param>
            inline virtual void set_name(const char* name){ name_ = name; }

        private:
            /// object name.
            std::string name_;



        };
    }
}