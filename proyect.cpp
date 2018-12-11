
#include <GL/glut.h>
#include <GL/glui.h>
#include <stdio.h>
#include "graph.h"
#include "drawing.h"

double translation[3] = {0.0, 0.0, -100.0};
Node *graph = NULL;
int mainWindow = 0;
int forcesEnable = false;

FILE *getFile();
void display();
void idle();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void printInformation();
FILE *getGraphFile();
void callback(int id);

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(683, 768);
  glutInitWindowPosition(0, 0);
  mainWindow = glutCreateWindow("Dictionary Proyect");
  glutDisplayFunc(display);
  GLUI_Master.set_glutSpecialFunc(special);
  glutReshapeFunc(reshape);
  GLUI_Master.set_glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  GLUI *gluiWindow = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_LEFT);
  gluiWindow->set_main_gfx_window(mainWindow);
  gluiWindow->add_checkbox("Enable forces?", &forcesEnable, -1, callback);
  glutMainLoop();
  deleteNodes(graph);
}
void callback(int id){

}
void idle(){
  if(forcesEnable)
    applyForces(graph);
  glutPostRedisplay();
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
void reshape(int w, int h){
  if(h==0)
    h = 1;
  float ratio = 1.0*w/h;
  glutSetWindow(mainWindow);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLUI_Master.auto_set_viewport();
  gluPerspective(45, ratio, 1, 1000);
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
}
void keyboard(unsigned char key, int x, int y){
  switch(key){
    case '+':
    if(translation[2]<-1)
      translation[2]++;
    break;
    case '-':
    if(translation[2]>-1000)
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
  printf("x: %.3lf\n", translation[0]);
  printf("y: %.3lf\n", translation[1]);
  printf("z: %.3lf\n", translation[2]);
  printf("Words: %d\n", countWords(graph));
  printf("Nodes: %d\n", countNodes(graph));
  printf("NodeLinks: %d\n", countTotalLinks(graph));
  printf("WordLinks: %d\n", countTotalWordLinks(graph));
}
