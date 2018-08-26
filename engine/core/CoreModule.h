#pragma once

#include <glm/glm.hpp>
#include <memory>


/// If define _DEBUG, then use DBG_NEW to create new object,
/// will can use _CRTDBG_MAP_ALLOC to check memory allocate leak position,
/// otherwise DBG_NEW just create a normal object.

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#ifdef _WIN32
#ifdef dll_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif
#else
#define DLL_EXPORT
#endif

#define VERIFY(x) assert(x)


namespace qe {
    namespace core {
        struct Ray
        {
            glm::vec3 direction;
            glm::vec3 origion;
        };

        struct Rect
        {

            /// <summary>
            /// static method
            /// </summary>
        public:
            static Rect MinMaxRect(float xmin, float ymin, float xmax, float ymax) {
                return Rect(xmin, ymin, xmax, ymax);
            }

            static Rect Zero() {
                return Rect(0, 0, 0, 0);
            }


        public:
            Rect()
            {
            }

            Rect(const float& x, const float& y, const float& width, const float& height)
                :x(x),
                y(y),
                width(width),
                height(height)
            {
            }

            bool Contains(const glm::vec2& point) {
                return true;
            }

            bool Contains(const glm::vec3& point) {
                return true;
            }

            bool Contains(const glm::vec3& point, bool allowInverse) {
                return true;
            }


            bool Overlaps(const Rect& rect) {
                return true;
            }

            bool Overlaps(const Rect& rect, bool allowInverse) {
                return true;
            }

            auto Set(const float& x, const float& y, const float& width, const float& height) {
                this->x = x;
                this->y = y;
                this->width = width;
                this->height = height;
            }


        public:
            float x;

            float y;

            float width;

            float height;

            float center;

            glm::vec2 max;

            glm::vec2 min;

            /// <summary>
            /// The X and Y position of the rectangle.
            /// </summary>
            glm::vec2 position;

            glm::vec2 size;

            float xMax;

            float xMin;

            float yMax;

            float yMin;

        };

