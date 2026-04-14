#include"transform.h"
#include<math.h>

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
	
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x=v1.x-v2.x;
	result.y=v1.y-v2.y;
	result.z=v1.z-v2.z;
	return result;
}

Vector3 Multiply(const float scalar, const Vector3& v1)
{
	Vector3 result;
	result.x = scalar * v1.x;
	result.y = scalar * v1.y;
	result.z = scalar * v1.z;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2)
{ 
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


