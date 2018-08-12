/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 7/9/2018 8:54:12 PM
/// author: eric
/// class description ....

#pragma once

#include "Component.h"

namespace qe {
    namespace core
    {
        class DLL_EXPORT Behaviour : public Component
        {
        public:
            explicit Behaviour();
            ~Behaviour();

        // property
        public:
            /// <summary>
            /// Sets whether enable the behaviour 
            /// </summary>
            /// <param name="enable">if set to <c>true</c> enable the behaviour, else disable.</param>
            inline void set_enable(const bool& enable) { enable_ = enable; }


            /// <summary>
            /// Gets whether enable the behaviour 
            /// </summary>
            /// <returns></returns>
            inline auto get_enable() const -> const bool& { return enable_; }


        private:
            bool enable_;

        };
    }
}

