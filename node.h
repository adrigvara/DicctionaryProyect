#ifndef __NODE_H__
#define __NODE_H__

//
//  HEADERS
//

#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "vector.h"

//
//  STRUCTS
//

typedef struct Node Node;
typedef struct Link Link;

struct Node{
  char word[MAXIMUM_WORD_LENGTH+1];
  unsigned int count;
  double probability;
  Vector ubication;
  Link *links;
  Node *next;
};
struct Link{
  unsigned int count;
  double probability;
  Node *node;
  Link *next;
};

//
//  FUNCTION PROTOTYPES
//

Link *allocateLink(Node *node);
Node *allocateNode(char *word);
Link *includeLink(Link **pointer, Link *link);
Node *includeNode(Node **pointer, Node *node);
Link *searchLink(Link *links, Node *node);
Node *searchNode(Node *nodes, char *word);
Link *searchOrInsertLink(Node *node1, Node *node2);
Node *searchOrInsertNode(Node **graph, char *word);
unsigned int countLinks(Link *links);
unsigned int countNodes(Node *nodes);
unsigned int countTotalLinks(Node *nodes);
unsigned int countTotalWordLinks(Node *nodes);
unsigned int countWordLinks(Link *links);
unsigned int countWords(Node *nodes);
void deleteLinks(Link *links);
void deleteNodes(Node *nodes);

//
//  NODE FUNCTIONS
//

unsigned int countNodes(Node *nodes){
  return nodes==NULL ? 0 : 1 + countNodes(nodes->next);
}
unsigned int countWords(Node *nodes){
  return nodes==NULL ? 0 : nodes->count + countWords(nodes->next);
}
Node *searchOrInsertNode(Node **graph, char *word){
  Node *node = searchNode(*graph, word);
  if(node==NULL)
    node = includeNode(graph, allocateNode(word));
  return node;
}
Node *searchNode(Node *nodes, char *word){
  return nodes==NULL || strcmp(nodes->word, word)==0 ? nodes : searchNode(nodes->next, word);
}
Node *includeNode(Node **pointer, Node *node){
  if(node!=NULL){
    node->next = *pointer;
    *pointer = node;
  }
  return node;
}
Node *allocateNode(char *word){
  Node *node = (Node*)calloc(1, sizeof(Node));
  if(node!=NULL)
    strcpy(node->word, word);
  return node;
}
void deleteNodes(Node *nodes){
  if(nodes!=NULL){
    deleteLinks(nodes->links);
    deleteNodes(nodes->next);
    free(nodes);
  }
}

//
//  LINK FUNCTIONS
//

unsigned int countTotalWordLinks(Node *nodes){
  return nodes==NULL ? 0 : countWordLinks(nodes->links) + countTotalWordLinks(nodes->next);
}
unsigned int countTotalLinks(Node *nodes){
  return nodes==NULL ? 0 : countLinks(nodes->links) + countTotalLinks(nodes->next);
}
unsigned int countLinks(Link *links){
  return links==NULL ? 0 : 1 + countLinks(links->next);
}
unsigned int countWordLinks(Link *links){
  return links==NULL ? 0 : links->count + countWordLinks(links->next);
}
Link *searchOrInsertLink(Node *node1, Node *node2){
  if(node1!=NULL && node2!=NULL){
    Link *link = searchLink(node1->links, node2);
    if(link==NULL)
      link = includeLink(&node1->links, allocateLink(node2));
    return link;
  }
  return NULL;
}
Link *searchLink(Link *links, Node *node){
  return links==NULL || links->node==node ? links : searchLink(links->next, node);
}
Link *includeLink(Link **pointer, Link *link){
  if(link!=NULL){
    link->next = *pointer;
    *pointer = link;
  }
  return link;
}
Link *allocateLink(Node *node){
  Link *link = (Link*)calloc(1, sizeof(Link));
  if(link!=NULL)
    link->node = node;
  return link;
}
void deleteLinks(Link *links){
  if(links!=NULL){
    deleteLinks(links->next);
    free(links);
  }
}

#endif