        enum class KeyCode
        {
            NONE,           // not assigned
            KEYBACKSPACE,      // backspace key
            KEYDELETE,         // delete key
            KEYTAB,            // tab key
            KEYCLEAR,          // clear key
            KEYRETURN,         // return key
            KEYPAUSE,          // Pause on PC machines
            KEYESCAPE,         // escape key
            KEYSPACE,          // space key
            KEYPAD0,        // Numeric keypad 0
            KEYPAD1,        // Numeric keypad 1
            KEYPAD2,        // Numeric keypad 2
            KEYPAD3,        // Numeric keypad 3
            KEYPAD4,        // Numeric keypad 4
            KEYPAD5,        // Numeric keypad 5
            KEYPAD6,        // Numeric keypad 6
            KEYPAD7,        // Numeric keypad 7
            KEYPAD8,        // Numeric keypad 8
            KEYPAD9,        // Numeric keypad 9
            KEYPADPERIOD,   // Numeric keypad .
            KEYPADDIVIDE,   // Numeric keypad /
            KEYPADMULTIPLY, // Numeric keypad *
            KEYPADMINUS,    // Numeric keypad -
            KEYPADPLUS,     // Numeric keypad +
            KEYPADENTER,    // Numeric keypad enter key
            KEYPADEQUALS,   // Numeric keypad =
            UPARROW,        // up arrow key
            DOWNARROW,      // down arrow key
            RIGHTARROW,     // right arrow key
            LEFTARROW,      // left arrow key
            INSERT,         // insert key
            HOME,           // home key
            END,            // end key
            PAGEUP,         // page up
            PAGEDOWN,       // page down
            F1,             // F1 key
            F2,             // F2 key
            F3,             // F3 key
            F4,             // F4 key
            F5,             // F5 key
            F6,             // F6 key
            F7,             // F7 key
            F8,             // F8 key
            F9,             // F9 key
            F10,            // F10 key
            F11,            // F11 key
            F12,            // F12 key
            F13,            // F13 key
            F14,            // F14 key
            F15,            // F15 key
            ALPHA0,         // alphanumeric keyboard 0
            ALPHA1,         // alphanumeric keyboard 1
            ALPHA2,         // alphanumeric keyboard 2
            ALPHA3,         // alphanumeric keyboard 3
            ALPHA4,         // alphanumeric keyboard 4
            ALPHA5,         // alphanumeric keyboard 5
            ALPHA6,         // alphanumeric keyboard 6
            ALPHA7,         // alphanumeric keyboard 7
            ALPHA8,         // alphanumeric keyboard 8
            ALPHA9,         // alphanumeric keyboard 9
            EXCLAIM,        // '!'
            DOUBLEQUOTE,    // '"'
            HASH,           // '#'
            DOLLAR,         // '$'
            AMPERSAND,      // '&'
            QUOTE,          // '''
            LEFTPAREN,      // '('
            RIGHTPAREN,     // ')'
            ASTERISK,       // '*'
            PLUS,           // '+'
            MINUS,          // '-'
            PERIOD,         // '.'
            SLASH,          // '/'
            COLON,          // ':'
            SEMICOLON,      // ';'
            LESS,           // '<'
            EQUALS,         // '='
            GREATER,        // '>'
            QUESTION,       // '?'
            AT,             // '@'
            LEFTBRACKET,    // '['
            BACKSLASH,      // '\'
            RIGHTBRACKET,   // ']'
            CARET,          // '^'
            UNDERSCORE,     // '_'
            BACKQUOTE,      // '`'
            A,              // 'a'
            B,              // 'b'
            C,              // 'c'
            D,              // 'd'
            E,              // 'e'
            F,              // 'f'
            G,              // 'g'
            H,              // 'h'
            I,              // 'i'
            J,              // 'j'
            K,              // 'k'
            L,              // 'l'
            M,              // 'm'
            N,              // 'n'
            O,              // 'o'
            P,              // 'p'
            Q,              // 'q'
            R,              // 'r'
            S,              // 's'
            T,              // 't'
            U,              // 'u'
            V,              // 'v'
            W,              // 'w'
            X,              // 'x'
            Y,              // 'y'
            Z,              // 'z'
            NUMLOCK,        // numlock key
            CAPSLOCK,       // capslock key
            SCROLLLOCK,     // scroll lock key
            RIGHTSHIFT,     // right shift key
            LEFTSHIFT,      // left shift key
            RIGHTCONTROL,   // right control key
            LEFTCONTROL,    // left control key
            RIGHTALT,       // right alt key
            LEFTALT,        // left alt key
            LEFTCOMMAND,    // left command key
            LEFTAPPLE,      // left command key
            LEFTWINDOWS,    // left windows key
            RIGHTCOMMAND,   // right command key
            RIGHTAPPLE,     // right command key
            RIGHTWINDOWS,   // right windows key
            ALTGR,          // alt gr key
            HELP,           // help key
            PRINT,          // print key
            SYSREQ,         // sys req key
            BREAK,          // break key
            MENU,           // menu key
            MOUSE0,         // left mouse button
            MOUSE1,         // right mouse button
            MOUSE2,         // middle mouse button
            MOUSE3,         // Additional mouse button
            MOUSE4,         // Additional mouse button
            MOUSE5,         // Additional mouse button
            MOUSE6,         // Additional mouse button
            JOYSTICKBUTTON0,
            JOYSTICKBUTTON1,
            JOYSTICKBUTTON2,
            JOYSTICKBUTTON3,
            JOYSTICKBUTTON4,
            JOYSTICKBUTTON5,
            JOYSTICKBUTTON6,
            JOYSTICKBUTTON7,
            JOYSTICKBUTTON8,
            JOYSTICKBUTTON9,
            JOYSTICKBUTTON10,
            JOYSTICKBUTTON11,
            JOYSTICKBUTTON12,
            JOYSTICKBUTTON13,
            JOYSTICKBUTTON14,
            JOYSTICKBUTTON15,
            JOYSTICKBUTTON16,
            JOYSTICKBUTTON17,
            JOYSTICKBUTTON18,
            JOYSTICKBUTTON19,
            JOYSTICK1BUTTON0,
            JOYSTICK1BUTTON1,
            JOYSTICK1BUTTON2,
            JOYSTICK1BUTTON3,
            JOYSTICK1BUTTON4,
            JOYSTICK1BUTTON5,
            JOYSTICK1BUTTON6,
            JOYSTICK1BUTTON7,
            JOYSTICK1BUTTON8,
            JOYSTICK1BUTTON9,
            JOYSTICK1BUTTON10,
            JOYSTICK1BUTTON11,
            JOYSTICK1BUTTON12,
            JOYSTICK1BUTTON13,
            JOYSTICK1BUTTON14,
            JOYSTICK1BUTTON15,
            JOYSTICK1BUTTON16,
            JOYSTICK1BUTTON17,
            JOYSTICK1BUTTON18,
            JOYSTICK1BUTTON19,
            JOYSTICK2BUTTON0,
            JOYSTICK2BUTTON1,
            JOYSTICK2BUTTON2,
            JOYSTICK2BUTTON3,
            JOYSTICK2BUTTON4,
            JOYSTICK2BUTTON5,
            JOYSTICK2BUTTON6,
            JOYSTICK2BUTTON7,
            JOYSTICK2BUTTON8,
            JOYSTICK2BUTTON9,
            JOYSTICK2BUTTON10,
            JOYSTICK2BUTTON11,
            JOYSTICK2BUTTON12,
            JOYSTICK2BUTTON13,
            JOYSTICK2BUTTON14,
            JOYSTICK2BUTTON15,
            JOYSTICK2BUTTON16,
            JOYSTICK2BUTTON17,
            JOYSTICK2BUTTON18,
            JOYSTICK2BUTTON19,
            JOYSTICK3BUTTON0,
            JOYSTICK3BUTTON1,
            JOYSTICK3BUTTON2,
            JOYSTICK3BUTTON3,
            JOYSTICK3BUTTON4,
            JOYSTICK3BUTTON5,
            JOYSTICK3BUTTON6,
            JOYSTICK3BUTTON7,
            JOYSTICK3BUTTON8,
            JOYSTICK3BUTTON9,
            JOYSTICK3BUTTON10,
            JOYSTICK3BUTTON11,
            JOYSTICK3BUTTON12,
            JOYSTICK3BUTTON13,
            JOYSTICK3BUTTON14,
            JOYSTICK3BUTTON15,
            JOYSTICK3BUTTON16,
            JOYSTICK3BUTTON17,
            JOYSTICK3BUTTON18,
            JOYSTICK3BUTTON19,
            JOYSTICK4BUTTON0,
            JOYSTICK4BUTTON1,
            JOYSTICK4BUTTON2,
            JOYSTICK4BUTTON3,
            JOYSTICK4BUTTON4,
            JOYSTICK4BUTTON5,
            JOYSTICK4BUTTON6,
            JOYSTICK4BUTTON7,
            JOYSTICK4BUTTON8,
            JOYSTICK4BUTTON9,
            JOYSTICK4BUTTON10,
            JOYSTICK4BUTTON11,
            JOYSTICK4BUTTON12,
            JOYSTICK4BUTTON13,
            JOYSTICK4BUTTON14,
            JOYSTICK4BUTTON15,
            JOYSTICK4BUTTON16,
            JOYSTICK4BUTTON17,
            JOYSTICK4BUTTON18,
            JOYSTICK4BUTTON19,
            JOYSTICK5BUTTON0,
            JOYSTICK5BUTTON1,
            JOYSTICK5BUTTON2,
            JOYSTICK5BUTTON3,
            JOYSTICK5BUTTON4,
            JOYSTICK5BUTTON5,
            JOYSTICK5BUTTON6,
            JOYSTICK5BUTTON7,
            JOYSTICK5BUTTON8,
            JOYSTICK5BUTTON9,
            JOYSTICK5BUTTON10,
            JOYSTICK5BUTTON11,
            JOYSTICK5BUTTON12,
            JOYSTICK5BUTTON13,
            JOYSTICK5BUTTON14,
            JOYSTICK5BUTTON15,
            JOYSTICK5BUTTON16,
            JOYSTICK5BUTTON17,
            JOYSTICK5BUTTON18,
            JOYSTICK5BUTTON19,
            JOYSTICK6BUTTON0,
            JOYSTICK6BUTTON1,
            JOYSTICK6BUTTON2,
            JOYSTICK6BUTTON3,
            JOYSTICK6BUTTON4,
            JOYSTICK6BUTTON5,
            JOYSTICK6BUTTON6,
            JOYSTICK6BUTTON7,
            JOYSTICK6BUTTON8,
            JOYSTICK6BUTTON9,
            JOYSTICK6BUTTON10,
            JOYSTICK6BUTTON11,
            JOYSTICK6BUTTON12,
            JOYSTICK6BUTTON13,
            JOYSTICK6BUTTON14,
            JOYSTICK6BUTTON15,
            JOYSTICK6BUTTON16,
            JOYSTICK6BUTTON17,
            JOYSTICK6BUTTON18,
            JOYSTICK6BUTTON19,
            JOYSTICK7BUTTON0,
            JOYSTICK7BUTTON1,
            JOYSTICK7BUTTON2,
            JOYSTICK7BUTTON3,
            JOYSTICK7BUTTON4,
            JOYSTICK7BUTTON5,
            JOYSTICK7BUTTON6,
            JOYSTICK7BUTTON7,
            JOYSTICK7BUTTON8,
            JOYSTICK7BUTTON9,
            JOYSTICK7BUTTON10,
            JOYSTICK7BUTTON11,
            JOYSTICK7BUTTON12,
            JOYSTICK7BUTTON13,
            JOYSTICK7BUTTON14,
            JOYSTICK7BUTTON15,
            JOYSTICK7BUTTON16,
            JOYSTICK7BUTTON17,
            JOYSTICK7BUTTON18,
            JOYSTICK7BUTTON19,
            JOYSTICK8BUTTON0,
            JOYSTICK8BUTTON1,
            JOYSTICK8BUTTON2,
            JOYSTICK8BUTTON3,
            JOYSTICK8BUTTON4,
            JOYSTICK8BUTTON5,
            JOYSTICK8BUTTON6,
            JOYSTICK8BUTTON7,
            JOYSTICK8BUTTON8,
            JOYSTICK8BUTTON9,
            JOYSTICK8BUTTON10,
            JOYSTICK8BUTTON11,
            JOYSTICK8BUTTON12,
            JOYSTICK8BUTTON13,
            JOYSTICK8BUTTON14,
            JOYSTICK8BUTTON15,
            JOYSTICK8BUTTON16,
            JOYSTICK8BUTTON17,
            JOYSTICK8BUTTON18,
            JOYSTICK8BUTTON19,

        };

