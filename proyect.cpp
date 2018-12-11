
#include <GL/glut.h>

#include <stdio.h>
#include "graph.h"
#include "drawing.h"

double translation[3] = {0.0, 0.0, -100.0};
Node *graph = NULL;
int mainWindow = 0;
bool forcesEnable = false;

FILE *getFile();
void display();
void idle();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void printInformation();
FILE *getGraphFile();

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(683, 768);
  glutInitWindowPosition(0, 0);
  mainWindow = glutCreateWindow("Dictionary Proyect");
  glutDisplayFunc(display);
  glutSpecialFunc(special);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  deleteNodes(graph);
}
void idle(){
  if(forcesEnable)
    applyForces(graph);
  display();
}
void display(){
  glutSetWindow(mainWindow);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glTranslated(translation[0], translation[1], translation[2]);
  drawGraph(graph);
  glutSwapBuffers();
}
void reshape(int width, int height){
  glutSetWindow(mainWindow);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}
void special(int key, int x, int y){
  switch(key){
    case GLUT_KEY_LEFT:
    translation[0]++;
    break;
    case GLUT_KEY_RIGHT:
    translation[0]--;
    break;
    case GLUT_KEY_DOWN:
    translation[1]++;
    break;
    case GLUT_KEY_UP:
    translation[1]--;
    break;
  }
  //printf("(x:%.2lf, y:%.2lf, z:%.2lf)\n", translation[0], translation[1], translation[2]);
}
void keyboard(unsigned char key, int x, int y){
  switch(key){
    case '+':
    if(translation[2]<-1)
      translation[2]++;
    break;
    case '-':
    if(translation[2]>-100)
      translation[2]--;
    break;
    case 'F':
    case 'f':
    forcesEnable = !forcesEnable;
    break;
    case 'E':
    case 'e':
    deleteNodes(graph);
    exit(0);
    break;
    case 'I':
    case 'i':
    printInformation();
    break;
    case 'T':
    case 't':
    addTextFileToGraph(&graph, getFile());
    break;
    case 'G':
    case 'g':
    addGraphFileToGraph(&graph, getFile());
    break;
    case 'S':
    case 's':
    saveNodes(graph, getGraphFile());
    break;
    case 'D':
    case 'd':
    deleteNodes(graph);
    graph = NULL;
    break;
  }
}
FILE *getFile(){
  char filePath[50];
  printf("File path:\n");
  scanf("%s", filePath);
  return fopen(filePath, "r");
}
FILE *getGraphFile(){
  char filePath[50];
  printf("File path:\n");
  scanf("%s", filePath);
  return fopen(filePath, "w");
}
void printInformation(){
  printf("Words :%d\n", countWords(graph));
  printf("Nodes :%d\n", countNodes(graph));
  printf("NodeLinks :%d\n", countTotalLinks(graph));
  printf("WordLinks :%d\n", countTotalWordLinks(graph));
}
