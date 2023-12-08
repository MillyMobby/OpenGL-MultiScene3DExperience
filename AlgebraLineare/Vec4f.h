#pragma 
#include "Vec3f.h"
class Vec4f
{
public:
	typedef float vType;

	vType x;
	vType y;
	vType z;
	vType w;

	Vec4f();
	Vec4f(vType n);
	Vec4f(vType v0, vType v1, vType v2, vType v3);
	Vec4f(const Vec4f& v); //copy constructor
	Vec4f(const Vec3f& v, const vType& w);
	Vec4f(const Vec3f& v);
	~Vec4f();

	Vec4f operator+(Vec4f& other);
	Vec4f operator+(float other);
	Vec4f operator+=(Vec4f& other);
	Vec4f operator+=(float other);


	Vec4f operator-(Vec4f& other);
	Vec4f operator-(float other);

	Vec4f operator*(float other);
	Vec4f operator*(Vec4f& other);

	friend std::ostream& operator<<(std::ostream& output, const Vec4f& a);
	float pScalare(Vec4f& other);
	float length();
	float length2();
	Vec4f normalize();
};