        struct Color
        {
        public:
            explicit Color() {}

            Color(const float&r, const float&g, const float&b, const float&a)
                : r_(r),
                g_(g),
                b_(b),
                a_(a)
            {}

            ~Color() {}

            // static methods
        public:
            static std::shared_ptr<Color> Black() {
                return std::make_shared<Color>(0, 0, 0, 1);
            }

            static std::shared_ptr<Color> Blue() {
                return std::make_shared<Color>(0, 0, 1, 1);
            }

            static std::shared_ptr<Color> Clear() {
                return std::make_shared<Color>(0, 0, 0, 0);
            }

            static std::shared_ptr<Color> Cyan() {
                return std::make_shared<Color>(0, 1, 1, 1);
            }

            static std::shared_ptr<Color> Gray() {
                return std::make_shared<Color>(0.5, 0.5, 0.5, 1);
            }

            static std::shared_ptr<Color> Green() {
                return std::make_shared<Color>(0, 1, 0, 1);
            }

            static std::shared_ptr<Color> Magenta() {
                return std::make_shared<Color>(1, 0, 1, 1);
            }

            static std::shared_ptr<Color> Red() {
                return std::make_shared<Color>(1, 0, 0, 1);
            }

            static std::shared_ptr<Color> White() {
                return std::make_shared<Color>(1, 1, 1, 1);
            }

