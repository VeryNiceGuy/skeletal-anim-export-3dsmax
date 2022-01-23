#ifndef VECTOR3_H
#define VECTOR3_H

namespace POD_Math
{

    struct Matrix4x3;

#pragma pack(push,1)

    struct Vector3
    {
	   float x,y,z;
    };

#pragma pack(pop)

// ������������
void  Vector3Normal(Vector3&);
void  Vector3Normal(Vector3&, const Vector3&);

// ��������� ������� �� ������
void  Vector3Mul(Vector3&,const Vector3&, const float);

 // ������� ������� �� ������
void  Vector3Div(Vector3&,const Vector3&, const float);

// �������� ��������
void  Vector3Add(Vector3&,const Vector3&, const Vector3&);

// ��������� ��������
void  Vector3Sub(Vector3&,const Vector3&, const Vector3&);

// ��������� ������� �� ������������ ������� 4�3
void  Vector3Mul(Vector3&,const Vector3&,const Matrix4x3&);

// ��������� ���������
float Vector3Dot(const Vector3&, const Vector3&);

// ��������� ���������
void  Vector3Cross(Vector3&, const Vector3&, const Vector3&);

// �������� ������������
void  Vector3Lerp(Vector3&, Vector3&, const Vector3&, const float);

};

#endif