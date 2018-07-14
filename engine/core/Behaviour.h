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

            /// <summary>
            /// Sets whether enable the behaviour 
            /// </summary>
            /// <param name="enable">if set to <c>true</c> enable the behaviour, else disable.</param>
            void set_enable(bool enable);


            /// <summary>
            /// Gets whether enable the behaviour 
            /// </summary>
            /// <returns></returns>
            bool get_enable();


        private:
            bool enable_;

        };
    }
}

