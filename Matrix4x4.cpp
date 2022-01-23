#include "Matrix4x4.h"
#include <memory>

//Умножаем на скаляр
void  POD_Math::Matrix4x4Mul(POD_Math::Matrix4x4& r, const POD_Math::Matrix4x4& md, const float mr)
{
	r._11 = md._11 * mr;  r._12 = md._12 * mr;  r._13 = md._13 * mr;  r._14= md._14 * mr;

	r._21 = md._21 * mr;  r._22 = md._22 * mr;  r._23 = md._23 * mr;  r._24= md._24 * mr; 

	r._31 = md._31 * mr;  r._32 = md._32 * mr;  r._33 = md._33 * mr;  r._34= md._34 * mr;

	r._41 = md._41 * mr;  r._42 = md._42 * mr;  r._43 = md._43 * mr;  r._44= md._44 * mr;
}; 

// Транспонирование
void POD_Math::Matrix4x4Transpose(POD_Math::Matrix4x4& m)                                                                  
{                     
	POD_Math::Matrix4x4 tmp = POD_Math::Matrix4x4();

	tmp._11 = m._11;  tmp._12 = m._21;  tmp._13 = m._31 ;  tmp._14 = m._41;

	tmp._21 = m._12;  tmp._22 = m._22;  tmp._23 = m._32 ;  tmp._24 = m._42; 

	tmp._31 = m._13;  tmp._32 = m._23;  tmp._33 = m._33 ;  tmp._34 = m._43;

	tmp._41 = m._14;  tmp._42 = m._24;  tmp._43 = m._34 ;  tmp._44 = m._44;

	m=tmp;
};                         

// Транспонирование
void POD_Math::Matrix4x4Transpose(POD_Math::Matrix4x4& r, const POD_Math::Matrix4x4& m)                                                                  
{                     

	r._11 = m._11;  r._12 = m._21;  r._13 = m._31 ;  r._14 = m._41;

	r._21 = m._12;  r._22 = m._22;  r._23 = m._32 ;  r._24 = m._42; 

	r._31 = m._13;  r._32 = m._23;  r._33 = m._33 ;  r._34 = m._43;

	r._41 = m._14;  r._42 = m._24;  r._43 = m._34 ;  r._44 = m._44;

}; 

// Сложение
void POD_Math::Matrix4x4Add(POD_Math::Matrix4x4& r, const POD_Math::Matrix4x4& s0, const POD_Math::Matrix4x4& s1)
{
	r._11  = s0._11  + s1._11;  r._12 = s0._12 + s1._12;  r._13 = s0._13 + s1._13;  r._14 = s0._14 + s1._14;

	r._21  = s0._21  + s1._21;  r._22 = s0._22 + s1._22;  r._23 = s0._23 + s1._23;  r._24 = s0._24 + s1._24;

	r._31  = s0._31  + s1._31;  r._32 = s0._32 + s1._32;  r._33 = s0._33 + s1._33;  r._34 = s0._34 + s1._34;

	r._41  = s0._41  + s1._41;  r._42 = s0._42 + s1._42;  r._43 = s0._43 + s1._43;  r._44 = s0._44 + s1._44;
};

// Вычитание
void POD_Math::Matrix4x4Sub(POD_Math::Matrix4x4& r, const POD_Math::Matrix4x4& m, const POD_Math::Matrix4x4& s)
{
	r._11  = m._11  - s._11;  r._12 = m._12 - s._12;  r._13 = m._13 - s._13;  r._14 = m._14 - s._14;

	r._21  = m._21  - s._21;  r._22 = m._22 - s._22;  r._23 = m._23 - s._23;  r._24 = m._24 - s._24;

	r._31  = m._31  - s._31;  r._32 = m._32 - s._32;  r._33 = m._33 - s._33;  r._34 = m._34 - s._34;

	r._41  = m._41  - s._41;  r._42 = m._42 - s._42;  r._43 = m._43 - s._43;  r._44 = m._44 - s._44;
};

// Умножение
void POD_Math::Matrix4x4Mul(POD_Math::Matrix4x4& r, const POD_Math::Matrix4x4& md, const POD_Math::Matrix4x4& mr)
{
	r._11 = md._11 * mr._11 + md._12 * mr._21 + md._13 * mr._31 + md._14 * mr._41;

	r._12 = md._11 * mr._12 + md._12 * mr._22 + md._13 * mr._32 + md._14 * mr._42; 

	r._13 = md._11 * mr._13 + md._12 * mr._23 + md._13 * mr._33 + md._14 * mr._43;

	r._14 = md._11 * mr._14 + md._12 * mr._24 + md._13 * mr._34 + md._14 * mr._44;


	r._21 = md._21 * mr._11 + md._22 * mr._21 + md._23 * mr._31 + md._24 * mr._41;

	r._22 = md._21 * mr._12 + md._22 * mr._22 + md._23 * mr._32 + md._24 * mr._42; 

	r._23 = md._21 * mr._13 + md._22 * mr._23 + md._23 * mr._33 + md._24 * mr._43;

	r._24 = md._21 * mr._14 + md._22 * mr._24 + md._23 * mr._34 + md._24 * mr._44;   


	r._31 = md._31 * mr._11 + md._32 * mr._21 + md._33 * mr._31 + md._34 * mr._41;

	r._32 = md._31 * mr._12 + md._32 * mr._22 + md._33 * mr._32 + md._34 * mr._42; 

	r._33 = md._31 * mr._13 + md._32 * mr._23 + md._33 * mr._33 + md._34 * mr._43;

	r._34 = md._31 * mr._14 + md._32 * mr._24 + md._33 * mr._34 + md._34 * mr._44;   


	r._41 = md._41 * mr._11 + md._42 * mr._21 + md._43 * mr._31 + md._44 * mr._41;

	r._42 = md._41 * mr._12 + md._42 * mr._22 + md._43 * mr._32 + md._44 * mr._42; 

	r._43 = md._41 * mr._13 + md._42 * mr._23 + md._43 * mr._33 + md._44 * mr._43;

	r._44 = md._41 * mr._14 + md._42 * mr._24 + md._43 * mr._34 + md._44 * mr._44;
};

// Обнуление
void POD_Math::Matrix4x4Zero(POD_Math::Matrix4x4&i)
{
	memset(&i,0,sizeof(POD_Math::Matrix4x4));
};

// Обнуление
void POD_Math::Matrix4x4Identity(POD_Math::Matrix4x4&i)
{
	i._11 = 1.0f; i._12 = 0.0f; i._13 = 0.0f; i._14 = 0.0f;

	i._21 = 0.0f; i._22 = 1.0f; i._23 = 0.0f; i._24 = 0.0f;

	i._31 = 0.0f; i._32 = 0.0f; i._33 = 1.0f; i._34 = 0.0f;

	i._41 = 0.0f; i._42 = 0.0f; i._43 = 0.0f; i._44 = 1.0f;
};

// След
float POD_Math::Matrix4x4Trace(const POD_Math::Matrix4x4& m)
{
	return m._11 + m._22 + m._33 + m._44; 
};

// Создаем леворукую матрицу перспективной проекции
void POD_Math::CreatePerspectiveFovLH(POD_Math::Matrix4x4& p, float z_near, float z_far, float fovY, float aspect)
{
	float cotangent = 1.0f / tan( fovY / 2.0f );

	p._11 = cotangent / aspect;
	p._22 = cotangent;
	p._33 = z_far / ( z_far - z_near ); 
	p._34 = 1.0f;
	p._43 = -z_near * z_far / ( z_far - z_near );
};

