#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Matrix4x3.h"
#include "MathTools.h"
#include <memory>

// Прямой поворот вектора
void POD_Math::QuatMul(POD_Math::Vector3& r, const POD_Math::Quaternion& md, const POD_Math::Vector3& mr)
{
	
    POD_Math::Vector3 uv   = POD_Math::Vector3(); 
	POD_Math::Vector3 uuv  = POD_Math::Vector3();
	POD_Math::Vector3 qvec = { md.x, md.y, md.z };

	POD_Math::Vector3Cross(uv,  qvec, mr);
    POD_Math::Vector3Cross(uuv, qvec, uv);

	Vector3Mul(uv,  uv,  2.0f * md.w );
	Vector3Mul(uuv, uuv, 2.0f);

    Vector3Add(r, mr, uv); 
	Vector3Add(r, r,  uuv);
};

// Создаем кватернион из оси и угла
void POD_Math::QuatAxis(POD_Math::Quaternion& q, const Vector3& v, const float ang)
{
	POD_Math::Vector3 tmp=Vector3();
	POD_Math::Vector3Normal(tmp, v);

	float Sina = sin(ang / 2.0f);

	q.w = cos(ang/2);
	q.x = Sina * tmp.x;
	q.y = Sina * tmp.y;
	q.z = Sina * tmp.z;
};

// Нормализация
void POD_Math::QuatNormalize(POD_Math::Quaternion& r, const POD_Math::Quaternion& q)
{
	float magnitude = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

	if(magnitude > 0.0f)
	{
		float oneOverMag = 1.0f / magnitude;

		r.w = q.w * oneOverMag; 
		r.x = q.x * oneOverMag; 
		r.y = q.y * oneOverMag; 
		r.z = q.z * oneOverMag; 
	}
	else
	{
		POD_Math::QuatIdentity(r);
	};
};

void POD_Math::QuatSlerp(POD_Math::Quaternion& r, const POD_Math::Quaternion& q1, const POD_Math::Quaternion& q2, const float t)
{
   
	float cosOmega = POD_Math::QuatDotProduct(q1, q2);

	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	float k0 = 0;
	float k1 = 0;

	if (cosOmega < 0.0f)
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;

		cosOmega = -cosOmega;
	};

	if (cosOmega > 0.9999f) 
	{

		k0 = 1.0f-t;
		k1 = t;

	}
	else
	{

		float sinOmega = sqrt(1.0f - cosOmega * cosOmega);

		float omega = atan2(sinOmega, cosOmega);

		float oneOverSinOmega = 1.0f / sinOmega;

		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;

		k1 = sin(t * omega) * oneOverSinOmega;
	};

		r.w = k0 * q1.w + k1 * q1w;

		r.x = k0 * q1.x + k1 * q1x;

		r.y = k0 * q1.y + k1 * q1y;

		r.z = k0 * q1.z + k1 * q1z;
};

// Скалярное произведение
float POD_Math::QuatDotProduct(const POD_Math::Quaternion& md, const POD_Math::Quaternion& mr)
{
	return md.w * mr.w + md.x * mr.x + md.y * mr.y + md.z * mr.z; 
};

// Сопряжение
void POD_Math::QuatConjugate(POD_Math::Quaternion& r, const POD_Math::Quaternion& q)
{
	r.w =  q.w; 
	r.x = -r.x;  
	r.y = -r.y; 
	r.z = -r.z; 
};

// Умножение, следуя уравнению (ab - vu1 * vu2)(avu1 + bvu2 + vu1 x vu2)
void POD_Math::QuatMul(POD_Math::Quaternion& r, const POD_Math::Quaternion& md, const POD_Math::Quaternion& mr)
{
	 r.w = md.w * mr.w - md.x * mr.x - md.y * mr.y - md.z * mr.z;

	 r.x = md.w * mr.x + md.x * mr.w + md.y * mr.z - md.z * mr.y;  

	 r.y = md.w * mr.y + mr.w * md.y + md.z * mr.x - md.y * mr.z;

	 r.z = md.w * mr.z + mr.w * md.z + md.y * mr.y - md.y * mr.x;
};

// Конвертируем кватернион в матрицу 4х4
void POD_Math::QuatToMatrix4x4(POD_Math::Matrix4x4& r, const POD_Math::Quaternion& q)
{
	r._11 = 1.0f - 2.0f * ( q.y * q.y + q.z * q.z );
	r._12 = 2.0f * ( q.x * q.y + q.z * q.w );
	r._13 = 2.0f * ( q.x * q.z - q.y * q.w );

	r._21 = 2.0f * ( q.x * q.y - q.z*q.w);
	r._22 = 1.0f - 2.0f *(q.x * q.x + q.z * q.z);
	r._23 = 2.0f * ( q.y * q.z + q.x * q.w );

	r._31 = 2.0f * ( q.x * q.z + q.y * q.w );
	r._32 = 2.0f * ( q.y * q.z - q.w * q.x );
	r._33 = 1.0f - 2.0f * ( q.x * q.x + q.y * q.y ); 
};

