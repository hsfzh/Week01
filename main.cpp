#include <windows.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include "URenderer.h"
#include "UCamera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Cube.h"
#include "FVector.h"
#include "FMatrix.h"
#include "InputManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"

float RadtoDeg(float a) {
	return a * 180.0f / PI;
}

float DegtoRad(float a) {
	return a * PI / 180.0f;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return InputManager::Instance().ProcessMessage(hWnd, message, wParam, lParam);
	}

	return 0;
}

//카메라 전역변수
UCamera mainCamera;

bool bIsOrthogonal = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WCHAR WindowClass[] = L"JungleWindowClass";

	WCHAR Title[] = L"Game Tech Lab";

	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	RegisterClassW(&wndclass);

	HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
		nullptr, nullptr, hInstance, nullptr);

	bool bIsExit = false;

	//카메라 초기화
	mainCamera = UCamera(FVector(0.0f, 0.0f, -2.0f), FVector(0.0f, 0.0f, 0.0f), FVector::Up);

	URenderer renderer;
	renderer.Create(hWnd);
	renderer.CreateShader();
	renderer.CreateConstantBuffer();

	float z = -5.0f;

	UINT numVerticesSphere = sizeof(sphere_vertices) / sizeof(FVertexSimple);
	ID3D11Buffer* vertexBufferSphere = renderer.CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));

	UINT numVerticesTriangle = sizeof(triangle_vertices) / sizeof(FVertexSimple);
	ID3D11Buffer* vertexBufferTriangle = renderer.CreateVertexBuffer(triangle_vertices, sizeof(triangle_vertices));

	UINT numVerticesCube = sizeof(cube_vertices) / sizeof(FVertexSimple);
	ID3D11Buffer* vertexBufferCube = renderer.CreateVertexBuffer(cube_vertices, sizeof(cube_vertices));

	FMatrix overallChange;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

	const int targetFPS = 30;
	const double targetFrameTime = 1000.0 / targetFPS;

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER startTime, endTime;
	double elapsedTime = 0.0;
	float angle = 0;
	float newFOV = 45;
	float cameraPosition[3] = { mainCamera.position.X, mainCamera.position.Y, mainCamera.position.Z };
	float cameraRotation[3] = { 0, 0, 0 };
	while (bIsExit == false)
	{
		QueryPerformanceCounter(&startTime);
		MSG msg;

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
			
		}
		angle += 0.01f;
		renderer.Prepare();
		renderer.PrepareShader();
		//mainCamera.Rotate(FMatrix::RotationMatrix(FVector(1, 0, 0), PI/4.0f));
		//mainCamera.Translate(FMatrix::TranslationMatrix(FVector(0, sin(angle), 0)));
		//mainCamera.ChangeFOV(PI/3.0f);
		FMatrix rotation = FMatrix::RotationMatrix(0, 0, 0);
		FMatrix translation = FMatrix::TranslationMatrix(FVector::Zero);
		FMatrix scale = FMatrix(0.1f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.1f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.1f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		scale.ChangeLastToOne();
		overallChange = translation * rotation * scale;
		FMatrix MVP = mainCamera.projectionMatrix.Transpose() * mainCamera.viewMatrix * overallChange;
		renderer.UpdateConstant(FConstants(MVP));
		renderer.RenderPrimitive(vertexBufferCube, numVerticesCube);
		//renderer.RenderPrimitive(vertexBufferTriangle, numVerticesTriangle);
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Jungle Property Window");
		/*
		ImGui::Text("Hello Jungle World!");
		ImGui::Text("camera position: %f, %f, %f", mainCamera.position.X, mainCamera.position.Y, mainCamera.position.Z);
		ImGui::Text("camera up direction: %f, %f, %f", mainCamera.upDirection.X, mainCamera.upDirection.Y, mainCamera.upDirection.Z);
		ImGui::Text("camera facing: %f, %f, %f", mainCamera.facing.X, mainCamera.facing.Y, mainCamera.facing.Z);
		ImGui::Text("camera looking at: %f, %f, %f", mainCamera.targetPos.X, mainCamera.targetPos.Y, mainCamera.targetPos.Z);
		ImGui::Text("view Matrix:\n%s", mainCamera.viewMatrix.PrintMatrix().c_str());
		ImGui::Text("is dragging: %s", InputManager::Instance().bDragging ? "true" : "false");
		ImGui::Text("click position: %f, %f, %f", InputManager::Instance().ptInitial.X, InputManager::Instance().ptInitial.Y, InputManager::Instance().ptInitial.Z);
		ImGui::Text("current position: %f, %f, %f", InputManager::Instance().ptCurrent.X, InputManager::Instance().ptCurrent.Y, InputManager::Instance().ptCurrent.Z);
		ImGui::Text("dragged distance: %f, %f, %f", InputManager::Instance().change.X, InputManager::Instance().change.Y, InputManager::Instance().change.Z);
		*/
		cameraPosition[0] = mainCamera.position.X;
		cameraPosition[1] = mainCamera.position.Y;
		cameraPosition[2] = mainCamera.position.Z;

		cameraRotation[0] = RadtoDeg(mainCamera.rotation.X);
		cameraRotation[1] = RadtoDeg(mainCamera.rotation.Y);
		cameraRotation[2] = RadtoDeg(mainCamera.rotation.Z);

		ImGui::Checkbox("Orthogonal", &bIsOrthogonal);
		ImGui::InputFloat("FOV", & newFOV, 0.0f, 0.0f, "%.3f");
		float fov = DegtoRad(newFOV);
		if (fov != mainCamera.FOV) {
			mainCamera.ChangeFOV(fov);
		}
		ImGui::InputFloat3("Camera Location", cameraPosition, "%.3f");
		FVector newPos(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
		if (newPos != mainCamera.position) {
			mainCamera.SetPosition(newPos);
		}
		ImGui::InputFloat3("Camera Rotation", cameraRotation, "%.3f");
		FVector newRot(DegtoRad(cameraRotation[0]), DegtoRad(cameraRotation[1]), DegtoRad(cameraRotation[2]));
		if (newRot != mainCamera.rotation) {
			mainCamera.Rotate(FMatrix::RotationMatrix(newRot.X - mainCamera.rotation.X, newRot.Y - mainCamera.rotation.Y, newRot.Z - mainCamera.rotation.Z));
			mainCamera.rotation = newRot;
		}
		ImGui::Text("rotation matrix:\n%s", FMatrix::RotationMatrix(newRot.X, newRot.Y, newRot.Z).PrintMatrix().c_str());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		renderer.SwapBuffer();

		do {
			Sleep(0);
			QueryPerformanceCounter(&endTime);
			elapsedTime = (endTime.QuadPart - startTime.QuadPart) * 1000.0 / frequency.QuadPart;
		
		} while (elapsedTime < targetFrameTime);

	}
	renderer.ReleaseVertexBuffer(vertexBufferSphere);
	renderer.ReleaseVertexBuffer(vertexBufferCube);
	renderer.ReleaseVertexBuffer(vertexBufferTriangle);
	renderer.ReleaseConstantBuffer();
	renderer.ReleaseShader();
	renderer.Release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return 0;
}