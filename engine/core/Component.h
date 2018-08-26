/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// The Component is a component, can add to QuarkObject.
///
/// Every component have a flag for distinguish be added component.
/// this flag is default set by typeid(T*).name(), T is component.


#pragma once

#include "CoreObject.h"

namespace qe {
    namespace core {

        class QuarkObject;

        class DLL_EXPORT Component : public CoreObject {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Component"/> class.
            /// </summary>
            explicit Component();

            /// <summary>
            /// Finalizes an instance of the <see cref="Component"/> class.
            /// </summary>
            ~Component();

        // properties
        public:
            /// <summary>
            /// Get quark object that is this component be added.
            /// Get the quark object to add this component.
            /// </summary>
            /// <returns> Gets the quark object of this component. </returns>
            inline auto get_quark_object() const -> qe::core::QuarkObject* { return quark_object_; }

            /// <summary>
            /// Sets the quark object of this component.
            /// just only used in quark object add_component() function.
            /// </summary>
            /// <param name="quark_object">The quark object.</param>
            inline auto set_quark_object(qe::core::QuarkObject* quark_object){ quark_object_ = quark_object; }

        // properties
        private:
            /// <summary>
            /// Sets the component flag. default set by typeid(T*).name(), T is component.
            /// </summary>
            /// <param name="flag">The component flag.</param>
            inline void set_component_flag(const std::string& flag) { component_flag_ = flag; }

            /// <summary>
            /// Gets the component flag.
            /// </summary>
            /// <returns> component flag </returns>
            inline auto get_component_flag() { return component_flag_; }

        private:
            /// <summary>
            /// The component flag, this flag is default set by typeid(T*).name(), T is component.
            /// </summary>
            std::string component_flag_;

            /// <summary>
            /// The quark object of this component.
            /// never manual delete this raw pointer!
            /// </summary>
           qe::core::QuarkObject* quark_object_;

            /// <summary>
            /// friend class quarkobject. 
            /// then quarkobject can called component private function.
            /// just avoid developer called this function .
            /// </summary>
            friend class QuarkObject;

        };
    }
}