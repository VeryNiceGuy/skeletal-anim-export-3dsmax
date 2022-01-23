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

// Ќормализаци¤
void  Vector3Normal(Vector3&);
void  Vector3Normal(Vector3&, const Vector3&);

// ”множение вектора на скал¤р
void  Vector3Mul(Vector3&,const Vector3&, const float);

 // ƒеление вектора на скал¤р
void  Vector3Div(Vector3&,const Vector3&, const float);

// —ложение векторов
void  Vector3Add(Vector3&,const Vector3&, const Vector3&);

// ¬ычитание векторов
void  Vector3Sub(Vector3&,const Vector3&, const Vector3&);

// ”множение вектора на п¤моугольную матрицу 4х3
void  Vector3Mul(Vector3&,const Vector3&,const Matrix4x3&);

// —кал¤рное умножение
float Vector3Dot(const Vector3&, const Vector3&);

// ¬екторное умножение
void  Vector3Cross(Vector3&, const Vector3&, const Vector3&);

// Ћинейна¤ интерпол¤ци¤
void  Vector3Lerp(Vector3&, Vector3&, const Vector3&, const float);

};

#endif