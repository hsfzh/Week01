#include "InputManager.h"

InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

LRESULT InputManager::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_KEYDOWN:
        if (wParam == 'A') {
            OnKeyAPressed();
        }
        if (wParam == 'S') {
            OnKeySPressed();
        }
        if (wParam == 'D') {
            OnKeyDPressed();
        }
        if (wParam == 'F') {
            OnKeyFPressed();
        }
        break;
    case WM_KEYUP:
        // 예: 키가 떼어졌을 때의 처리
        break;
    case WM_MOUSEMOVE:
        // 예: 마우스 이동 이벤트 처리
        break;
        // 필요한 다른 메시지 케이스를 추가하세요.
    default:
        break;
    }
    // 추가 처리가 끝난 후 기본 메시지 처리가 필요하다면 DefWindowProc 호출
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void InputManager::OnKeyAPressed()
{
    mainCamera.Translate(FVector(-0.1f, 0, 0));
}

void InputManager::OnKeySPressed()
{
    mainCamera.Translate(FVector(0, 0, -0.1f));
}

void InputManager::OnKeyDPressed()
{
    mainCamera.Translate(FVector(0.1f, 0, 0));
}

void InputManager::OnKeyFPressed()
{
    mainCamera.Translate(FVector(0, 0, 0.1f));
}
