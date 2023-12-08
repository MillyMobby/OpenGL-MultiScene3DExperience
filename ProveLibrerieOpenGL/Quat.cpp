#include "Quat.h"
// static
//const Quat Quat::ZERO = Quat(0, 0, 0, 0);

// static
//const Quat Quat::IDENTITY = Quat(1, 0, 0, 0);

Quat::Quat()
{
    q[0] = 0;
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;
}

Quat::Quat(float w, float x, float y, float z)
{
    q[0] = w;
    q[1] = x;
    q[2] = y;
    q[3] = z;
}

Quat::Quat(const Quat& rq)
{
    q[0] = rq.q[0];
    q[1] = rq.q[1];
    q[2] = rq.q[2];
    q[3] = rq.q[3];
}

Quat& Quat::operator = (const Quat& rq)
{
    if (this != (&rq))
    {
        q[0] = rq.q[0];
        q[1] = rq.q[1];
        q[2] = rq.q[2];
        q[3] = rq.q[3];
    }
    return(*this);
}

Quat::Quat(const Vec3f& v)
{
    q[0] = 0;
    q[1] = v.x;
    q[2] = v.y;
    q[3] = v.z;
}

Quat::Quat(const Vec4f& v)
{
    q[0] = v.w;
    q[1] = v.x;
    q[2] = v.y;
    q[3] = v.z;
}


float& Quat::operator[] (int i)
{
    return q[i];
}

float Quat::w() const
{
    return q[0];
}

float Quat::x() const
{
    return q[1];
}

float Quat::y() const
{
    return q[2];
}

float Quat::z() const
{
    return q[3];
}

Vec3f Quat::xyz() const
{
    return Vec3f
    (
        q[1],
        q[2],
        q[3]
    );
}

Vec4f Quat::wxyz() const
{
    Vec4f v = Vec4f
    (
        q[0],
        q[1],
        q[2],
        q[3]
    );
    return v;
}

float Quat::lenght() const
{
    return sqrt(lenght2());
}

float Quat::lenght2() const
{
    return
        (
            q[0] * q[0] +
            q[1] * q[1] +
            q[2] * q[2] +
            q[3] * q[3]
            );
}

void Quat::normalize()
{
    float reciprocalAbs = 1.f / lenght();

    q[0] *= reciprocalAbs;
    q[1] *= reciprocalAbs;
    q[2] *= reciprocalAbs;
    q[3] *= reciprocalAbs;
}

Quat Quat::normalized() const
{
    Quat q(*this);
    q.normalize();
    return q;
}

void Quat::coniugate()
{
    q[1] = -q[1];
    q[2] = -q[2];
    q[3] = -q[3];
}

Quat Quat::coniugated() const
{
    return Quat
    (
        q[0],
        -q[1],
        -q[2],
        -q[3]
    );
}

void Quat::invert()
{
    Quat inverse = coniugated() * (1.0f / lenght2());

    q[0] = inverse.q[0];
    q[1] = inverse.q[1];
    q[2] = inverse.q[2];
    q[3] = inverse.q[3];
}

Quat Quat::inverse() const
{
    return coniugated() * (1.0f / lenght2());
}

Quat operator + (const Quat& q0, const Quat& q1)
{
    return Quat
    (
        q0.w() + q1.w(),
        q0.x() + q1.x(),
        q0.y() + q1.y(),
        q0.z() + q1.z()
    );
}

Quat operator - (const Quat& q0, const Quat& q1)
{
    return Quat
    (
        q0.w() - q1.w(),
        q0.x() - q1.x(),
        q0.y() - q1.y(),
        q0.z() - q1.z()
    );
}

Quat operator * (const Quat& q0, const Quat& q1)
{
    return Quat
    (
        q0.w() * q1.w() - q0.x() * q1.x() - q0.y() * q1.y() - q0.z() * q1.z(),
        q0.w() * q1.x() + q0.x() * q1.w() + q0.y() * q1.z() - q0.z() * q1.y(),
        q0.w() * q1.y() - q0.x() * q1.z() + q0.y() * q1.w() + q0.z() * q1.x(),
        q0.w() * q1.z() + q0.x() * q1.y() - q0.y() * q1.x() + q0.z() * q1.w()
    );
}


Quat operator * (const Quat& q, float f)
{
    return Quat
    (
        f * q.w(),
        f * q.x(),
        f * q.y(),
        f * q.z()
    );
}


