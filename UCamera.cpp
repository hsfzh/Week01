#include "UCamera.h"
#include <math.h>



UCamera::UCamera(FVector pos, FVector targetpos, FVector up) : originalPos(pos), targetPos(targetpos)
{
	position = originalPos;
	up.Normalize();
	FMatrix translation = FMatrix::TranslationMatrix(pos);
	FVector forward = (targetPos - pos);
	facing = forward;
	forward.Normalize();
	if (pos.Y == targetPos.Y) {
		originalUp = up;
		upDirection = originalUp;
	}
	else {
		FVector axis = FVector(0, 0, 1).Cross(forward);
		axis.Normalize();
		FMatrix rotation = FMatrix::RotationMatrix(axis, acosf(FVector(0, 0, 1).Dot(forward)));
		originalUp = rotation * up;
		upDirection = originalUp;
	}
	viewMatrix = CalculateViewMatrix(pos, targetPos, upDirection);
	projectionMatrix = CalculateProjectionMatrix();
	float fovAngleY = 3.141592f / 4.0f;
	float aspectRatio = 1.0f;
	float nearZ = 0.1f;
	float farZ = 1000.0f;
	rotation = FVector::Zero;
}

FMatrix UCamera::CalculateViewMatrix(FVector pos, FVector targetpos, FVector up)
{
	FVector zAxis = (targetpos-pos).Normalize();
	facing = zAxis;
	FVector xAxis = up.Cross(zAxis).Normalize();
	FVector yAxis = zAxis.Cross(xAxis);
	FMatrix result = FMatrix::Identity;
	result.M[0][0] = xAxis.X; result.M[0][1] = xAxis.Y; result.M[0][2] = xAxis.Z;
	result.M[1][0] = yAxis.X; result.M[1][1] = yAxis.Y; result.M[1][2] = yAxis.Z;
	result.M[2][0] = zAxis.X; result.M[2][1] = zAxis.Y; result.M[2][2] = zAxis.Z;
	result.M[0][3] = -xAxis.Dot(pos);
	result.M[1][3] = -yAxis.Dot(pos);
	result.M[2][3] = -zAxis.Dot(pos);
	result.M[3][3] = 1.0f;
	return result;
}

FMatrix UCamera::CalculateProjectionMatrix(float fov, float aspect, float nearZ, float farZ)
{
	float x1 = 1.0f / (tan(fov / 2.0f) * aspect);
	float y2 = 1.0f / (tan(fov / 2.0f));
	float z3 = farZ / (farZ - nearZ);
	float w3 = -1.0f * (nearZ * farZ) / (farZ - nearZ);
	projectionMatrix = FMatrix(x1, 0.0f, 0.0f, 0.0f,
		0.0f, y2, 0.0f, 0.0f,
		0.0f, 0.0f, z3, 1.0f,
		0.0f, 0.0f, w3, 0.0f);
	return projectionMatrix;
}

void UCamera::Rotate(FMatrix rotationMatrix)
{
	//position = rotationMatrix * originalPos;
	facing = rotationMatrix * facing;
	targetPos = facing + position;
	upDirection = rotationMatrix * upDirection;
	upDirection.Normalize();
	viewMatrix = CalculateViewMatrix(position, targetPos, upDirection);
	rotation = GetRotation();
}

void UCamera::Translate(FVector offset)
{
	originalPos += offset;
	position += offset;
	targetPos = facing + position;
	viewMatrix = CalculateViewMatrix(position, targetPos, upDirection);
}

void UCamera::ChangeFOV(float fov)
{
	FOV = fov;
	projectionMatrix = CalculateProjectionMatrix(FOV);
}

void UCamera::SetPosition(FVector pos)
{
	originalPos = pos;
	position = originalPos;
	targetPos = facing + position;
	viewMatrix = CalculateViewMatrix(position, targetPos, upDirection);
}

FVector UCamera::GetRotation()
{
	FVector zAxis = facing.Normalize();
	FVector yAxis = upDirection;
	FVector xAxis = yAxis.Cross(zAxis).Normalize();
	FMatrix R(xAxis.X, yAxis.X, zAxis.X, 0.0f,
			  xAxis.Y, yAxis.Y, zAxis.Y, 0.0f,
			  xAxis.Z, yAxis.Y, zAxis.Z, 0.0f,
			  0.0f, 0.0f, 0.0f, 1.0f);
	R.Transpose();
	float angleY = asinf(R.M[0][2]);              // 피치
	float angleZ = atan2f(-R.M[0][1], R.M[0][0]);   // 요
	float angleX = atan2f(-R.M[1][2], R.M[2][2]);   // 롤
	return FVector(angleX, angleY, angleZ);
}


