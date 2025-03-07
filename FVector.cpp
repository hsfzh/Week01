#include "FVector.h"
#include <math.h>
#include <cstdlib>

const FVector FVector::Up = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::Down = FVector(0.0f, -1.0f, 0.0f);
const FVector FVector::Right = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::Left = FVector(-1.0f, 0.0f, 0.0f);
const FVector FVector::Front = FVector(0.0f, 0.0f, 1.0f);
const FVector FVector::Back = FVector(0.0f, 0.0f, -1.0f);
const FVector FVector::Zero = FVector();


bool FVector::operator==(const FVector& other)
{
	return X == other.X && Y == other.Y && Z == other.Z;
}

FVector& FVector::operator+=(const FVector& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	return *this;
}

FVector& FVector::operator-=(const FVector& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	return *this;
}

FVector& FVector::operator*=(const FVector& other)
{
	X *= other.X;
	Y *= other.Y;
	Z *= other.Z;
	return *this;
}

FVector FVector::operator*(float scalar) const
{
	return FVector(X * scalar, Y * scalar, Z * scalar);
}

FVector FVector::operator+(const FVector& other) const
{
	return FVector(X + other.X, Y + other.Y, Z + other.Z);
}

FVector FVector::operator-(const FVector& other) const
{
	return FVector(X - other.X, Y - other.Y, Z - other.Z);
}

FVector FVector::operator/(float scalar) const
{
	if (scalar == 0.0f)
	{
		return FVector(0.0f, 0.0f, 0.0f);
	}
	return FVector(X / scalar, Y / scalar, Z / scalar);
}

FVector FVector::Random(FVector min, FVector max)
{
	return FVector(
		min.X + static_cast<float>(rand()) / RAND_MAX * (max.X - min.X),
		min.Y + static_cast<float>(rand()) / RAND_MAX * (max.Y - min.Y),
		min.Z + static_cast<float>(rand()) / RAND_MAX * (max.Z - min.Z)
	);
}

float FVector::Distance(const FVector& a)
{
	float dx = a.X - X;
	float dy = a.Y - Y;
	float dz = a.Z - Z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

float FVector::Dot(const FVector& a)
{
	return a.X * X + a.Y * Y + a.Z * Z;
}

FVector FVector::Cross(const FVector& a)
{
	float crossX = Y * a.Z - Z * a.Y;
	float crossY = Z * a.X - X * a.Z;
	float crossZ = X * a.Y - Y * a.X;
	return FVector(crossX, crossY, crossZ);
}

float FVector::Length()
{
	return sqrtf(X * X + Y * Y + Z * Z);
}

FVector FVector::Normalize()
{
	float length = Length();
	if (length != 0) {
		X /= length;
		Y /= length;
		Z /= length;
	}
	return *this;
}

