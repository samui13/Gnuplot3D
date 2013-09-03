#ifndef __TEX_MANAGE__
#define __TEX_MANAGE__
#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "PngLoad.h"

class TexManage{
private:
  int N;
  GLuint *tex_ID;
  std::vector<PngLoader*> list;
public:
  TexManage(int n);
  void addPng(char *file);
  void registPng(PngLoader *png_obj);
  void ChangeMode(int mode,int n);
  PngLoader* getPng(int id);
  int getN();
};

#endif
