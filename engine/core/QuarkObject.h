/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// QuarkObject is all quark object base class.
///
/// QuarkObject is all quark object base class.
/// a quark object can add,get,remove component.
/// a quark object have parent and child relation.
/// a quark object have self id.

#pragma once

#include "CoreObject.h"

#include <vector>

namespace qe {
    namespace core {
        class Mesh;
        class Transform;
        class Material;
        class Component;
        class Scene;

        class DLL_EXPORT QuarkObject : public CoreObject {
        public:           
            /// <summary>
            /// Initializes a new instance of the <see cref="QuarkObject"/> class.
            /// Init quark object default value.
            /// id defulat is 0.
            /// parent_ default is null.
            /// </summary>
            explicit QuarkObject();

            /// <summary>
            /// Finalizes an instance of the <see cref="QuarkObject"/> class.
            /// </summary>
            ~QuarkObject();

            /// <summary>
            /// Sets the identifier.
            /// </summary>
            /// <param name="id">The identifier.</param>
            void set_id(const int& id);

            /// <summary>
            /// Gets the identifier.
            /// </summary>
            /// <returns>this quark object id.</returns>
            int get_id();

            /// <summary>
            /// Add T type component to this quark object.
            /// auto component = object->add_component<qe::Component>();
            /// </summary>
            /// <returns> T* is a quark object component pointer.</returns>
            template<typename T>
            std::shared_ptr<T> add_component() {
                auto component = std::make_shared<T>();

                component->set_component_flag(typeid(T*).name());
                component->set_quark_object(this);
                components_.push_back(component);
                return component;
            }

            /// <summary>
            /// Get T type component in this quark object.
            /// auto component = object->get_component<qe::Component>();
            /// </summary>
            /// <returns> T* is a quark object component pointer.</returns>
            template<typename T>
            std::shared_ptr<T> get_component() {
                std::shared_ptr<T> comp = nullptr;

                for (auto component : components_) {
                    if (component->get_component_flag() == typeid(T*).name()) {
                        comp = std::static_pointer_cast<T>(component);
                    }
                }

                return comp;
            }

            /// <summary>
            /// Get T type component list in this quark object.
            /// auto components = object->get_components<qe::Component>();
            /// </summary>
            /// <returns> std::vector<T*> is a quark object component pointer list.</returns>
            template<typename T>
            std::vector<std::shared_ptr<T>> get_components() {
                std::vector<std::shared_ptr<T>> component_list;

                for (auto component : components_) {
                    if (component->get_component_flag() == typeid(T*).name()) {
                        component_list.push_back(std::static_pointer_cast<T>(component));
                    }
                }

                return component_list;
            }

            auto get_scene()->Scene*;

            void set_scene(Scene* scene);

        private:
            /// <summary>
            /// The quark object id.
            /// </summary>
            int id_;

            /// <summary>
            /// The quark object components.
            /// </summary>
            std::vector<std::shared_ptr<qe::core::Component>> components_;
            
            /// <summary>
            /// The quark object transform
            /// </summary>
            std::shared_ptr<qe::core::Transform> transform_;

            /// <summary>
            /// The scene of this quark object
            /// </summary>
            Scene* scene_;

        };
    }

}