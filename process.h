// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/30 03:47:11 by samui>
#ifndef __PROCESS__
#define __PROCESS__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "lib/pngload.h"
#include "lib/texmanage.h"

class ProcessGL{
private:
  GLuint rectlists;
  TexManage *img;
public:
  ProcessGL();
private:
  void Display();
public:
  static void display();
  static void timer();
  static void reshape(int width,int height);
  static void spkey(int key,int x,int y);
  static void idle();
public:
  void Init();
private:
  GLuint InitRect();
};

ProcessGL p;

ProcessGL::ProcessGL(){
}

void ProcessGL::Init(){
  int i;
  char file[256];
  rectlists = InitRect();
  img = new TexManage(50);
  for(i = 0; i < 50; i++){
    sprintf(file, "./data/split-data1/png/data%d.png",i);
    img->addPng(file);
  }
}
void ProcessGL::Display(){
  PngLoader *test;
  int i,j;

  for(i = 0; i < 50; i++){
    test = img->getPng(i);  
    glPushMatrix();
      glTranslatef(0.0,0.0,i*0.02);
      glBindTexture(GL_TEXTURE_2D,test->getTexname());
      glScalef(test->getRateX(),1.0,1.0);
      for(j = 0; j < 20; j++){
	glTranslatef(0.0,0.0,0.001);
	glPushMatrix();
	  glCallList(rectlists);
	glPopMatrix();
      }
    glPopMatrix();
  }

}
void ProcessGL::display(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  glAlphaFunc(GL_GEQUAL,0.5);
  glEnable(GL_ALPHA_TEST);

  
  glPushMatrix();
  
  glScalef(2.0,2.0,2.0);
  glTranslatef(0.0,0.0,-15.0);
  glRotatef(80.0,0.0,1.0,0.0);
  
  p.Display();
  glPopMatrix();
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_TEXTURE_2D);
  
  glutSwapBuffers();
  
}

void ProcessGL::timer(){

}

void ProcessGL::reshape(int width,int height){
  glViewport(0,0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 10000.0);
  glFrustum(-1.0, 1.0, -1.0, 1.0, 10.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
  //glOrtho(-1, 1, -1, 1, -1, 1);
}
void ProcessGL::spkey(int key,int x,int y){

}
void ProcessGL::idle(){
  glutPostRedisplay();
}
GLuint ProcessGL::InitRect(){
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
#endif



