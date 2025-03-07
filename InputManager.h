#pragma once
#include <windows.h>
#include "ImGui/imgui.h"
#include "imGui/imgui_impl_win32.h"
#include "UCamera.h"

extern UCamera mainCamera;

class InputManager {
public:
	static bool bDragging;
	static FVector ptInitial;
	static FVector ptCurrent;
	static FVector cameraInitialYaxis;
	static FVector cameraInitialZaxis;
	static FVector change;
public:
	static InputManager& Instance();
	LRESULT ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnKeyAPressed();
	void OnKeySPressed();
	void OnKeyDPressed();
	void OnKeyFPressed();
	void OnDrag(FVector yAxis, FVector zAxis, FVector angle);
	FVector ScreenToWorld(float x, float y);
};