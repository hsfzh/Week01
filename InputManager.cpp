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
        // ��: Ű�� �������� ���� ó��
        break;
    case WM_MOUSEMOVE:
        // ��: ���콺 �̵� �̺�Ʈ ó��
        break;
        // �ʿ��� �ٸ� �޽��� ���̽��� �߰��ϼ���.
    default:
        break;
    }
    // �߰� ó���� ���� �� �⺻ �޽��� ó���� �ʿ��ϴٸ� DefWindowProc ȣ��
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
