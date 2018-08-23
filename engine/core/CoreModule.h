#pragma once

#include <glm/glm.hpp>

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

            void Set(const float& x, const float& y, const float& width, const float& height) {
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


    }
}

