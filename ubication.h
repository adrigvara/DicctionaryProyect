#ifndef __FORCE_H__
#define __FORCE_H__

#include "node.h"
#include "vector.h"
#include <stdbool.h>

#define FORCE_CONST 100.0
#define UBICATION_CONST 0.5
#define ATTRACTION_CONST 1.0
#define REPULSION_CONST 1000.0

void applyForces(Node *nodes);
void assignUbications(Node *nodes);
Vector attractionForce(Vector vector1, Vector vector2);
Vector negativeAttractiveForce(Node *node, Link *links, Vector ubication);
Vector newUbication(Vector previusUbication, Vector force, unsigned int totalNodes);
double randomDouble();
Vector randomUbication(unsigned int totalNodes);
Vector repulsionForce(Vector vector1, Vector vector2);
Vector sumOfAttractiveForces(Node *node, Node *nodes);
Vector sumOfForces(Node *node, Node *nodes);
Vector sumOfPositiveAttractiveForces(Node *node, Link *links);
Vector sumOfRepulsiveForces(Node *node, Node *nodes);

Vector probabilityUbication(Node *node1, Node *node2){
  return vectorPlusVector(node1->ubication, vectorBetweenScalar(vectorDistance(node1->ubication, node2->ubication), 3));
}
void assignUbications(Node *nodes){
  for(unsigned int totalNodes = countNodes(nodes); nodes!=NULL; nodes = nodes->next)
    if(vectorInOrigin(nodes->ubication))
      nodes->ubication = randomUbication(totalNodes);
}
Vector randomUbication(unsigned int totalNodes){
  return {randomDouble()*totalNodes*UBICATION_CONST, randomDouble()*totalNodes*UBICATION_CONST};
}
double randomDouble(){
  return ((double)random()/RAND_MAX*2.0)-1.0;
}
void applyForces(Node *nodes){
  unsigned int totalNodes = countNodes(nodes);
  for(Node *node = nodes; node!=NULL; node = node->next)
    node->ubication = newUbication(node->ubication, sumOfForces(node, nodes), totalNodes);
}
Vector newUbication(Vector previusUbication, Vector force, unsigned int totalNodes){
  return vectorPlusVector(previusUbication, vectorBetweenScalar(force, FORCE_CONST));
}
Vector sumOfForces(Node *node, Node *nodes){
  return vectorPlusVector(sumOfAttractiveForces(node, nodes), sumOfRepulsiveForces(node, nodes));
}
Vector sumOfAttractiveForces(Node *node, Node *nodes){
  return nodes==NULL ? vectorOrigin() : node==nodes ? vectorPlusVector(sumOfPositiveAttractiveForces(node, node->links), sumOfAttractiveForces(node, nodes->next)) : vectorPlusVector(negativeAttractiveForce(node, nodes->links, nodes->ubication), sumOfAttractiveForces(node, nodes->next));
}
Vector sumOfPositiveAttractiveForces(Node *node, Link *links){
  return links==NULL ? vectorOrigin() : vectorPlusVector(attractionForce(node->ubication, links->node->ubication), sumOfPositiveAttractiveForces(node, links->next));
}
Vector negativeAttractiveForce(Node *node, Link *links, Vector ubication){
  return links==NULL ? vectorOrigin() : links->node==node ? attractionForce(node->ubication, ubication) : negativeAttractiveForce(node, links->next, ubication);
}
Vector sumOfRepulsiveForces(Node *node, Node *nodes){
  return nodes==NULL ? vectorOrigin() : node==nodes ? sumOfRepulsiveForces(node, nodes->next) : vectorPlusVector(repulsionForce(node->ubication, nodes->ubication), sumOfRepulsiveForces(node, nodes->next));
}
Vector repulsionForce(Vector vector1, Vector vector2){
  return vectorByScalar(direction(vectorDistance(vector2, vector1)), REPULSION_CONST/pow(distance(vector2, vector1), 2));
}
Vector attractionForce(Vector vector1, Vector vector2){
  return vectorByScalar(direction(vectorDistance(vector1, vector2)), ATTRACTION_CONST*distance(vector1, vector2));
}

#endif
