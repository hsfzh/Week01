#include "InputManager.h"
#include <windowsx.h>

bool InputManager::bDragging = false;
FVector InputManager::ptInitial = FVector::Zero;
FVector InputManager::ptCurrent = FVector::Zero;
FVector InputManager::change = FVector::Zero;
FVector InputManager::cameraInitialYaxis = FVector::Zero;
FVector InputManager::cameraInitialZaxis = FVector::Zero;

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
    case WM_LBUTTONDOWN:
        bDragging = true;
        ptInitial.X = GET_X_LPARAM(lParam);
        ptInitial.Y = GET_Y_LPARAM(lParam);
        cameraInitialYaxis = mainCamera.upDirection;
        cameraInitialZaxis = mainCamera.facing;
        break;
    case WM_LBUTTONUP:
        // ���� ��ư ���� �� �巡�� ����
        bDragging = false;
        break;
    case WM_MOUSEMOVE:
        if (bDragging) {
            // ���� ���콺 ��ġ ��������
            ptCurrent.X = GET_X_LPARAM(lParam);
            ptCurrent.Y = GET_Y_LPARAM(lParam);

            // ���� ��ġ�� ���� ��ġ ���� ����(����) ���
            float deltaX = ptCurrent.X - ptInitial.X;
            float deltaY = ptCurrent.Y - ptInitial.Y;

            change = ScreenToWorld(deltaX, deltaY);
            OnDrag(cameraInitialYaxis, cameraInitialZaxis, change);
        }
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

void InputManager::OnDrag(FVector yAxis, FVector zAxis, FVector angle)
{
    FVector xAxis = yAxis.Cross(zAxis);
    mainCamera.Rotate(FMatrix::RotationMatrix(xAxis, angle.Y));
    mainCamera.Rotate(FMatrix::RotationMatrix(yAxis, angle.X));
}

FVector InputManager::ScreenToWorld(float x, float y)
{
    float normalizedX = x / 1024.0f / 10.0f; // ���� ��ǥ ��ȯ (-1 ~ 1)
    float normalizedY = y / 1024.0f / 10.0f; // ���� ��ǥ ��ȯ (1 ~ -1)
    return FVector(normalizedX, normalizedY, 0.0f);
}
