#pragma once
#include <cmath>
#include <cstdio>

#include "Mat3f.h"
#include "Vec3f.h"
#include "Vec4f.h"

class Quat {

private:
    

public:
    std::vector<float> q;
   
    Quat();
    ~Quat() {}

    // q = w + x * i + y * j + z * k
    Quat(float w, float x, float y, float z);

    Quat(const Quat& rq); // copy constructor
    Quat& operator = (const Quat& rq); // assignment 

    Quat(const Vec3f& v);


    Quat(const Vec4f& v);


    const float& operator [] (int i) const;
    float& operator [] (int i);

    float w() const;
    float x() const;
    float y() const;
    float z() const;
    Vec3f xyz() const;
    Vec4f wxyz() const;

    float lenght() const;
    float lenght2() const;
    void normalize();
    Quat normalized() const;

    void coniugate();
    Quat coniugated() const;

    void invert();
    Quat inverse() const;
};

Quat operator + (const Quat& q0, const Quat& q1);
Quat operator - (const Quat& q0, const Quat& q1);
Quat operator * (const Quat& q0, const Quat& q1);
Quat operator * (float f, const Quat& q);
Quat operator * (const Quat& q, float f);

