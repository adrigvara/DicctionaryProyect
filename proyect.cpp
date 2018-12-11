
#include <GL/glut.h>
#include <GL/glui.h>
#include <stdio.h>
#include "graph.h"
#include "drawing.h"

enum{
  ADD_TEXT_FILE = 1,
  ADD_GRAPH_FILE,
  SAVE_GRAPH,
  DELETE_NODES,
  CLEAR_FILE_PATH
};

#define MAXIMUM_FILE_PATH_LENGTH 100

char filePath[MAXIMUM_FILE_PATH_LENGTH+1];
double translation[3] = {0.0, 0.0, -100.0};
Node *graph = NULL;
int mainWindow = 0;
int forcesEnable = false;

FILE *getWriteFile();
FILE *getReadFile();
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
  GLUI_Master.set_glutDisplayFunc(display);
  GLUI_Master.set_glutSpecialFunc(special);
  GLUI_Master.set_glutReshapeFunc(reshape);
  GLUI_Master.set_glutIdleFunc(idle);
  GLUI_Master.set_glutKeyboardFunc(keyboard);
  GLUI *gluiWindow = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_LEFT);
  gluiWindow->set_main_gfx_window(mainWindow);
  GLUI_Panel *filesPanel = gluiWindow->add_panel("Files", GLUI_PANEL_EMBOSSED);
  gluiWindow->add_edittext_to_panel(filesPanel, "File path", GLUI_EDITTEXT_TEXT, filePath, -1, callback);
  gluiWindow->add_button_to_panel(filesPanel, "Add text file", ADD_TEXT_FILE, callback);
  gluiWindow->add_button_to_panel(filesPanel, "Save graph", SAVE_GRAPH, callback);
  gluiWindow->add_button_to_panel(filesPanel, "Load graph", ADD_GRAPH_FILE, callback);
  gluiWindow->add_button_to_panel(filesPanel, "Clear path", CLEAR_FILE_PATH, callback);
  GLUI_Panel *optionsPanel = gluiWindow->add_panel("Options", GLUI_PANEL_EMBOSSED);
  gluiWindow->add_checkbox_to_panel(optionsPanel, "Enable forces?", &forcesEnable, -1, callback);
  gluiWindow->add_button_to_panel(optionsPanel, "Delete Graph", DELETE_NODES, callback);
  glutMainLoop();
  deleteNodes(graph);
}
void callback(int id){
  switch(id){
    case ADD_TEXT_FILE:
    addTextFileToGraph(&graph, fopen(filePath, "r"));
    break;
    case ADD_GRAPH_FILE:
    addGraphFileToGraph(&graph, fopen(filePath, "r"));
    break;
    case SAVE_GRAPH:
    saveNodes(graph, fopen(filePath, "w"));
    break;
    case DELETE_NODES:
    deleteNodes(graph);
    break;
    case CLEAR_FILE_PATH:
    memset(filePath, '\0', MAXIMUM_FILE_PATH_LENGTH+1);
    break;
  }
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
    addTextFileToGraph(&graph, getReadFile());
    break;
    case 'G':
    case 'g':
    addGraphFileToGraph(&graph, getReadFile());
    break;
    case 'S':
    case 's':
    saveNodes(graph, getWriteFile());
    break;
    case 'D':
    case 'd':
    deleteNodes(graph);
    graph = NULL;
    break;
  }
}
FILE *getReadFile(){
  char filePath[50];
  printf("File Path:\n");
  scanf("%s", filePath);
  return fopen(filePath, "r");
}
FILE *getWriteFile(){
  char filePath[50];
  printf("File Path:\n");
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
