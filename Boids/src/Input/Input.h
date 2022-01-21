#pragma once
#include <GLFW/glfw3.h>
#include "Math/vec2.h"

namespace Boids
{
	enum EKeyCode : uint16_t
	{
	BOIDS_KEY_UNKNOWN = GLFW_KEY_UNKNOWN,

	
	BOIDS_KEY_SPACE = GLFW_KEY_SPACE,
	
	BOIDS_KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE  /* ' */,
	
	BOIDS_KEY_COMMA = GLFW_KEY_COMMA  /* , */,
	
	BOIDS_KEY_MINUS = GLFW_KEY_MINUS   /* - */,
	
	BOIDS_KEY_PERIOD = GLFW_KEY_PERIOD   /* . */,
	
	BOIDS_KEY_SLASH = GLFW_KEY_SLASH   /* / */,
	
	BOIDS_KEY_0 = GLFW_KEY_0,
	
	BOIDS_KEY_1 = GLFW_KEY_1,
	
	BOIDS_KEY_2 = GLFW_KEY_2,
	
	BOIDS_KEY_3 = GLFW_KEY_3,
	
	BOIDS_KEY_4 = GLFW_KEY_4,
	
	BOIDS_KEY_5 = GLFW_KEY_5,
	
	BOIDS_KEY_6 = GLFW_KEY_6,
	
	BOIDS_KEY_7 = GLFW_KEY_7,
	
	BOIDS_KEY_8 = GLFW_KEY_8,
	
	BOIDS_KEY_9 = GLFW_KEY_9,
	
	BOIDS_KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
	
	BOIDS_KEY_EQUAL = GLFW_KEY_EQUAL,
	
	BOIDS_KEY_A = GLFW_KEY_A,
	
	BOIDS_KEY_B = GLFW_KEY_B,
	
	BOIDS_KEY_C = GLFW_KEY_C,
	

	BOIDS_KEY_D = GLFW_KEY_D,
	
	BOIDS_KEY_E = GLFW_KEY_E,
	
	BOIDS_KEY_F = GLFW_KEY_F,
	
	BOIDS_KEY_G = GLFW_KEY_G,
	
	BOIDS_KEY_H = GLFW_KEY_H,
	
	BOIDS_KEY_I = GLFW_KEY_I,
	
	BOIDS_KEY_J = GLFW_KEY_J,
	
	BOIDS_KEY_K = GLFW_KEY_K,
	
	BOIDS_KEY_L = GLFW_KEY_L,
	
	BOIDS_KEY_M = GLFW_KEY_M,
	
	BOIDS_KEY_N = GLFW_KEY_N,
	
	BOIDS_KEY_O = GLFW_KEY_O,
	
	BOIDS_KEY_P = GLFW_KEY_P,
	
	BOIDS_KEY_Q = GLFW_KEY_Q,
	
	BOIDS_KEY_R = GLFW_KEY_R,
	
	BOIDS_KEY_S = GLFW_KEY_S,
	
	BOIDS_KEY_T = GLFW_KEY_T,
	
	BOIDS_KEY_U = GLFW_KEY_U,
	
	BOIDS_KEY_V = GLFW_KEY_V,
	
	BOIDS_KEY_W = GLFW_KEY_W,
	
	BOIDS_KEY_X = GLFW_KEY_X,
	
	BOIDS_KEY_Y = GLFW_KEY_Y,
	
	BOIDS_KEY_Z = GLFW_KEY_Z,
	
	BOIDS_KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
	
	BOIDS_KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
	
	BOIDS_KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
	
	BOIDS_KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
	
	BOIDS_KEY_WORLD_1 = GLFW_KEY_WORLD_1,
	
	BOIDS_KEY_WORLD_2 = GLFW_KEY_WORLD_2,
	
	BOIDS_KEY_ESCAPE = GLFW_KEY_ESCAPE,
	
	BOIDS_KEY_ENTER = GLFW_KEY_ENTER,
	
	BOIDS_KEY_TAB = GLFW_KEY_TAB,
	
	BOIDS_KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
	
	BOIDS_KEY_INSERT = GLFW_KEY_INSERT,
	
	BOIDS_KEY_DELETE = GLFW_KEY_DELETE,
	
	BOIDS_KEY_RIGHT = GLFW_KEY_RIGHT,
	
	BOIDS_KEY_LEFT = GLFW_KEY_LEFT,
	
	BOIDS_KEY_DOWN = GLFW_KEY_DOWN,
	
	BOIDS_KEY_UP = GLFW_KEY_UP,
	
	BOIDS_KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
	
