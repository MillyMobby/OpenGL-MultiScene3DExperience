#include "Mat4f.h"
using namespace std;


Mat4f::Mat4f() {
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
}
Mat4f::Mat4f(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15) {

    m.push_back(m0);
    m.push_back(m1);
    m.push_back(m2);
    m.push_back(m3);

    m.push_back(m4);
    m.push_back(m5);
    m.push_back(m6);
    m.push_back(m7);

    m.push_back(m8);
    m.push_back(m9);
    m.push_back(m10);
    m.push_back(m11);

    m.push_back(m12);
    m.push_back(m13);
    m.push_back(m14);
    m.push_back(m15);

}

Mat4f::~Mat4f() {}

float Mat4f::operator() (const int i, const int j) 
{
    return m[i * 4 + j];
}

void Mat4f::setAtIndex(float v, int i, int j)
{
    m[i * 4 + j] = v;
}

Vec4f Mat4f::getCol(int j) const { 
    if (j >= 0 && j < 5) return Vec4f(m[j], m[j + 4], m[j + 8], m[j + 12]);
    else return NULL;
}
Vec4f Mat4f::getRow(int i) const {
    if (i >= 0 && i < 5) return Vec4f(m[i], m[i + 1], m[i + 2], m[i + 3]);
    else return NULL;
}
void Mat4f::setCol(int i, const Vec4f& v)
{
    if (i>=0 && i<5) {
        m[i] = v.x;
        m[i + 4] = v.y;
        m[i + 8] = v.z;
        m[i + 12] = v.w;
    }
}
Mat3f Mat4f::getSubmat3x3(int i0, int j0) 
{
    float start = (*this)(i0, j0);
    return Mat3f(start, start + 1, start + 2, start + 3, start + 4, start + 5, start + 6, start + 7, start + 8);
}

Mat4f Mat4f::operator+(const Mat4f& other)
{
    return Mat4f(
        m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2],  m[3] + other.m[3],
        m[4] + other.m[4], m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7], 
        m[8] + other.m[8], m[9] + other.m[9], m[10] + other.m[10], m[11] + other.m[11],
        m[12] + other.m[12], m[13] + other.m[13], m[14] + other.m[14], m[15] + other.m[15]);
}

Mat4f Mat4f::operator-(const Mat4f& other)
{
    return Mat4f(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3],
        m[4] - other.m[4], m[5] - other.m[5],  m[6] - other.m[6], m[7] - other.m[7],
        m[8] - other.m[8], m[9] - other.m[9], m[10] - other.m[10], m[11] - other.m[11], 
        m[12] - other.m[12], m[13] - other.m[13], m[14] - other.m[14], m[15] - other.m[15]);
}

bool Mat4f::operator == (const Mat4f& other) const {
    return (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3] 
        && m[4] == other.m[4] && m[5] == other.m[5] && m[6] == other.m[6] && m[7] == other.m[7] 
        && m[8] == other.m[8] && m[9] == other.m[9] && m[10] == other.m[10] && m[11] == other.m[11] 
        && m[12] == other.m[12] && m[13] == other.m[13] && m[14] == other.m[14] && m[15] == other.m[15]);
}

bool Mat4f::operator != (const Mat4f& other) const {
    return (m[0] != other.m[0] || m[1] != other.m[1] || m[2] != other.m[2] || m[3] != other.m[3] 
        || m[4] != other.m[4] || m[5] != other.m[5] || m[6] != other.m[6] || m[7] != other.m[7] 
        || m[8] != other.m[8] && m[9] != other.m[9] || m[10] != other.m[10] || m[11] != other.m[11]
        || m[12] != other.m[12] || m[13] != other.m[13] || m[14] != other.m[14] || m[15] != other.m[15]);
}

