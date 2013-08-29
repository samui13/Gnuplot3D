// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/30 03:17:30 by samui>

#include <iostream>
#include <cstdio>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include "process.h"
#include "lib/pngload.h"
#include "lib/texmanage.h"

using namespace std;
//PngLoader *p;
TexManage pngs(50);
static GLuint rectlist;

static void display (){
  PngLoader *test;
  int i,j;
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  glAlphaFunc(GL_GEQUAL,0.5);
  glEnable(GL_ALPHA_TEST);

  
  glPushMatrix();
  
  glScalef(2.0,2.0,2.0);
  glTranslatef(0.0,0.0,-15.0);
  glRotatef(80.0,0.0,1.0,0.0);
  
  for(i = 0; i < 50; i++){
    test = pngs.getPng(i);  
    glPushMatrix();
      glTranslatef(0.0,0.0,i*0.02);
      glBindTexture(GL_TEXTURE_2D,test->getTexname());
      glScalef(test->getRateX(),1.0,1.0);
      for(j = 0; j < 20; j++){
	glTranslatef(0.0,0.0,0.001);
	glPushMatrix();
          glCallList(rectlist);
	glPopMatrix();
      }
    glPopMatrix();
  }

  glPopMatrix();
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_TEXTURE_2D);
  
  glutSwapBuffers();
}

static void reshape (int width, int height){
  glViewport(0,0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 10000.0);
  glFrustum(-1.0, 1.0, -1.0, 1.0, 10.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
  //glOrtho(-1, 1, -1, 1, -1, 1);
}

static void idle (){
  glutPostRedisplay();
}

GLuint InitRect(){
  GLint list;
  list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3f(-1.0,-1.0,0.0);
    glTexCoord2f(0.0,1.0); glVertex3f(-1.0,1.0,0.0);
    glTexCoord2f(1.0,1.0); glVertex3f(1.0,1.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(1.0,-1.0,0.0);
  glEnd();
  glEndList();
  
  return list;
}

int main(int argc, char **argv){
  char file[256];
  int i;
  
  /*
  sprintf(file, "./data/split-data1/png/data25.png");
  p = new PngLoader(file,0);
  p->PngLoad();
  //p = pngs.getPng(0);
  */


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutCreateWindow("3DPlotter");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  
  glDisable(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  
  glClearColor (0.1,0.1,0.1,1);
  for(i = 0; i < 50; i++){
    sprintf(file, "./data/split-data1/png/data%d.png",i);
    pngs.addPng(file);
  }
  rectlist = InitRect();
  glutMainLoop();

  return 0;
}