	BOIDS_KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
	
	BOIDS_KEY_HOME = GLFW_KEY_HOME,
	
	BOIDS_KEY_END = GLFW_KEY_END,
	
	BOIDS_KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
	
	BOIDS_KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
	
	BOIDS_KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
	
	BOIDS_KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
	
	BOIDS_KEY_PAUSE = GLFW_KEY_PAUSE,
	
	BOIDS_KEY_F1 = GLFW_KEY_F1,
	
	BOIDS_KEY_F2 = GLFW_KEY_F2,
	
	
	BOIDS_KEY_F3 = GLFW_KEY_F3,
	
	BOIDS_KEY_F4 = GLFW_KEY_F4,
	
	BOIDS_KEY_F5 = GLFW_KEY_F5,
	
	BOIDS_KEY_F6 = GLFW_KEY_F6,
	
	BOIDS_KEY_F7 = GLFW_KEY_F7,
	
	BOIDS_KEY_F8 = GLFW_KEY_F8,
	
	BOIDS_KEY_F9 = GLFW_KEY_F9,
	
	BOIDS_KEY_F10 = GLFW_KEY_F10,
	
	BOIDS_KEY_F11 = GLFW_KEY_F11,
	
	BOIDS_KEY_F12 = GLFW_KEY_F12,
	
	BOIDS_KEY_F13 = GLFW_KEY_F13,
	
	BOIDS_KEY_F14 = GLFW_KEY_F14,
	
	BOIDS_KEY_F15 = GLFW_KEY_F15,
	
	BOIDS_KEY_F16 = GLFW_KEY_F16,
	
	BOIDS_KEY_F17 = GLFW_KEY_F17,
	
	BOIDS_KEY_F18 = GLFW_KEY_F18,
	
	BOIDS_KEY_F19 = GLFW_KEY_F19,
	
	BOIDS_KEY_F20 = GLFW_KEY_F20,
	
	BOIDS_KEY_F21 = GLFW_KEY_F21,
	
	BOIDS_KEY_F22 = GLFW_KEY_F22,
	
	BOIDS_KEY_F23 = GLFW_KEY_F23,
	
	BOIDS_KEY_F24 = GLFW_KEY_F24,
	
	BOIDS_KEY_F25 = GLFW_KEY_F25,
	
	BOIDS_KEY_KP_0 = GLFW_KEY_KP_0,
	
	BOIDS_KEY_KP_1 = GLFW_KEY_KP_1,
	
	BOIDS_KEY_KP_2 = GLFW_KEY_KP_2,
	
	BOIDS_KEY_KP_3 = GLFW_KEY_KP_3,
	
	BOIDS_KEY_KP_4 = GLFW_KEY_KP_4,
	
	BOIDS_KEY_KP_5 = GLFW_KEY_KP_5,
	
	BOIDS_KEY_KP_6 = GLFW_KEY_KP_6,
	
	BOIDS_KEY_KP_7 = GLFW_KEY_KP_7,
	
	BOIDS_KEY_KP_8 = GLFW_KEY_KP_8,
	
	BOIDS_KEY_KP_9 = GLFW_KEY_KP_9,
	
	BOIDS_KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
	
	BOIDS_KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
	
	BOIDS_KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
	
	BOIDS_KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
	
	BOIDS_KEY_KP_ADD = GLFW_KEY_KP_ADD,
	
	BOIDS_KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
	
	BOIDS_KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
	
	BOIDS_KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
	
	BOIDS_KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
	
	BOIDS_KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
	
	BOIDS_KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
	
	BOIDS_KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
	
	BOIDS_KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
	
	BOIDS_KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
	
	BOIDS_KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
	
	BOIDS_KEY_MENU = GLFW_KEY_MENU,
	
	BOIDS_KEY_LAST = BOIDS_KEY_MENU
	};

	enum MouseButtonsCode : uint8_t
	{
		BOIDS_MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
		BOIDS_MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
		BOIDS_MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
		BOIDS_MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
		BOIDS_MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
		BOIDS_MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
		BOIDS_MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
		BOIDS_MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,
		BOIDS_MOUSE_BUTTON_LAST = GLFW_MOUSE_BUTTON_LAST,
		BOIDS_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
		BOIDS_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		BOIDS_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
	};
	
	class Input
	{
	public:
		static bool IsKeyPressed(EKeyCode kc);
		static bool IsMouseButtonPressed(MouseButtonsCode mb);
		static void HideAndLockCursor(bool cond);
		static vec2 GetMousePosition();
		static void SetCursorPosition(int x, int y);
	};
	
}