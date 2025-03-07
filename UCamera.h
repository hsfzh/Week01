#pragma once
#include "FVector.h"
#include "FMatrix.h"

class UCamera {
public: 
	FVector originalPos;
	FVector position;
	FVector targetPos;
	FVector originalUp;
	FVector upDirection;
	FVector facing;
	FVector rotation;
	float FOV;
	FMatrix viewMatrix;
	FMatrix projectionMatrix;

public:
	UCamera(FVector pos = FVector::Zero, FVector targetpos = FVector::Zero, FVector up = FVector::Zero);
	FMatrix CalculateViewMatrix(FVector pos, FVector targetpos, FVector up);
	FMatrix CalculateProjectionMatrix(float fov = PI/4.0f, float aspect = 1.0f, float nearZ = 0.1f, float farZ=1000.0f);
	void Rotate(FMatrix rotationMatrix);
	void Translate(FVector offset);
	void ChangeFOV(float fov);
	void SetPosition(FVector pos);
	FVector GetRotation();
};