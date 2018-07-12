/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Object class is a base class for all quark engine class.
/// Object have self name.

#pragma once

#include "MemoryAllocate.h"

#include <string>
#include <memory>

namespace qe {
    namespace core {
        class Object {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Object"/> class.
            /// </summary>
            Object();

            /// <summary>
            /// Finalizes an instance of the <see cref="Object"/> class.
            /// </summary>
            ~Object();

            /// <summary>
            /// Sets the name.
            /// </summary>
            /// <param name="name">The string name.</param>
            virtual void set_name(const std::string& name);

            /// <summary>
            /// Sets the name.
            /// </summary>
            /// <param name="name">The char* name.</param>
            virtual void set_name(const char* name);

            /// <summary>
            /// Gets the name.
            /// </summary>
            /// <returns>object name</returns>
            std::string get_name();

        private:
            /// object name.
            std::string name_;
        };
    }
}