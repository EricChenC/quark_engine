/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric


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

        /// <summary>
        /// QuarkObject is all quark object base class.  
        /// a quark object can add,get,remove component.  
        /// a quark object have parent and child relation, that can auto release memory.  
        /// a quark object have self id.  
        /// </summary>
        /// <seealso cref="CoreObject" />
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


        // properties
        public:
            /// <summary>
            /// Gets the identifier.
            /// </summary>
            /// <returns>this quark object id.</returns>
            inline auto get_id() const -> const int& { return id_; };

            /// <summary>
            /// Sets the identifier.
            /// </summary>
            /// <param name="id">The identifier.</param>
            inline void set_id(const int& id) { id_ = id; }

            /// <summary>
            /// Gets the scene.
            /// </summary>
            /// <returns></returns>
            inline auto get_scene()->Scene* { return scene_; }

            /// <summary>
            /// Sets the scene.
            /// </summary>
            /// <param name="scene">The scene.</param>
            inline void set_scene(Scene* scene) { scene_ = scene; }

            /// <summary>
            /// Gets the parent.
            /// </summary>
            /// <returns></returns>
            inline auto get_parent() const -> const qe::core::QuarkObject* { return parent_; }

            /// <summary>
            /// Sets the parent.
            /// </summary>
            /// <param name="parent">The parent.</param>
            inline void set_parent(qe::core::QuarkObject* parent) { parent_ = parent; }

        // methods
        public:

            /// <summary>
            /// Add T type component to this quark object.
            /// auto component = object->add_component<qe::Component>();
            /// </summary>
            /// <returns> T* is a quark object component pointer.</returns>
            template<typename T>
            inline auto AddComponent() -> std::shared_ptr<T>
            {
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
            inline auto GetComponent() const -> std::shared_ptr<T>
            {
                for (auto component : components_) {
                    if (component->get_component_flag() == typeid(T*).name()) {
                        return std::static_pointer_cast<T>(component);
                    }
                }

                return nullptr;
            }

            /// <summary>
            /// Get T type component list in this quark object.
            /// auto components = object->get_components<qe::Component>();
            /// </summary>
            /// <returns> std::vector<T*> is a quark object component pointer list.</returns>
            template<typename T>
            inline auto GetComponents() const -> std::vector<std::shared_ptr<T>>
            {
                std::vector<std::shared_ptr<T>> component_list;

                for (auto component : components_) {
                    if (component->get_component_flag() == typeid(T*).name()) {
                        component_list.push_back(std::static_pointer_cast<T>(component));
                    }
                }

                return component_list;
            }

            /// <summary>
            /// Gets the childs.
            /// </summary>
            /// <returns></returns>
            inline auto GetChilds() const ->std::vector<std::shared_ptr<qe::core::QuarkObject>> { return childs_; }

            /// <summary>
            /// Adds the child.
            /// </summary>
            /// <param name="child">The child.</param>
            inline void AddChild(const std::shared_ptr<qe::core::QuarkObject>& child);

            /// <summary>
            /// Detaches the child.
            /// </summary>
            /// <param name="child">The child.</param>
            inline void DetachChild(const std::shared_ptr<qe::core::QuarkObject>& child);

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
            /// The quark object pointer child list.
            /// </summary>
            std::vector<std::shared_ptr<qe::core::QuarkObject>> childs_;
            

            /// <summary>
            /// The scene of this quark object
            /// never manual delete this raw pointer!
            /// </summary>
            Scene* scene_;

            /// <summary>
            /// The quark object parent.
            /// never manual delete this raw pointer!
            /// </summary>
            QuarkObject* parent_;

        };
    }

}