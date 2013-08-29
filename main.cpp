// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/30 05:21:39 by samui>

#include <iostream>
#include <cstdio>
#include <iostream>
#include "process.h"

using namespace std;

int main(int argc, char **argv){
  char file[256];
  int i;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512*2, 2*512);
  glutCreateWindow("3DPlotter");

  glutDisplayFunc(p.display);
  glutReshapeFunc(p.reshape);
  glutKeyboardFunc(p.keyfunc);
  glutSpecialFunc(p.keyspecial);
  glutIdleFunc(p.idle);
  glutMotionFunc(p.DragFunc);
  
  glDisable(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  
  glClearColor (0.1,0.1,0.1,1);
  p.Init();
  glutMainLoop();

  return 0;
}