            static std::shared_ptr<Color> Yellow() {
                return std::make_shared<Color>(1, 0.92, 0.016, 1);
            }

            // properties
        public:
            inline auto get_r()const -> const float& { return r_; }

            inline auto set_r(const float& r) { r_ = r; }

            inline auto get_g()const -> const float& { return g_; }

            inline auto set_g(const float& g) { g_ = g; }

            inline auto get_b()const -> const float& { return b_; }

            inline auto set_b(const float& b) { b_ = b; }

            inline auto get_a()const -> const float& { return a_; }

            inline auto set_a(const float& a) { a_ = a; }

        private:
            float r_;
            float g_;
            float b_;
            float a_;

        };

        class Time {
        public:
            inline static auto get_capture_frame_rate() -> const int& { return capture_frame_rate_; }

            inline static auto set_capture_frame_rate(const int& rate) { capture_frame_rate_ = rate; }

            inline static auto get_delta_time() -> const float& { return delta_time_; }

            inline static auto set_delta_time(const float& time) { delta_time_ = time; }

            inline static auto get_fixed_delta_time() -> const float& { return fixed_delta_time_; }

            inline static auto set_fixed_delta_time(const float& time) { fixed_delta_time_ = time; }

            inline static auto get_fixed_time() -> const float& { return fixed_time_; }

