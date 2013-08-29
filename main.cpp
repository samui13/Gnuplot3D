// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/29 23:36:49 by samui>

#include <iostream>
#include <cstdio>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include "lib/pngload.h"
#include "lib/texmanage.h"

using namespace std;
PngLoader *p;
TexManage pngs(2);

static void display (){
  PngLoader *test;
  test = pngs.getPng(0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode   (GL_MODELVIEW);
  glLoadIdentity ();

  glBindTexture   (GL_TEXTURE_2D, test->getTexname());

  glBegin       (GL_TRIANGLE_STRIP);
  glColor4f     (1,1,1,1);
    
  glTexCoord2f  (1,0);
  glVertex3f    (1,0,0);

  glTexCoord2f  (1,1);
  glVertex3f    (1,1,0);

  glTexCoord2f  (0,0);
  glVertex3f    (0,0,0);

  glTexCoord2f  (0,1);
  glVertex3f    (0,1,0);

  glEnd         ();

  glutSwapBuffers ();
}

static void reshape (int width, int height){
  glViewport     (0,0, width, height);
  glMatrixMode   (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho        (0, 1, 0, 1, -1, 1);
}

static void idle (){
  glutPostRedisplay();
}


int main(int argc, char **argv){
  char file[256];
  sprintf(file, "./data/split-data1/png/data25.png");

  p = new PngLoader(file,0);
  p->PngLoad();
  
  //p = pngs.getPng(0);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutCreateWindow("MyOpenGL");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);

  
  
  glDisable(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  
  glClearColor (0,0,0,1);
  sprintf(file, "./data/split-data1/png/data25.png");
  pngs.addPng(file);
  sprintf(file, "./data/split-data1/png/data30.png");
  pngs.addPng(file);

  /*
  glGenTextures(1, p->setTexname());
  glBindTexture(GL_TEXTURE_2D, p->getTexname());
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p->getWidth(), p->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)p->getRawdata());
  */
  

  glutMainLoop();

  return 0;
}
