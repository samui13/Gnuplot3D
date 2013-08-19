// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/19 03:07:18 by samui>

#ifndef __PNG_LOADER__
#define __PNG_LOADER__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

typedef unsigned char ubyte_t;
class PngLoad{
private:
  unsigned int id;
  unsigned int width,height;
  ubyte_t *raw_data;
  int depth,color_type,interlace_type;
  char filename[256];
  void init();
public:
  PngLoad();
  PngLoad(const char *file,unsigned int ID);
  ~PngLoad();
  
  ubyte_t* rawData();
  unsigned int getID();
  unsigned int getWidth();
  unsigned int getHeight();

};
 

#endif
