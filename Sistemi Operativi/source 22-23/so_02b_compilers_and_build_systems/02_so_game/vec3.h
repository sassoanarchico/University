#ifndef _VEC3_H_
#define _VEC3_H_

//! simple 3D vector
typedef struct Vec3 {
  float values[3];
} Vec3;

//! dest = a*alpha_a+b*alpha_b
void v3compose(Vec3* dest, const Vec3* a, const Vec3* b, float alpha_a, float alpha_b);

//! returns the scalar product of  a and b
float v3dot(const Vec3* a, const Vec3* b);

//! dest = cross_product(a,b)
void v3cross(Vec3* dest, const Vec3* a, const Vec3* b);

//! dest = a * dest
void v3scale(Vec3* dest, float s);

//! scales dest to unit norm
void v3normalize(Vec3* dest);

//! 4x4 matrix multiplication
void mat4mult(float dest[], float a[], float b[]);

//! fills a 3 transform with a rotation along z 
void mat4rotationX(float dest[], float alpha);

void v3polar(Vec3* dest, const Vec3* src);

void mat4invtransform(float dest[], const float src[]);

#endif
