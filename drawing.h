#ifndef __DRAWING_H__
#define __DRAWING_H__

#include <GL/glut.h>
#include "graph.h"

enum{
  BLACK_COLOR = 0,
  BLUE_COLOR,
  GREEN_COLOR,
  RED_COLOR,
  YELLOW_COLOR,
  GRAY_COLOR
};

void changeColor(int color);
void drawGraph(Node *graph);
void drawLine(int color, Vector ubication1, Vector ubication2);
void drawNodeLinks(Node *nodes);
void drawNodes(Node *nodes);
void drawString(int color, Vector ubication, char *string, void *font);

void drawGraph(Node *graph){
  drawNodeLinks(graph);
  drawNodes(graph);
}
void drawNodeLinks(Node *nodes){
  char buffer[11];
  for(; nodes!=NULL; nodes = nodes->next)
    for(Link *links = nodes->links; links!=NULL; links = links->next){
      drawLine(GRAY_COLOR, nodes->ubication, links->node->ubication);
      sprintf(buffer, "(%1.5lf)", links->probability);
      drawString(GRAY_COLOR, probabilityUbication(nodes, links->node), buffer, GLUT_BITMAP_HELVETICA_10);
    }
}
void drawLine(int color, Vector ubication1, Vector ubication2){
  changeColor(color);
  glBegin(GL_LINES);
  glVertex3d(ubication1.x, ubication1.y, 0);
  glVertex3d(ubication2.x, ubication2.y, 0);
  glEnd();
}
void changeColor(int color){
  switch(color){
    case GRAY_COLOR:
    glColor3f(0.5, 0.5, 0.5);
    break;
    case RED_COLOR:
    glColor3f(1, 0.0, 0.0);
    break;
    case YELLOW_COLOR:
    glColor3f(1, 1, 0.0);
    break;
    case BLUE_COLOR:
    glColor3f(0.0, 0.0, 1.0);
    break;
    case GREEN_COLOR:
    glColor3f(0.25, 1.0, 0.25);
    break;
    case BLACK_COLOR:
    default:
    glColor3f(0.0, 0.0, 0.0);
  }
}
void drawNodes(Node *nodes){
  char buffer[101];
  for(; nodes!=NULL; nodes = nodes->next){
    sprintf(buffer, "%s(%1.5lf)", nodes->word, nodes->probability);
    drawString(nodes->color, nodes->ubication, buffer, GLUT_BITMAP_HELVETICA_18);
  }
}
void drawString(int color, Vector ubication, char *string, void *font){
  changeColor(color);
  glRasterPos3d(ubication.x, ubication.y, 0);
  for(int i = 0; string[i]!='\0'; i++)
    glutBitmapCharacter(font, string[i]);
}

#endif
