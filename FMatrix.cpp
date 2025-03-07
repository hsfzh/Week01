#include "FMatrix.h"
#include <math.h>
#include <cstdlib>
#include <string>
#include <iostream>

FMatrix::FMatrix()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            M[i][j] = 0.0f;
        }
    }
}

FMatrix::FMatrix(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4, float z1, float z2, float z3, float z4, float w1, float w2, float w3, float w4)
{
    M[0][0] = x1; M[0][1] = x2; M[0][2] = x3; M[0][3] = x4;
    M[1][0] = y1; M[1][1] = y2; M[1][2] = y3; M[1][3] = y4;
    M[2][0] = z1; M[2][1] = z2; M[2][2] = z3; M[2][3] = z4;
    M[3][0] = w1; M[3][1] = w2; M[3][2] = w3; M[3][3] = w4;
}

FMatrix FMatrix::operator*(float scalar) const
{
    FMatrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.M[i][j] = M[i][j]*scalar;
        }
    }
    return result;
}

FVector FMatrix::operator*(FVector& a) const
{
    FVector result = FVector();
    float x = M[0][0] * a.X + M[0][1] * a.Y + M[0][2] * a.Z + M[0][3];
    float y = M[1][0] * a.X + M[1][1] * a.Y + M[1][2] * a.Z + M[1][3];
    float z = M[2][0] * a.X + M[2][1] * a.Y + M[2][2] * a.Z + M[2][3];
    return FVector(x, y, z);
}

FMatrix FMatrix::operator*(FMatrix& a) const
{
    FMatrix result = FMatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.M[i][j] += M[i][k] * a.M[k][j];
            }
        }
    }
    return result;
}

FMatrix FMatrix::Transpose()
{
    FMatrix transposeMatrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transposeMatrix.M[i][j] = M[j][i];
        }
    }
    return transposeMatrix;
}

const FMatrix FMatrix::Identity = FMatrix(1.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f);

FMatrix FMatrix::RotationMatrix(const FVector& axis, float angle)
{
    // 회전축을 정규화
    FVector nAxis = axis;
    nAxis.Normalize();

    float cosA = cos(angle);
    float sinA = sin(angle);
    float oneMinusCosA = 1.0f - cosA;

    // 미리 계산
    float xx = nAxis.X * nAxis.X;
    float yy = nAxis.Y * nAxis.Y;
    float zz = nAxis.Z * nAxis.Z;
    float xy = nAxis.X * nAxis.Y;
    float xz = nAxis.X * nAxis.Z;
    float yz = nAxis.Y * nAxis.Z;

    return FMatrix(
        cosA + xx * oneMinusCosA, xy * oneMinusCosA - nAxis.Z * sinA, xz * oneMinusCosA + nAxis.Y * sinA, 0.0f,
        xy * oneMinusCosA + nAxis.Z * sinA, cosA + yy * oneMinusCosA, yz * oneMinusCosA - nAxis.X * sinA, 0.0f,
        xz * oneMinusCosA - nAxis.Y * sinA, yz * oneMinusCosA + nAxis.X * sinA, cosA + zz * oneMinusCosA, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

FMatrix FMatrix::RotationMatrix(float angleX, float angleY, float angleZ)
{
    FMatrix xRotation = RotationMatrix(FVector(1, 0, 0), angleX);
    FMatrix yRotation = RotationMatrix(FVector(0, 1, 0), angleY);
    FMatrix zRotation = RotationMatrix(FVector(0, 0, 1), angleZ);
    if (angleX == 0) {
        xRotation = FMatrix::Identity;
    }
    if (angleY == 0) {
        yRotation = FMatrix::Identity;
    }
    if (angleZ == 0) {
        zRotation = FMatrix::Identity;
    }
    FMatrix rotationMatrix = xRotation * yRotation * zRotation;
    return rotationMatrix;
}

FMatrix FMatrix::TranslationMatrix(FVector translation)
{
    FMatrix translationMatrix = FMatrix(1.0f, 0.0f, 0.0f, translation.X,
                                        0.0f, 1.0f, 0.0f, translation.Y,
                                        0.0f, 0.0f, 1.0f, translation.Z,
                                        0.0f, 0.0f, 0.0f, 1.0f);
    return translationMatrix;
}

void FMatrix::ChangeLastToOne()
{
    M[3][3] = 1.0f;
}

std::string FMatrix::PrintMatrix()
{
    std::string result = "";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result += std::to_string(M[i][j]) + ", ";
        }
        result += "\n";
    }
    return result;
}
