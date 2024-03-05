#include "vec3.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

void v3compose(Vec3* dest, const Vec3* a, const Vec3* b, float alpha_a, float alpha_b){
  dest->values[0]=a->values[0]*alpha_a+b->values[0]*alpha_b;
  dest->values[1]=a->values[1]*alpha_a+b->values[1]*alpha_b;
  dest->values[2]=a->values[2]*alpha_a+b->values[2]*alpha_b;
}

float v3dot(const Vec3* a, const Vec3* b){
  return a->values[0]*b->values[0]+a->values[1]*b->values[1]+a->values[2]*b->values[2];
}

void v3cross(Vec3* dest, const Vec3* a, const Vec3* b){
  dest->values[0]=a->values[1]*b->values[2]-a->values[2]*b->values[1];
  dest->values[1]=a->values[2]*b->values[0]-a->values[0]*b->values[2];
  dest->values[2]=a->values[0]*b->values[1]-a->values[1]*b->values[0];
}

void v3scale(Vec3* dest, float s){
  dest->values[0]*=s;
  dest->values[1]*=s;
  dest->values[2]*=s;
}


void v3normalize(Vec3* dest){
  float n2=v3dot(dest, dest);
  n2=1./sqrt(n2);
  v3scale(dest, n2);
}

void mat4mult(float dest[], float a[], float b[]){
  memset(dest, 0, 16*sizeof(float));
  for(int r=0; r<4; r++)
    for (int c=0; c<4; c++){
      float* mrc=dest+(c*4+r);
      for (int i=0; i<4; i++){
	(*mrc) +=  a[i*4+r] * b[4*c+i];
      }
    }
}

void mat4rotationX(float dest[], float alpha){
  float s = sin(alpha), c=cos(alpha);
  memset(dest, 0, 16*sizeof(float));
  dest[0]=c;
  dest[1]=s;
  dest[4]=-s;
  dest[5]=c;
  dest[10]=dest[15]=1;
}

void v3polar(Vec3* dest, const Vec3* src) {
  dest->values[0]=sqrt(v3dot(src, src));
  dest->values[1]=atan2(src->values[1],src->values[0]);
  float nxy=sqrt(src->values[0]*src->values[0]+src->values[1]*src->values[1]);
  dest->values[2]=atan2(src->values[2],nxy);
}

void mat4invtransform(float dest[], const float src[]){
  dest[0]=src[0];
  dest[1]=src[4];
  dest[2]=src[8];
  dest[3]=0.f;
  dest[4]=src[1];
  dest[5]=src[5];
  dest[6]=src[9];
  dest[7]=0.f;
  dest[8]=src[2];
  dest[9]=src[6];
  dest[10]=src[10];
  dest[11]=0.f;
  dest[12]=-(dest[0]*src[12]+dest[4]*src[13]+dest[8]*src[14]);
  dest[13]=-(dest[1]*src[12]+dest[5]*src[13]+dest[9]*src[14]);
  dest[14]=-(dest[2]*src[12]+dest[6]*src[13]+dest[10]*src[14]);
  dest[15]=1.f;
}
