#ifndef MATRIX4X3_H
#define MATRIX4X3_H

namespace POD_Math
{

#pragma pack(push,1)

struct Matrix4x3
{
	float _11, _12, _13;

	float _21, _22, _23;

	float _31, _32, _33;

	float _41, _42, _43;
};

#pragma pack(pop)

//��������� �� ������
void Matrix4x3Mul(Matrix4x3&, const Matrix4x3&, const float);

//����������������
void Matrix4x3Transpose(Matrix4x3&);
void Matrix4x3Transpose(Matrix4x3&, const Matrix4x3&);

//��������
void Matrix4x3Add(Matrix4x3&, const Matrix4x3&, const Matrix4x3&);

//���������
void Matrix4x3Sub(Matrix4x3&, const Matrix4x3&, const Matrix4x3&);

//���������
void Matrix4x3Mul(Matrix4x3&, const Matrix4x3&, const Matrix4x3&);

//���������
void Matrix4x3Zero(Matrix4x3&);

// �������������
void Matrix4x3Identity(Matrix4x3&);

};

#endif