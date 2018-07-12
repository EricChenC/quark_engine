/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 7/9/2018 10:20:07 PM
/// author: eric
/// class description ....

#pragma once

#include "Scriptbehaviour.h"

namespace qe {
    namespace core
    {
        class AwakeBehaviour : public ScriptBehaviour
        {
        public:
            explicit AwakeBehaviour();
            ~AwakeBehaviour();

            void Awake() override;

            void Update() override;


        };
    }
}

