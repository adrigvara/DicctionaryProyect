#ifndef __WORD_H__
#define __WORD_H__

#include <stdlib.h>
#include <string.h>

#define MAXIMUM_WORD_LENGTH 25

struct Word{
  char word[MAXIMUM_WORD_LENGTH+1];
  unsigned int count;
  Word *next;
};

Word *includeWord(Word **pointer, Word *word);
Word *allocateWordCount(char *word, unsigned int count);

Word *insertWord(Word **pointer, char *word, unsigned int count){
  while(*pointer!=NULL)
    pointer = &(*pointer)->next;
  return includeWord(pointer, allocateWordCount(word, count));
}
Word *includeWord(Word **pointer, Word *word){
  if(word!=NULL){
    word->next = *pointer;
    *pointer = word;
  }
  return word;
}
Word *allocateWord(char *word){
  Word *newWord = (Word*)calloc(1, sizeof(Word));
  if(newWord!=NULL)
    strcpy(newWord->word, word);
  return newWord;
}
Word *allocateWordCount(char *word, unsigned int count){
  Word *newWord = allocateWord(word);
  if(newWord!=NULL)
    newWord->count = count;
  return newWord;
}
void deleteWords(Word *words){
  if(words!=NULL){
    deleteWords(words->next);
    free(words);
  }
}

#endif