            inline static auto set_fixed_time(const float& time) { fixed_time_ = time; }

            inline static auto get_fixed_unscaled_delta_time() -> const float& { return fixed_unscaled_delta_time_; }

            inline static auto set_fixed_unscaled_delta_time(const float& time) { fixed_unscaled_delta_time_ = time; }

            inline static auto get_fixed_unscaled_time() -> const float& { return fixed_unscaled_time_; }

            inline static auto set_fixed_unscaled_time(const float& time) { fixed_unscaled_time_ = time; }

            inline static auto get_frame_count() -> const int& { return frame_count_; }

            inline static auto set_frame_count(const int& count) { frame_count_ = count; }

            inline static auto get_in_fixed_time_step() -> const bool& { return in_fixed_time_step_; }

            inline static auto set_in_fixed_time_step(const bool& step) { in_fixed_time_step_ = step; }

            inline static auto get_maximum_delta_time() -> const float& { return maximum_delta_time_; }

            inline static auto set_maximum_delta_time(const float& time) { maximum_delta_time_ = time; }

            inline static auto get_maximum_particle_delta_time() -> const float& { return maximum_particle_delta_time_; }

            inline static auto set_maximum_particle_delta_time(const float& time) { maximum_particle_delta_time_ = time; }

            inline static auto get_realtime_since_startup() -> const float& { return realtime_since_startup_; }

            inline static auto set_realtime_since_startup(const float& time) { realtime_since_startup_ = time; }

            inline static auto get_smooth_delta_time() -> const float& { return smooth_delta_time_; }

            inline static auto set_smooth_delta_time(const float& time) { smooth_delta_time_ = time; }

            inline static auto get_time() -> const float& { return time_; }

            inline static auto set_time(const float& time) { time_ = time; }

            inline static auto get_time_scale() -> const float& { return time_scale_; }

            inline static auto set_time_scale(const float& scale) { time_scale_ = scale; }

            inline static auto get_time_since_level_load() -> const float& { return time_since_level_load_; }

            inline static auto set_time_since_level_load(const float& time) { time_since_level_load_ = time; }

            inline static auto get_unscaled_delta_time() -> const float& { return unscaled_delta_time_; }

            inline static auto set_unscaled_delta_time(const float& time) { unscaled_delta_time_ = time; }

            inline static auto get_unscaled_time() -> const float& { return unscaled_time_; }

            inline static auto set_unscaled_time(const float& time) { unscaled_time_ = time; }


        private:
            /// <summary>
            /// Slows game playback time to allow screenshots to be saved between frames.
            /// </summary>
            static int capture_frame_rate_;

            /// <summary>
            /// The time in seconds it took to complete the last frame (Read Only).
            /// </summary>
            static float delta_time_;

            /// <summary>
            /// The interval in seconds at which physics and other fixed frame rate updates (like MonoBehaviour's FixedUpdate) are performed.
            /// </summary>
            static float fixed_delta_time_;

            /// <summary>
            /// The time the latest FixedUpdate has started (Read Only). This is the time in seconds since the start of the game.
            /// </summary>
            static float fixed_time_;

