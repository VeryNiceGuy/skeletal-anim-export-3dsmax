#include "Vector3.h"
#include "Matrix4x3.h"
#include "MathTools.h"

void POD_Math::Vector3Normal(POD_Math::Vector3& v)
{
	float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	      if(magnitude != 0.0f)
	      {

	      v.x *= 1.0f / magnitude;

	      v.y *= 1.0f / magnitude;

	      v.z *= 1.0f / magnitude;

          };
};

void POD_Math::Vector3Normal(POD_Math::Vector3& r, const POD_Math::Vector3& v)
{
	float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	      if(magnitude != 0.0f)
	      {

	      r.x = v.x * 1.0f / magnitude;

	      r.y = v.y * 1.0f / magnitude;

		  r.z = v.z * 1.0f / magnitude;

          };
};

void POD_Math::Vector3Mul(POD_Math::Vector3& r,const POD_Math::Vector3& md, const float mr)
{
	r.x = md.x * mr;

	r.y = md.y * mr;

	r.z = md.z * mr;
};

void POD_Math::Vector3Div(POD_Math::Vector3& r,const POD_Math::Vector3& md, const float mr)
{
	r.x = md.x / mr;

	r.y = md.y / mr;

	r.z = md.z / mr;
};

void POD_Math::Vector3Add(POD_Math::Vector3& r, const POD_Math::Vector3& s0, const POD_Math::Vector3& s1)
{
	r.x = s0.x + s1.x;

	r.y = s0.y + s1.y;

	r.z = s0.z + s1.z;
};

void POD_Math::Vector3Sub(POD_Math::Vector3& r, const POD_Math::Vector3& m, const POD_Math::Vector3& s)
{
	r.x = m.x - s.x;

	r.y = m.y - s.y;

	r.z = m.z - s.z;
};

// Умножение вектора на матрицу
void POD_Math::Vector3Mul(POD_Math::Vector3& r, const POD_Math::Vector3& md, const POD_Math::Matrix4x3& mr)
{
	r.x = md.x * mr._11 + md.y * mr._21 + md.z * mr._31 + mr._41;

	r.y = md.x * mr._12 + md.y * mr._22 + md.z * mr._32 + mr._42;

	r.y = md.x * mr._13 + md.y * mr._23 + md.z * mr._33 + mr._43;
};

// Скалярное умножение
float POD_Math::Vector3Dot(const POD_Math::Vector3& md,const POD_Math::Vector3& mr)
{
	return md.x * mr.x + md.y * mr.y + md.z * mr.z;
};

// Векторное умножение
void POD_Math::Vector3Cross(POD_Math::Vector3& r, const POD_Math::Vector3& md, const POD_Math::Vector3& mr)
{
	r.x = md.y * mr.z - md.z * mr.y;

	r.y = md.z * mr.x - md.x * mr.z;

	r.z = md.x * mr.y - md.y * mr.x;
};

// Линейная интерполяция
void POD_Math::Vector3Lerp(POD_Math::Vector3& r, POD_Math::Vector3& start, const POD_Math::Vector3& end, const float diff)
{
	Vector3 VDiff=Vector3();
	POD_Math::Vector3Sub(VDiff,end,start);
	POD_Math::Vector3Div(VDiff,VDiff,diff);
	POD_Math::Vector3Add(r,VDiff,start);
};