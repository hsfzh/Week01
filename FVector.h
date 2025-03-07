#pragma once

struct FVector
{
	float X, Y, Z;
	FVector(float _x = 0, float _y = 0, float _z = 0) : X(_x), Y(_y), Z(_z) {}

	static const FVector Up;
	static const FVector Down;
	static const FVector Left;
	static const FVector Right;
	static const FVector Front;
	static const FVector Back;
	static const FVector Zero;

	bool operator==(const FVector& other);

	FVector& operator+=(const FVector& other);

	FVector& operator-=(const FVector& other);

	FVector operator*(float scalar) const;

	FVector operator+(const FVector& other) const;

	FVector operator-(const FVector& other) const;

	FVector operator/(float scalar) const;

	FVector Random(FVector min, FVector max);

	float Distance(const FVector& a);

	float Dot(const FVector& a);

	FVector Cross(const FVector& a);

	float Length();

	FVector Normalize();
};