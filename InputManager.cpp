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
        // 예: 키가 떼어졌을 때의 처리
        break;
    case WM_LBUTTONDOWN:
        bDragging = true;
        ptInitial.X = GET_X_LPARAM(lParam);
        ptInitial.Y = GET_Y_LPARAM(lParam);
        cameraInitialYaxis = mainCamera.upDirection;
        cameraInitialZaxis = mainCamera.facing;
        break;
    case WM_LBUTTONUP:
        // 왼쪽 버튼 해제 시 드래그 종료
        bDragging = false;
        break;
    case WM_MOUSEMOVE:
        if (bDragging) {
            // 현재 마우스 위치 가져오기
            ptCurrent.X = GET_X_LPARAM(lParam);
            ptCurrent.Y = GET_Y_LPARAM(lParam);

            // 시작 위치와 현재 위치 간의 벡터(차이) 계산
            float deltaX = ptCurrent.X - ptInitial.X;
            float deltaY = ptCurrent.Y - ptInitial.Y;

            change = ScreenToWorld(deltaX, deltaY);
            OnDrag(cameraInitialYaxis, cameraInitialZaxis, change);
        }
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

void InputManager::OnDrag(FVector yAxis, FVector zAxis, FVector angle)
{
    FVector xAxis = yAxis.Cross(zAxis);
    mainCamera.Rotate(FMatrix::RotationMatrix(xAxis, angle.Y));
    mainCamera.Rotate(FMatrix::RotationMatrix(yAxis, angle.X));
}

FVector InputManager::ScreenToWorld(float x, float y)
{
    float normalizedX = x / 1024.0f / 10.0f; // 가로 좌표 변환 (-1 ~ 1)
    float normalizedY = y / 1024.0f / 10.0f; // 세로 좌표 변환 (1 ~ -1)
    return FVector(normalizedX, normalizedY, 0.0f);
}
