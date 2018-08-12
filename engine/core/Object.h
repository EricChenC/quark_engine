/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Object class is a base class for all quark engine class.
/// Object have self name.

#pragma once

#include "Common.h"

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