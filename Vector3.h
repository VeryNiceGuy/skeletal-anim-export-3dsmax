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

// Нормализация
void  Vector3Normal(Vector3&);
void  Vector3Normal(Vector3&, const Vector3&);

// Умножение вектора на скаляр
void  Vector3Mul(Vector3&,const Vector3&, const float);

 // Деление вектора на скаляр
void  Vector3Div(Vector3&,const Vector3&, const float);

// Сложение векторов
void  Vector3Add(Vector3&,const Vector3&, const Vector3&);

// Вычитание векторов
void  Vector3Sub(Vector3&,const Vector3&, const Vector3&);

// Умножение вектора на пямоугольную матрицу 4х3
void  Vector3Mul(Vector3&,const Vector3&,const Matrix4x3&);

// Скалярное умножение
float Vector3Dot(const Vector3&, const Vector3&);

// Векторное умножение
void  Vector3Cross(Vector3&, const Vector3&, const Vector3&);

// Линейная интерполяция
void  Vector3Lerp(Vector3&, Vector3&, const Vector3&, const float);

};

#endif