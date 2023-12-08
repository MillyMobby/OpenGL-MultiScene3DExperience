#include "Vec3f.h"
#include "Mat3f.h"
#include "Mat4f.h"
//#include "Vec3f.h"
#include <vector>
#include <iostream>

using namespace std;

int main() {

    Mat4f mat = Mat4f(1, 22, 3, 4, 8, 5, 3, 8, 9,10,11,12,13,14,15,16);
    cout << mat;
    //mat.transpose();
    float det = mat.det();
    cout << "il determinante e' " << det << endl;
    Mat4f mat2 = Mat4f(1, 22, 3, 4, 8, 5, 3, 8, 9, 2,2,2, 13, 14, 15, 16);
    Mat4f mat3 = mat * mat2;
    cout << "prodotto mat + mat2 = " << mat3;
    cout << "\n elemento (3,1) " << mat(2, 0);
    cout << "\n mat per 3 \n" << mat * 3;
    /*Mat3f cof = mat.cofattori();
    cout << cof;
    Mat3f inv = mat.inversa2();
    cout << inv;
    Mat3f prod = mat * inv;
    cout << "mat per inversa = " << prod;
    

    /*Vec3f vet1 = Vec3f(1, 2, 3);
    cout << vet1;
    Vec3f vet2 = Vec3f(4,5,6);
    float prodScal = vet1.dot(vet2);
    cout << " prodotto scalare tra vet1 e vet2 " << prodScal;
    Vec3f prodVett = vet1.cross(vet2);
    cout << prodVett;*/

    return 0;
}