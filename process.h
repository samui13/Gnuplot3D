// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/30 05:50:12 by samui>
#ifndef __PROCESS__
#define __PROCESS__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "lib/pngload.h"
#include "lib/texmanage.h"
#include "src/view.h"

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
  static void DragFunc(int x,int y);
  static void MouseFunc(int button,int stat, int x, int y);
  static void reshape(int width,int height);
  static void keyfunc(unsigned char key,int x,int y);
  static void keyspecial(int key,int x,int y);
  static void idle();
public:
  void Init();
private:
  GLuint InitRect();
};

ProcessGL p;
View views;
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
  views.setN(50);
    
}
void ProcessGL::Display(){
  PngLoader *test;
  int i,j;

  for(i = 0; i < views.getVC(); i++){
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
  
  glTranslatef(0.0,0.0,-15.0);
  glTranslatef(views.posX,views.posY,views.posZ);
  glRotatef(views.rotX, 1.0, 0.0, 0.0);
  glRotatef(views.rotY, 0.0, 1.0, 0.0);
  glScalef(views.scale*1.0,views.scale*1.0,views.scale);
  //glRotatef(80.0,0.0,1.0,0.0);
  
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
void ProcessGL::keyspecial(int key,int x,int y){
  switch(key){
  case GLUT_KEY_UP:
    views.posZ+=0.01;
    break;
  case GLUT_KEY_DOWN:
    views.posZ-=0.01;
    break;
  case GLUT_KEY_LEFT:
    views.posX+=0.01;
    break;
  case GLUT_KEY_RIGHT:
    views.posX-=0.01;
    break;
  default:
    break;
  }
}
void ProcessGL::keyfunc(unsigned char key,int x,int y){
  switch(key){
  case 'q':
    exit(1);
    break;
  case 'n':
    views.setVC(views.getVC()-1);
    break;
  case 'm':
    views.setVC(views.getVC()+1);
    break;
  default:
    break;
  }
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
void ProcessGL::DragFunc(int x,int y){
  views.rotX = (float)(y-views.mouseY)+views.fX;
  views.rotY = (float)(x-views.mouseX)+views.fY;
  views.rotX=int(views.rotX)%360;
  views.rotY=int(views.rotY)%360;
}
void ProcessGL::MouseFunc(int button,int stat, int x, int y){
  if(stat == GLUT_DOWN && button == GLUT_LEFT){
    views.mouseX = x;
    views.mouseY = y;
    views.fX = views.rotX;
    views.fY = views.rotY;
  }
  if(stat == GLUT_DOWN && button == GLUT_RIGHT_BUTTON){
    // Cannot use this
    views.scale+=0.5;
    std::cout<<"H"<<std::endl;
  }
  
}
#endif