            /// <summary>
            /// The timeScale-independent interval in seconds from the last fixed frame to the current one (Read Only).
            /// </summary>
            static float fixed_unscaled_delta_time_;

            /// <summary>
            /// The TimeScale-independant time the latest FixedUpdate has started (Read Only). This is the time in seconds since the start of the game.
            /// </summary>
            static float fixed_unscaled_time_;

            /// <summary>
            /// The total number of frames that have passed (Read Only).
            /// </summary>
            static int frame_count_;

            /// <summary>
            /// Returns true if called inside a fixed time step callback (like MonoBehaviour's FixedUpdate), otherwise returns false.
            /// </summary>
            static bool in_fixed_time_step_;

            /// <summary>
            /// The maximum time a frame can take. Physics and other fixed frame rate updates (like MonoBehaviour's FixedUpdate).
            /// </summary>
            static float maximum_delta_time_;

            /// <summary>
            /// The maximum time a frame can spend on particle updates. If the frame takes longer than this, then updates are split into multiple smaller updates.
            /// </summary>
            static float maximum_particle_delta_time_;

            /// <summary>
            /// The real time in seconds since the game started (Read Only).
            /// </summary>
            static float realtime_since_startup_;

            /// <summary>
            /// A smoothed out Time.deltaTime (Read Only).
            /// </summary>
            static float smooth_delta_time_;

            /// <summary>
            /// The time at the beginning of this frame (Read Only). This is the time in seconds since the start of the game.
            /// </summary>
            static float time_;

            /// <summary>
            /// The scale at which the time is passing. This can be used for slow motion effects.
            /// </summary>
            static float time_scale_;

            /// <summary>
            /// The time this frame has started (Read Only). This is the time in seconds since the last level has been loaded.
            /// </summary>
            static float time_since_level_load_;

            /// <summary>
            /// The timeScale-independent interval in seconds from the last frame to the current one (Read Only).
            /// </summary>
            static float unscaled_delta_time_;

            /// <summary>
            /// The timeScale-independant time for this frame (Read Only). This is the time in seconds since the start of the game.
            /// </summary>
            static float unscaled_time_;

        };

        enum class LightmapBakeType
        {
            REALTIME,
            BAKED,
            MIXED
        };

        enum class LightShadowCasterMode
        {
            DEFAULT,
            NONLIGHTMAPPEDONLY,
            EVERYTHING
        };

        enum class MixedLightingMode
        {
            INDIRECTONLY,
            SHADOWMASK,
            SUBTRACTIVE
        };

        enum class LightRenderMode
        {
            AUTO,
            FORCEPIXEL,
            FORCEVERTEX
        };

        enum class LightShadowResolution
        {
            FROMQUALITYSETTINGS,
            LOW,
            MEDIUM,
            HIGH,
            VERYHIGH
        };

        struct LightBakingOutput
        {
        public:
            inline auto get_is_baked() const -> const bool& { return is_baked_; }

            inline auto set_is_baked(const bool& is_baked) { is_baked_ = is_baked; }

            inline auto get_lightmap_bake_type() const -> const LightmapBakeType& { return lightmap_bake_type_; }

            inline auto set_lightmap_bake_type(const LightmapBakeType& type) { lightmap_bake_type_ = type; }

            inline auto get_mixed_lighting_mode() const -> const MixedLightingMode& { return mixed_lighting_mode_; }

            inline auto set_mixed_lighting_mode(const MixedLightingMode& mode) { mixed_lighting_mode_ = mode; }

            inline auto get_occlusion_mask_channel() const -> const int& { return occlusion_mask_channel_; }

            inline auto set_occlusion_mask_channel(const int& occlusion) { occlusion_mask_channel_ = occlusion; }

            inline auto get_probe_occlusion_light_index() const -> const int& { return probe_occlusion_light_index_; }

            inline auto set_probe_occlusion_light_index(const int& index) { probe_occlusion_light_index_ = index; }

        private:
            bool is_baked_;

            LightmapBakeType lightmap_bake_type_;

            MixedLightingMode mixed_lighting_mode_;

            int occlusion_mask_channel_;

            int probe_occlusion_light_index_;

        };

    }
}

