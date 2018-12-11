#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct Vector Vector;

struct Vector{
  double x;
  double y;
};

Vector vectorOrigin(){
  return {0.0, 0.0};
}
double magnitude(Vector vector){
  return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}
bool vectorNearOrigin(Vector vector){
  return magnitude(vector)<1.0;
}
bool equalVectors(Vector vector1, Vector vector2){
  return vector1.x==vector2.x && vector1.y==vector2.y;
}
bool vectorInOrigin(Vector vector){
  return equalVectors(vector, vectorOrigin());
}
Vector vectorPlusVector(Vector vector1, Vector vector2){
  return {vector1.x+vector2.x, vector1.y+vector2.y};
}
Vector vectorMinusVector(Vector vector1, Vector vector2){
  return {vector1.x-vector2.x, vector1.y-vector2.y};
}
Vector vectorByScalar(Vector vector, double scalar){
  return {vector.x*scalar, vector.y*scalar};
}
Vector vectorBetweenScalar(Vector vector, double scalar){
  return {vector.x/scalar, vector.y/scalar};
}
Vector vectorDistance(Vector vector1, Vector vector2){
  return vectorMinusVector(vector2, vector1);
}
double distance(Vector vector1, Vector vector2){
  return magnitude(vectorDistance(vector1, vector2));
}
Vector direction(Vector vector){
  return vectorBetweenScalar(vector, magnitude(vector));
}

#endif
