// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/19 03:33:00 by samui>
#include <iostream>
#include <cstdio>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "png.h"
#include "./lib/PngLoad.h"
using namespace std;
#define WIDTH 640
#define HEIGHT 480
PngLoad *test;
GLuint texName[1];

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glRotatef(45.0, 0.0, 1.0, 0.0);
  glBindTexture(GL_TEXTURE_2D, (*test).getID());
  glBegin(GL_QUADS);
  //glColor3f(1.0, 0.0, 0.0);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1.0,1.0,0.0);

  glTexCoord2f(-1.0, 1.0);
  glVertex3f(-1.0,1.0,0.0);

  glTexCoord2f(-1.0, -1.0);
  glVertex3f(-1.0,-1.0,0.0);

  glTexCoord2f(1.0, -1.0);
  glVertex3f(1.0,-1.0,0.0);
  glEnd();
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);


  //init Display
  glClearColor(1.0, 1.0, 1.0, 1.0);
  /*
  glEnable(GL_TEXTURE_2D);
  glAlphaFunc(GL_GEQUAL,0.5);
  glEnable(GL_ALPHA_TEST);
  */

  char file[256];
  sprintf(file,"./data/split-data1/png/data25.png");
  glGenTextures(1,texName);
  test = new PngLoad(file,0);
  
  glutMainLoop();
  return 0;
}
