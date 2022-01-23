#ifndef QUATERNION_H
#define QUATERNION_H

// Обычно скаляр идет первым, но для простоты записи ставим его последним //

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

// Нормализация
void  QuatNormalize(Quaternion&, const Quaternion&);

// Сферическая линейная интерполяция
void  QuatSlerp(Quaternion&, const Quaternion&, const Quaternion&, const float);

// Скалярное умножение
float QuatDotProduct(const Quaternion&, const Quaternion&);

//Сопряжение
void  QuatConjugate(Quaternion&, const Quaternion&);

// Умножение 
void  QuatMul(Quaternion&, const Quaternion&, const Quaternion&);

// Конвертирование кватерниона в матрицу 4х4
void  QuatToMatrix4x4(Matrix4x4&, const Quaternion&);

// Конвертирование кватерниона в матрицу 4х3
void  QuatToMatrix4x3(Matrix4x3&, const Quaternion&);

// Конвертирование матрицы 4х4 в кватернион
void  Matrix4x4ToQuat(Quaternion&, const Matrix4x4&);

// Конвертирование матрицы 4х3 в кватернион
void  Matrix4x3ToQuat(Quaternion&, const Matrix4x3&);

// Конвертирование оси и угла в кватернион
void  QuatAxis(Quaternion&,const Vector3&, const float); 

// Идентитизация
void QuatIdentity(Quaternion&);

// Обнуление
void QuatZero(Quaternion&);

};

#endif