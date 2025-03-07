#pragma once
#include "FVector.h"
#include <string>


static const float PI = 3.14159265358979323846f;

struct FMatrix {
	float M[4][4];
	FMatrix();
	FMatrix(float x1, float x2, float x3, float x4,
			float y1, float y2, float y3, float y4,
			float z1, float z2, float z3, float z4,
			float w1, float w2, float w3, float w4);
	static const FMatrix Identity;
	FMatrix operator*(float scalar) const;
	FVector operator*(FVector& a) const;
	FMatrix operator*(FMatrix& a) const;
	FMatrix Transpose();
	static FMatrix RotationMatrix(float angleX = 0, float angleY = 0, float angleZ = 0);
	static FMatrix RotationMatrix(const FVector& axis, float angle);
	static FMatrix TranslationMatrix(FVector translation);
	void ChangeLastToOne();
	std::string PrintMatrix();
};