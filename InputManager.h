#pragma once
#include <windows.h>
#include "ImGui/imgui.h"
#include "imGui/imgui_impl_win32.h"
#include "UCamera.h"

extern UCamera mainCamera;

class InputManager {
public:
	
public:
	static InputManager& Instance();
	LRESULT ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnKeyAPressed();
	void OnKeySPressed();
	void OnKeyDPressed();
	void OnKeyFPressed();
};