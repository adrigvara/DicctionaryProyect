#ifndef __PARSING_H__
#define __PARSING_H__

#include <stdio.h>
#include "word.h"
#include <ctype.h>
#include <stdbool.h>

Word *getWordsFromTextFile(FILE *textFile);
bool insertWordFromTextFile(Word **pointer, FILE *textFile);
bool isSpecialAlphabetic(int c);
bool isSpecialPunctuation(int c);
bool parseWordFromFile(char buffer[MAXIMUM_WORD_LENGTH+1], FILE *file);
int specialToPunctuation(int c);
int specialToAlphabetic(int c);
bool insertWordFromGraphFile(Word **pointer, FILE *graphFile);
bool parseCountFromGraphFile(char *buffer, FILE *graphFile);

Word *getWordsFromPhrase(char *phrase){
  return NULL;
}
Word *getWordsFromGraphFile(FILE *graphFile){
  Word *words = NULL;
  while(insertWordFromGraphFile(&words, graphFile))
    ;
  return words;
}
Word *getWordsFromTextFile(FILE *textFile){
  Word *words = NULL;
  while(insertWordFromTextFile(&words, textFile))
    ;
  return words;
}
bool insertWordFromTextFile(Word **pointer, FILE *textFile){
  char buffer[MAXIMUM_WORD_LENGTH+1];
  memset(buffer, '\0', MAXIMUM_WORD_LENGTH+1);
  bool flag = parseWordFromFile(buffer, textFile);
  if(strlen(buffer)>0)
    insertWord(pointer, buffer, 1);
  return flag;
}
bool parseWordFromFile(char *buffer, FILE *file){
  for(int i = 0, c = getc(file); i<MAXIMUM_WORD_LENGTH; i++, c = getc(file)){
    if(c==EOF)
      return false;
    else if(isSpecialAlphabetic(c))
      c = specialToAlphabetic(getc(file));
    else if(isSpecialPunctuation(c))
      c = specialToPunctuation(getc(file));
    if(isalpha(c))
      buffer[i] = tolower(c);
    else
      return !ispunct(c);
  }
  return true;
}
bool insertWordFromGraphFile(Word **pointer, FILE *graphFile){
  char wordBuffer[MAXIMUM_WORD_LENGTH+1];
  memset(wordBuffer, '\0', MAXIMUM_WORD_LENGTH+1);
  char countBuffer[12];
  memset(countBuffer, '\0', 12);
  parseWordFromFile(wordBuffer, graphFile);
  bool flag = parseCountFromGraphFile(countBuffer, graphFile);
  insertWord(pointer, wordBuffer, atoi(countBuffer));
  return flag;
}
bool parseCountFromGraphFile(char *buffer, FILE *file){
  for(int i = 0, c = getc(file); i<11; i++, c = getc(file)){
    if(c==EOF)
      return false;
    else if(isdigit(c))
      buffer[i] = c;
    else
      return c!='\n';
  }
  return true;
}
bool isSpecialPunctuation(int c){
  return c==-62 || c==194;
}
bool isSpecialAlphabetic(int c){
  return c==-61 || c==195;
}
int specialToPunctuation(int c){
  switch(c){
    case 191:
    case -65:
    return '?';
    case 161:
    case -95:
    return '!';
    default:
    return c;
  }
}
int specialToAlphabetic(int c){
  switch(c){
    case 177:
    case -79:
    return 'n';
    case 161:
    case -95:
    return 'a';
    case 169:
    case -87:
    return 'e';
    case 173:
    case -83:
    return 'i';
    case 179:
    case -77:
    return 'o';
    case 186:
    case 188:
    case -70:
    case -68:
    return 'u';
    case 145:
    return 'N';
    case 129:
    case -127:
    return 'A';
    case 137:
    case -119:
    return 'E';
    case 141:
    case -115:
    return 'I';
    case -109:
    case 147:
    return 'O';
    case 154:
    case 156:
    case -102:
    case -100:
    return 'U';
    default:
    return c;
  }
}
#endif
