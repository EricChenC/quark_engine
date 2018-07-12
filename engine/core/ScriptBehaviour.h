/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 7/9/2018 8:57:43 PM
/// author: eric
/// class description ....

#pragma once

#include "Behaviour.h"

namespace qe {
    namespace core
    {
        class ScriptBehaviour : public Behaviour
        {
        public:
            explicit ScriptBehaviour();
            ~ScriptBehaviour();

            /// <summary>
            /// Awake is called when the script instance is being loaded.
            /// </summary>
            virtual void Awake();

            /// <summary>
            /// This function is called every fixed framerate frame, if the Behaviour is enabled.
            /// </summary>
            virtual void FixedUpdate();

            /// <summary>
            /// LateUpdate is called every frame, if the Behaviour is enabled.
            /// </summary>
            virtual void LateUpdate();

            /// <summary>
            /// Callback for setting up animation IK (inverse kinematics).
            /// </summary>
            virtual void OnAnimatorIK();

            /// <summary>
            /// Callback for processing animation movements for modifying root motion.
            /// </summary>
            virtual void OnAnimatorMove();

            /// <summary>
            /// Sent to all GameObjects when the player gets or loses focus.
            /// </summary>
            virtual void OnApplicationFocus();

            /// <summary>
            /// Sent to all GameObjects when the application pauses.
            /// </summary>
            virtual void OnApplicationPause();

            /// <summary>
            /// Sent to all game objects before the application is quit.
            /// </summary>
            virtual void OnApplicationQuit();

            /// <summary>
            /// If OnAudioFilterRead is implemented, Unity will insert a custom filter into the audio DSP chain.
            /// </summary>
            virtual void OnAudioFlterRead();

            /// <summary>
            /// OnBecameInvisible is called when the renderer is no longer visible by any camera.
            /// </summary>
            virtual void OnBecameInvisible();

            /// <summary>
            /// OnBecameVisible is called when the renderer became visible by any camera.
            /// </summary>
            virtual void OnBecameVisible();

            /// <summary>
            /// OnCollisionEnter is called when this collider/rigidbody has begun touching another rigidbody/collider.
            /// </summary>
            virtual void OnCollisionEnter();

            /// <summary>
            /// OnCollisionExit is called when this collider/rigidbody has stopped touching another rigidbody/collider.
            /// </summary>
            virtual void OnCollisionExit();

            /// <summary>
            /// OnCollisionStay is called once per frame for every collider/rigidbody that is touching rigidbody/collider.
            /// </summary>
            virtual void OnCollisionStay();

            /// <summary>
            /// Called on the client when you have successfully connected to a server.
            /// </summary>
            virtual void OnConnectedToServer();

            /// <summary>
            /// OnControllerColliderHit is called when the controller hits a collider while performing a Move.
            /// </summary>
            virtual void OnControllerColliderHit();

            /// <summary>
            /// This function is called when the Behaviour will be destroyed.
            /// </summary>
            virtual void OnDestroy();

            /// <summary>
            /// This function is called when the behaviour becomes disabled () or inactive.
            /// </summary>
            virtual void OnDisable();

            /// <summary>
            /// Called on the client when the connection was lost or you disconnected from the server.
            /// </summary>
            virtual void OnDisconnectedFromServer();

            /// <summary>
            /// This function is called when the object becomes enabled and active.
            /// </summary>
            virtual void OnEnable();

            /// <summary>
            /// Called on the client when a connection attempt fails for some reason.
            /// </summary>
            virtual void OnFailedToConnect();

            /// <summary>
            /// Called on clients or servers when there is a problem connecting to the MasterServer.
            /// </summary>
            virtual void OnFailedToConnectToMasterServer();

            /// <summary>
            /// OnGUI is called for rendering and handling GUI events.
            /// </summary>
            virtual void OnGUI();

            /// <summary>
            /// OnMouseDown is called when the user has pressed the mouse button while over the GUIElement or Collider.
            /// </summary>
            virtual void OnMouseDown();

            /// <summary>
            /// OnMouseDrag is called when the user has clicked on a GUIElement or Collider and is still holding down the mouse.
            /// </summary>
            virtual void OnMouseDrag();

            /// <summary>
            /// Called when the mouse enters the GUIElement or Collider.
            /// </summary>
            virtual void OnMouseEnter();

            /// <summary>
            /// Called when the mouse is not any longer over the GUIElement or Collider.
            /// </summary>
            virtual void OnMouseExit();

            /// <summary>
            /// Called every frame while the mouse is over the GUIElement or Collider.
            /// </summary>
            virtual void OnMouseOver();

            /// <summary>
            /// OnMouseUp is called when the user has released the mouse button.
            /// </summary>
            virtual void OnMouseUp();

            /// <summary>
            /// OnParticleCollision is called when a particle hits a Collider.
            /// </summary>
            virtual void OnParticleCollision();

            /// <summary>
            /// OnParticleTrigger is called when any particles in a particle system meet the conditions in the trigger module.
            /// </summary>
            virtual void OnParticleTrigger();

            /// <summary>
            /// Called on the server whenever a new player has successfully connected.
            /// </summary>
            virtual void OnPlayerConnected();

            /// <summary>
            /// Called on the server whenever a player disconnected from the server.
            /// </summary>
            virtual void OnPlayerDisconnected();

            /// <summary>
            /// OnPostRender is called after a camera finished rendering the scene.
            /// </summary>
            virtual void OnPostRender();

            /// <summary>
            /// OnPreCull is called before a camera culls the scene.
            /// </summary>
            virtual void OnPreCull();

            /// <summary>
            /// OnPreRender is called before a camera starts rendering the scene.
            /// </summary>
            virtual void OnPreRender();

            /// <summary>
            /// OnRenderImage is called after all rendering is complete to render image.
            /// </summary>
            virtual void OnRenderImage();

            /// <summary>
            /// OnRenderObject is called after camera has rendered the scene.
            /// </summary>
            virtual void OnRenderObject();

            /// <summary>
            /// This function is called when the list of children of the transform of the GameObject has changed.
            /// </summary>
            virtual void OnTransformChildrenChanged();

            /// <summary>
            /// This function is called when the parent property of the transform of the GameObject has changed.
            /// </summary>
            virtual void OnTransformParentChanged();

            /// <summary>
            /// OnTriggerEnter is called when the Collider other enters the trigger.
            /// </summary>
            virtual void OnTriggerEnter();

            /// <summary>
            /// OnTriggerExit is called when the Collider other has stopped touching the trigger.
            /// </summary>
            virtual void OnTriggerExit();

            /// <summary>
            /// OnTriggerStay is called once per physics update for every Collider other that is touching the trigger.
            /// </summary>
            virtual void OnTriggerStay();

            /// <summary>
            /// OnWillRenderObject is called for each camera if the object is visible and not a UI element.
            /// </summary>
            virtual void OnWillRenderObject();

            /// <summary>
            /// Reset to default values.
            /// </summary>
            virtual void Reset();

            /// <summary>
            /// Start is called on the frame when a script is enabled just before any of the Update methods are called the first time.
            /// </summary>
            virtual void Start();

            /// <summary>
            /// Update is called every frame, if the Behaviour is enabled.
            /// </summary>
            virtual void Update();
                

        };
    }
}

