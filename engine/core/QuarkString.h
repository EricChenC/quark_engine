/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// String processed string data.
#pragma once

#include "CoreObject.h"

#include <vector>
#include <string>

namespace qe {
    namespace core {
        class DLL_EXPORT QuarkString : public CoreObject {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="QuarkString"/> class.
            /// </summary>
            explicit QuarkString();

            /// <summary>
            /// Finalizes an instance of the <see cref="QuarkString"/> class.
            /// </summary>
            ~QuarkString();

        // methods
        public:

            /// <summary>
            /// split a string use split_str, then return a splited string list.
            /// </summary>
            /// <param name="str">The string.</param>
            /// <param name="split_str">is used to split string.</param>
            /// <returns>a list is str be splited use split_str.</returns>
            static auto Split(const std::string& str, const std::string& delimiter)->std::vector<std::string>;

            /// <summary>
            /// Gets the path prefixed. 
            /// path: ./shader/standard.shader 
            /// path prefixed: ./shader/
            /// </summary>
            /// <param name="path">The path.</param>
            /// <returns>path prefixed</returns>
            static auto PathPrefixed(const std::string& path) ->std::string;

            /// <summary>
            /// Get a file name in give path, return a file name.
            /// if have not find file name, will return nullptr.
            /// </summary>
            /// <param name="path">The file path..</param>
            /// <returns>a file name.</returns>
            static auto FileName(const std::string& path) ->std::string;

            /// <summary>
            /// Gets the file format.
            /// </summary>
            /// <param name="path">The path.</param>
            /// <returns>file format</returns>
            static std::string FileFormat(const std::string& path);


        };
    }
}

