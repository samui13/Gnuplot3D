// -*- coding: utf-8 -*-
// Last-Updated : <2013/09/03 10:18:57 by samui>
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
  void ChangeColor(int mode){
    int i;
    for(i = 0; i < img->getN();i++){
      img->ChangeMode(mode,i);
    }
  }
public:
  static void display();
  static void timer();
  static void DragFunc(int x,int y);
  static void MouseFunc(int button,int stat, int x, int y);
  static void reshape(int width,int height);
  static void keyfunc(unsigned char key,int x,int y);
  static void keyspecial(int key,int x,int y);
  static void idle();
  static void capture();
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
    //img->ChangeMode(3,i);
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
  glEnable(GL_DEPTH_TEST); //両面表示

  
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
  glDisable(GL_DEPTH_TEST);
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
  int i;
  switch(key){
  case 'r':
    p.ChangeColor(3);
    break;
  case 'g':
    p.ChangeColor(2);
    break;
  case 'b':
    p.ChangeColor(1);
    break;
  case 'a':
    p.ChangeColor(0);
    break;
  case 'q':
    exit(1);
    break;
  case 'c':
    capture();
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
void ProcessGL::capture(){
  // Copy from here
  //http://d.hatena.ne.jp/yatt/20091004/1254678048

  const char filepath[] = "./output.png";
  png_bytep raw1D;
  png_bytepp raw2D;
  int i;
  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);

  // 構造体確保
  FILE *fp = fopen(filepath, "wb");
  png_structp pp = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop ip = png_create_info_struct(pp);
  // 書き込み準備
  png_init_io(pp, fp);
  png_set_IHDR(pp, ip, width, height,
	       8, // 8bit以外にするなら変える
	       PNG_COLOR_TYPE_RGBA, // RGBA以外にするなら変える
	       PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  // ピクセル領域確保
  raw1D = (png_bytep)malloc(height * png_get_rowbytes(pp, ip));
  raw2D = (png_bytepp)malloc(height * sizeof(png_bytep));
  for (i = 0; i < height; i++)
    raw2D[i] = &raw1D[i*png_get_rowbytes(pp, ip)];
  // 画像のキャプチャ
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 初期値は4
  glReadPixels(0, 0, width, height,
	       GL_RGBA, // RGBA以外にするなら変える
	       GL_UNSIGNED_BYTE, // 8bit以外にするなら変える
	       (void*)raw1D);
  // 上下反転
  for (i = 0; i < height/ 2; i++){
    png_bytep swp = raw2D[i];
    raw2D[i] = raw2D[height - i - 1];
    raw2D[height - i - 1] = swp;
  }
  // 書き込み
  png_write_info(pp, ip);
  png_write_image(pp, raw2D);
  png_write_end(pp, ip);
  // 開放
  png_destroy_write_struct(&pp, &ip);
  fclose(fp);
  free(raw1D);
  free(raw2D);

  printf("write out screen capture to '%s'\n", filepath);
}
#endif



