#include "Matrix4x3.h"
#include <memory>

// Умножаем матрицу на скаляр
void  POD_Math::Matrix4x3Mul(Matrix4x3& r, const Matrix4x3& md, const float mr)
{
	r._11 = md._11 * mr;  r._12 = md._12 * mr;  r._13 = md._13 * mr; 

	r._21 = md._21 * mr;  r._22 = md._22 * mr;  r._23 = md._23 * mr;  

	r._31 = md._31 * mr;  r._32 = md._32 * mr;  r._33 = md._33 * mr; 

	r._41 = md._41 * mr;  r._42 = md._42 * mr;  r._43 = md._43 * mr;
};


//Транспонирование 
void POD_Math::Matrix4x3Transpose(Matrix4x3& m)
{
	Matrix4x3 tmp=Matrix4x3();

	tmp._11 = m._11; tmp._12 = m._21; tmp._13 = m._31; tmp._21 = m._41;

	tmp._22 = m._12; tmp._23 = m._22; tmp._31 = m._32; tmp._32 = m._42; 

	tmp._33 = m._13; tmp._41 = m._23; tmp._42 = m._33; tmp._43 = m._43;

	m=tmp;
};

// Транспонированная матрица задается по адресу r
void POD_Math::Matrix4x3Transpose(Matrix4x3& r, const Matrix4x3& m)
{
	r._11 = m._11; r._12 = m._21; r._13 = m._31; r._21 = m._41;

	r._22 = m._12; r._23 = m._22; r._31 = m._32; r._32 = m._42; 

	r._33 = m._13; r._41 = m._23; r._42 = m._33; r._43 = m._43;
};


// Сложение
void POD_Math::Matrix4x3Add(POD_Math::Matrix4x3& r, const POD_Math::Matrix4x3& s0, const POD_Math::Matrix4x3& s1)
{
	r._11  = s0._11  + s1._11;  r._12 = s0._12 + s1._12;  r._13 = s0._13 + s1._13;

	r._21  = s0._21  + s1._21;  r._22 = s0._22 + s1._22;  r._23 = s0._23 + s1._23;

	r._31  = s0._31  + s1._31;  r._32 = s0._32 + s1._32;  r._33 = s0._33 + s1._33;

	r._41  = s0._41  + s1._41;  r._42 = s0._42 + s1._42;  r._43 = s0._43 + s1._43;
};



// Вычитание
void POD_Math::Matrix4x3Sub(POD_Math::Matrix4x3& r, const POD_Math::Matrix4x3& m, const POD_Math::Matrix4x3& s)
{
	r._11  = m._11  - s._11;  r._12 = m._12 - s._12;  r._13 = m._13 - s._13;

	r._21  = m._21  - s._21;  r._22 = m._22 - s._22;  r._23 = m._23 - s._23;

	r._31  = m._31  - s._31;  r._32 = m._32 - s._32;  r._33 = m._33 - s._33;

	r._41  = m._41  - s._41;  r._42 = m._42 - s._42;  r._43 = m._43 - s._43;
};


// Умножение
void POD_Math::Matrix4x3Mul(POD_Math::Matrix4x3& r, const POD_Math::Matrix4x3& md, const POD_Math::Matrix4x3& mr)
{/*
	r._11 = md._11 * mr._11 + md._12 * mr._21 + md._13 * mr._31;

	r._12 = md._11 * mr._12 + md._12 * mr._22 + md._13 * mr._32; 

	r._13 = md._11 * mr._13 + md._12 * mr._23 + md._13 * mr._33;


	r._21 = md._21 * mr._11 + md._22 * mr._21 + md._23 * mr._31;

	r._22 = md._21 * mr._12 + md._22 * mr._22 + md._23 * mr._32; 

	r._23 = md._21 * mr._13 + md._22 * mr._23 + md._23 * mr._33;


	r._31 = md._31 * mr._11 + md._32 * mr._21 + md._33 * mr._31;

	r._32 = md._31 * mr._12 + md._32 * mr._22 + md._33 * mr._32; 

	r._33 = md._31 * mr._13 + md._32 * mr._23 + md._33 * mr._33;


	r._41 = md._41 * mr._11 + md._42 * mr._21 + md._43 * mr._31 + mr._41;

	r._42 = md._41 * mr._12 + md._42 * mr._22 + md._43 * mr._32 + mr._42; 

	r._43 = md._41 * mr._13 + md._42 * mr._23 + md._43 * mr._33 + mr._43;*/


	r._11 = md._11 * mr._11 + md._12 * mr._21 + md._13 * mr._31; 
	r._12 = md._11 * mr._12 + md._12 * mr._22 + md._13 * mr._32;   
	r._13 = md._11 * mr._13 + md._12 * mr._23 + md._13 * mr._33;

	r._21 = md._21 * mr._11 + md._22 * mr._21 + md._23 * mr._31;
	r._22 = md._21 * mr._12 + md._22 * mr._22 + md._23 * mr._32;
	r._23 = md._21 * mr._13 + md._22 * mr._23 + md._23 * mr._33;

	r._31 = md._31 * mr._11 + md._32 * mr._21 + md._33 * mr._31;
	r._32 = md._31 * mr._12 + md._32 * mr._22 + md._33 * mr._32 ; 
	r._33 = md._31 * mr._13 + md._32 * mr._23 + md._33 * mr._33 ;

	r._41 = md._41 * mr._11 + md._42 * mr._21 + md._43 * mr._31 + mr._41;
	r._42 = md._41 * mr._12 + md._42 * mr._22 + md._43 * mr._32 + mr._42; 
	r._43 = md._41 * mr._13 + md._42 * mr._23 + md._43 * mr._33 + mr._43;

};


// Обнуление
void POD_Math::Matrix4x3Zero(POD_Math::Matrix4x3&i)
{
	memset(&i,0,sizeof(POD_Math::Matrix4x3));
};

// Идентитизация
void POD_Math::Matrix4x3Identity(POD_Math::Matrix4x3&i)
{
	i._11 = 1.0f; i._12 = 0.0f; i._13 = 0.0f;

	i._21 = 0.0f; i._22 = 1.0f; i._23 = 0.0f;

	i._31 = 0.0f; i._32 = 0.0f; i._33 = 1.0f;

	i._41 = 0.0f; i._42 = 0.0f; i._43 = 0.0f;
};