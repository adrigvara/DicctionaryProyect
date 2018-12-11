#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>
#include "parsing.h"
#include "node.h"
#include "ubication.h"
#include "probability.h"

Node *addWordsToGraph(Node **graph, Word *words);
Node *addWordToGraph(Node **graph, Word *word);
char *getPrediction(Node *graph, char *phrase);
void addGraphFileToGraph(Node **graph, FILE *graphFile);
void addLinksToGraph(Node *node, Word *words, Node **graph);
void addTextFileToGraph(Node **graph, FILE *textFile);
void saveNodes(Node *nodes, FILE *graphFile);
void saveLinks(Link *links, FILE *graphFile);

char *getPrediction(Node *graph, char *phrase){
  Word *words = getWordsFromPhrase(phrase);
  graph = searchNode(graph, words->word);
  if(graph==NULL)
    phrase = NULL;
  else{
    Link *link = getMostLikelyLink(graph->links);
    if(link!=NULL)
      phrase = link->node->word;
    else
      phrase = NULL;
  }
  deleteWords(words);
  return phrase;
}
void addGraphFileToGraph(Node **graph, FILE *graphFile){
  while(!feof(graphFile)){
    if(Word *words = getWordsFromGraphFile(graphFile)){
      addLinksToGraph(addWordToGraph(graph, words), words->next, graph);
      deleteWords(words);
    }
  }
  fclose(graphFile);
  assignUbications(*graph);
  updateConditionalProbabilities(*graph);
}
void addLinksToGraph(Node *node, Word *words, Node **graph){
  for(; words!=NULL; words = words->next){
    Node *nextNode = searchOrInsertNode(graph, words->word);
    Link *link = searchLink(node->links, nextNode);
    if(link==NULL)
      link = includeLink(&node->links, allocateLink(nextNode));
    if(link!=NULL)
      link->count += words->count;
  }
}
Node *addWordToGraph(Node **graph, Word *word){
  Node *node = searchNode(*graph, word->word);
  if(node==NULL)
    node = includeNode(graph, allocateNode(word->word));
  if(node!=NULL)
    node->count += word->count;
  return node;
}
void addTextFileToGraph(Node **graph, FILE *textFile){
  while(!feof(textFile)){
    if(Word *words = getWordsFromTextFile(textFile)){
      addWordsToGraph(graph, words);
      deleteWords(words);
    }
  }
  fclose(textFile);
  assignUbications(*graph);
  updateConditionalProbabilities(*graph);
}
Node *addWordsToGraph(Node **graph, Word *words){
  if(words!=NULL){
    Node *node = addWordToGraph(graph, words);
    Node *nextNode = addWordsToGraph(graph, words->next);
    if(Link *link = searchOrInsertLink(node, nextNode))
      link->count++;
    return node;
  }
  return NULL;
}
void saveNodes(Node *nodes, FILE *graphFile){
  for(; nodes!=NULL; nodes = nodes->next){
    fprintf(graphFile, "%s ", nodes->word);
    fprintf(graphFile, "%d ", nodes->count);
    saveLinks(nodes->links, graphFile);
  }
  fclose(graphFile);
}
void saveLinks(Link *links, FILE *graphFile){
  for(; links!=NULL; links = links->next){
    fprintf(graphFile, "%s ", links->node->word);
    fprintf(graphFile, "%d ", links->count);
  }
  fputc('\n', graphFile);
}
#endif
