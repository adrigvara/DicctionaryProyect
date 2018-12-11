#ifndef __PROBABILITY_H__
#define __PROBABILITY_H__

#include "node.h"

double getConditionalProbability(Link *links);
void updateLinksConditionalProbabilities(Link *links);
void updateLinksProbabilities(Link *links, unsigned int linksCount);
void updateConditionalProbabilities(Node *nodes);
void updateNodesProbabilities(Node *nodes, unsigned int totalWords);
Link *getMostLikelyLink(Link *links);

Link *getMostLikelyLink(Link *links){
  if(links==NULL)
    return NULL;
  Link *next = getMostLikelyLink(links->next);
  return next==NULL ? links : links->probability>next->probability ? links : next;
}
void updateConditionalProbabilities(Node *nodes){
  updateNodesProbabilities(nodes, countWords(nodes));
  for(; nodes!=NULL; nodes = nodes->next)
    updateLinksConditionalProbabilities(nodes->links);
}
void updateNodesProbabilities(Node *nodes, unsigned int totalWords){
  for(; nodes!=NULL; nodes = nodes->next){
    nodes->probability = (double)nodes->count/totalWords;
    updateLinksProbabilities(nodes->links, countWordLinks(nodes->links));
  }
}
void updateLinksProbabilities(Link *links, unsigned int totalLinks){
  for(; links!=NULL; links = links->next)
    links->probability = (double)links->count/totalLinks;
}
void updateLinksConditionalProbabilities(Link *links){
  double conditionalProbability = getConditionalProbability(links);
  for(; links!=NULL; links = links->next)
    links->probability *= links->node->probability/conditionalProbability;
}
double getConditionalProbability(Link *links){
  return links==NULL ? 0.0 : links->probability*links->node->probability + getConditionalProbability(links->next);
}

#endif
