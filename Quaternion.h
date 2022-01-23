#ifndef QUATERNION_H
#define QUATERNION_H

// ������ ������ ���� ������, �� ��� �������� ������ ������ ��� ��������� //

namespace POD_Math
{

	struct Matrix4x4;
	struct Matrix4x3;
	struct Vector3;

#pragma pack(push,1)

struct Quaternion
{
   float x,y,z,w;
};

#pragma pack(pop)

void  QuatMul(Vector3&, const Quaternion&, const Vector3&);

// ������������
void  QuatNormalize(Quaternion&, const Quaternion&);

// ����������� �������� ������������
void  QuatSlerp(Quaternion&, const Quaternion&, const Quaternion&, const float);

// ��������� ���������
float QuatDotProduct(const Quaternion&, const Quaternion&);

//����������
void  QuatConjugate(Quaternion&, const Quaternion&);

// ��������� 
void  QuatMul(Quaternion&, const Quaternion&, const Quaternion&);

// ��������������� ����������� � ������� 4�4
void  QuatToMatrix4x4(Matrix4x4&, const Quaternion&);

// ��������������� ����������� � ������� 4�3
void  QuatToMatrix4x3(Matrix4x3&, const Quaternion&);

// ��������������� ������� 4�4 � ����������
void  Matrix4x4ToQuat(Quaternion&, const Matrix4x4&);

// ��������������� ������� 4�3 � ����������
void  Matrix4x3ToQuat(Quaternion&, const Matrix4x3&);

// ��������������� ��� � ���� � ����������
void  QuatAxis(Quaternion&,const Vector3&, const float); 

// �������������
void QuatIdentity(Quaternion&);

// ���������
void QuatZero(Quaternion&);

};

#endif