// Конвертируем кватернион в матрицу 4х3
void POD_Math::QuatToMatrix4x3(Matrix4x3& r, const POD_Math::Quaternion& q)
{
	r._11 = 1.0f - 2.0f * (q.y*q.y + q.z*q.z);
	r._12 = 2.0f * (q.x*q.y - q.w*q.z);
	r._13 = 2.0f * (q.x*q.z + q.w*q.y);

	r._21 = 2.0f * (q.x*q.y + q.w*q.z);
	r._22 = 1.0f - 2.0f * (q.x*q.x + q.z*q.z);
	r._23 = 2.0f * (q.y*q.z - q.w*q.x);

	r._31 = 2.0f * (q.x*q.z - q.w*q.y);
	r._32 = 2.0f * (q.y*q.z + q.w*q.x);
	r._33 = 1.0f - 2.0f * (q.x*q.x + q.y*q.y);
};

// Конвертирование матрицы 4х4 в кватернион
void POD_Math::Matrix4x4ToQuat(POD_Math::Quaternion& r, const POD_Math::Matrix4x4& m)
{
	unsigned short inx=0;

	float Bigest1 = m._11 + m._22 + m._33;  
	float Bigest2 = m._11 - m._22 - m._33; 
	float Bigest3 = m._22 - m._11 - m._33; 
	float Bigest4 = m._33 - m._11 - m._22; 

	float Bigest=Bigest1;

	     if( Bigest < Bigest2 ) { Bigest=Bigest2; inx=1; };
	     if( Bigest < Bigest3 ) { Bigest=Bigest3; inx=2; };
	     if( Bigest < Bigest4 ) { Bigest=Bigest4; inx=3; };

	float BigestValue = sqrt(Bigest+1.0f)*0.5f;
    float mult = 0.25f / BigestValue;

	switch(inx)
	{

	    case 0:

		     r.w = BigestValue; 
		     r.x = ( m._23 - m._32 ) * mult;
		     r.y = ( m._31 - m._13 ) * mult;
		     r.z = ( m._12 - m._21 ) * mult;

		break;

	    case 1:

		     r.x = BigestValue;
		     r.w = ( m._23 - m._32 ) * mult;
		     r.y = ( m._12 + m._21 ) * mult;
		     r.z = ( m._31 + m._13 ) * mult;

		break;

	    case 2:

		     r.y = BigestValue;
		     r.w = ( m._31 - m._13 ) * mult;
		     r.x = ( m._12 + m._21 ) * mult;
		     r.z = ( m._23 + m._32 ) * mult;

		break;

	    case 3:

		     r.z = BigestValue;
		     r.w = ( m._12 - m._21 ) * mult;
		     r.x = ( m._31 + m._13 ) * mult;
		     r.y = ( m._23 + m._32 ) * mult;

		break;
	};
};

// Конвертирование матрицы 4х3 в кватернион
void POD_Math::Matrix4x3ToQuat(POD_Math::Quaternion& r, const POD_Math::Matrix4x3& m)
{
	unsigned short inx=0;

	float Bigest1 = m._11 + m._22 + m._33;  
	float Bigest2 = m._11 - m._22 - m._33; 
	float Bigest3 = m._22 - m._11 - m._33; 
	float Bigest4 = m._33 - m._11 - m._22; 

	float Bigest=Bigest1;

	     if( Bigest < Bigest2 ) { Bigest=Bigest2; inx=1; };
	     if( Bigest < Bigest3 ) { Bigest=Bigest3; inx=2; };
	     if( Bigest < Bigest4 ) { Bigest=Bigest4; inx=3; };

	float BigestValue = sqrt(Bigest+1.0f)*0.5f;
    float mult = 0.25f / BigestValue;

	switch(inx)
	{

	    case 0:

		     r.w = BigestValue; 
		     r.x = ( m._23 - m._32 ) * mult;
		     r.y = ( m._31 - m._13 ) * mult;
		     r.z = ( m._12 - m._21 ) * mult;

		break;

	    case 1:

		     r.x = BigestValue;
		     r.w = ( m._23 - m._32 ) * mult;
		     r.y = ( m._12 + m._21 ) * mult;
		     r.z = ( m._31 + m._13 ) * mult;

		break;

	    case 2:

		     r.y = BigestValue;
		     r.w = ( m._31 - m._13 ) * mult;
		     r.x = ( m._12 + m._21 ) * mult;
		     r.z = ( m._23 + m._32 ) * mult;

		break;

	    case 3:

		     r.z = BigestValue;
		     r.w = ( m._12 - m._21 ) * mult;
		     r.x = ( m._31 + m._13 ) * mult;
		     r.y = ( m._23 + m._32 ) * mult;

		break;
	};
};

void POD_Math::QuatIdentity(POD_Math::Quaternion& q)
{
	q.w=1.0f; q.x = q.y = q.z = 0.0f;
};

void POD_Math::QuatZero(Quaternion& q)
{
	memset(&q,0,sizeof(POD_Math::Quaternion)); 
};