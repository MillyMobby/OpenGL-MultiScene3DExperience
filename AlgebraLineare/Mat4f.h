#pragma once
#include <vector>
#include <iostream>
#include "Vec4f.h"
#include "Mat3f.h"
using namespace std;
typedef float vtype;
class Mat4f
{
	std::vector<float> m;
public:
	
	Mat4f();
	Mat4f(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12 ,float m13, float m14, float m15);

	~Mat4f();
	float operator()(const int i, const int j);
	void setAtIndex(float v, int i, int j);
	Vec4f getCol(int j) const;
	Vec4f getRow(int i) const;
	void setCol(int i, const Vec4f& v);
	Mat3f getSubmat3x3(int i0, int j0);
	Mat4f operator+(const Mat4f& other);
    //friend Mat3f operator+(const Mat3f& other, const vtype& scalare);
	Mat4f operator-(const Mat4f& other);
	bool operator == (const Mat4f& other) const;
	bool operator != (const Mat4f& other) const;
	Mat4f operator*(const float& other);
	Mat4f operator*(const Mat4f& other);
	
	Mat4f& operator/=(float d);
	

	friend std::ostream& operator<<(std::ostream& output, const Mat4f& a);

	Mat4f trasposta();
	void transpose();
	float det() const;
	bool invertibile();
	Mat4f cofattori();
	Mat4f inversa();
	Mat4f inversa2();

};




