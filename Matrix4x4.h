#ifndef MATRIX4X4_H
#define MATRIX4X4_H

namespace POD_Math
{

#pragma pack(push,1)

struct Matrix4x4
{
	float _11, _12, _13, _14;

	float _21, _22, _23, _24;

	float _31, _32, _33, _34;

	float _41, _42, _43, _44;
};

#pragma pack(pop)

// ��������� �� �������
void  Matrix4x4Mul(Matrix4x4&, const Matrix4x4&, const float);

// ����������������
void  Matrix4x4Transpose(Matrix4x4&);
void  Matrix4x4Transpose(Matrix4x4& r, const Matrix4x4&);  

// ��������
void  Matrix4x4Add(Matrix4x4&, const Matrix4x4&, const Matrix4x4&);

// ���������
void  Matrix4x4Sub(Matrix4x4&, const Matrix4x4&, const Matrix4x4&);

// ���������
void  Matrix4x4Mul(Matrix4x4&, const Matrix4x4&, const Matrix4x4&);

// ���������
void Matrix4x4Zero(Matrix4x4&);

// �������������
void  Matrix4x4Identity(Matrix4x4&);

// ����
float Matrix4x4Trace(const Matrix4x4&);

// ������� ��������� ������� ������������� ��������
void CreatePerspectiveFovLH(Matrix4x4&, float, float, float, float);

};


#endif