Mat4f Mat4f::operator*(const Mat4f& other)
{
    return Mat4f(m.at(0) * other.m.at(0) + m.at(1) * other.m.at(4) + m.at(2) * other.m.at(8) + m.at(3) * other.m.at(12),
        m.at(0) * other.m.at(1) + m.at(1) * other.m.at(5) + m.at(2) * other.m.at(9) + m.at(3) * other.m.at(13),
        m.at(0) * other.m.at(2) + m.at(1) * other.m.at(6) + m.at(2) * other.m.at(10) + m.at(3) * other.m.at(14),
        m.at(0) * other.m.at(3) + m.at(1) * other.m.at(7) + m.at(2) * other.m.at(11) + m.at(3) * other.m.at(15),

        m.at(4) * other.m.at(0) + m.at(5) * other.m.at(4) + m.at(6) * other.m.at(8) + m.at(7) * other.m.at(12),
        m.at(4) * other.m.at(1) + m.at(5) * other.m.at(5) + m.at(6) * other.m.at(9) + m.at(7) * other.m.at(13),
        m.at(4) * other.m.at(2) + m.at(5) * other.m.at(6) + m.at(6) * other.m.at(10) + m.at(7) * other.m.at(14),
        m.at(4) * other.m.at(3) + m.at(5) * other.m.at(7) + m.at(6) * other.m.at(11) + m.at(7) * other.m.at(15),

        m.at(8) * other.m.at(0) + m.at(9) * other.m.at(4) + m.at(10) * other.m.at(8) + m.at(11) * other.m.at(12),
        m.at(8) * other.m.at(1) + m.at(9) * other.m.at(5) + m.at(10) * other.m.at(9) + m.at(11) * other.m.at(13),
        m.at(8) * other.m.at(2) + m.at(9) * other.m.at(6) + m.at(10) * other.m.at(10) + m.at(11) * other.m.at(14),
        m.at(8) * other.m.at(3) + m.at(9) * other.m.at(7) + m.at(10) * other.m.at(11) + m.at(11) * other.m.at(15),

        m.at(12) * other.m.at(0) + m.at(13) * other.m.at(4) + m.at(14) * other.m.at(8) + m.at(15) * other.m.at(12),
        m.at(12) * other.m.at(1) + m.at(13) * other.m.at(5) + m.at(14) * other.m.at(9) + m.at(15) * other.m.at(13),
        m.at(12) * other.m.at(2) + m.at(13) * other.m.at(6) + m.at(14) * other.m.at(10) + m.at(15) * other.m.at(14),
        m.at(12) * other.m.at(3) + m.at(13) * other.m.at(7) + m.at(14) * other.m.at(11) + m.at(15) * other.m.at(15));
}

Mat4f Mat4f::operator*(const float& other) {
    return Mat4f(m[0] * other, m[1] * other, m[2] * other, m[3] * other,
        m[4] * other, m[5] * other, m[6] * other, m[7] * other,
        m[8] * other,  m[9] * other, m[10] * other, m[11] * other,
        m[12] * other, m[13] * other, m[14] * other, m[15] * other);
}

Mat4f& Mat4f::operator/=(float d)
{
    for (int i = 0; i < 16; i++) {
        m[i] /= d;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& output, const Mat4f& a)
{
    output << endl
        << a.m[0] << " " << a.m[1] << " " << a.m[2] << " " << a.m[3] << endl
        << a.m[4] << " " << a.m[5] << " " << a.m[6] << " " << a.m[7] << endl
        << a.m[8] << " " << a.m[9] << " " << a.m[10]<< " " << a.m[11]<< endl
        << a.m[12] << " "<< a.m[13]<< " " << a.m[14]<< " " << a.m[15]<< endl;
    return output;
}

Mat4f Mat4f::trasposta() {
    return Mat4f(
        m[0], m[4], m[8], m[12], 
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]);
}

void Mat4f::transpose()
{
}

float Mat4f::det() const
{
    float m00 = m[0];
    float m10 = m[1];
    float m20 = m[2];
    float m30 = m[3];

    float m01 = m[4];
    float m11 = m[5];
    float m21 = m[6];
    float m31 = m[7];

    float m02 = m[8];
    float m12 = m[9];
    float m22 = m[10];
    float m32 = m[11];

    float m03 = m[12];
    float m13 = m[13];
    float m23 = m[14];
    float m33 = m[15];

    Mat3f sub00 = Mat3f(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    Mat3f sub01 = Mat3f(m12, m13, m10, m22, m23, m20, m32, m33, m30);
    Mat3f sub02 = Mat3f(m13, m10, m11, m23, m20, m21, m33, m30, m31);
    Mat3f sub03 = Mat3f(m10, m11, m12, m20, m21, m22, m30, m31, m32);

    float cofactor00 = sub00.det();
    float cofactor01 = -sub01.det();
    float cofactor02 = sub02.det();
    float cofactor03 = -sub03.det();

    return(m00 * cofactor00 + m01 * cofactor01 + m02 * cofactor02 + m03 * cofactor03);
}