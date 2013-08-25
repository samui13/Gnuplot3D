// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/25 23:47:12 by samui>

#ifndef __PNG_LOADER__
#define __PNG_LOADER__
#include "png.h"
class PngLoader{
private:
  unsigned int id;
  unsigned int width,height;
  int bpp;
  unsigned char *raw_data;
  unsigned int tex_name;
  char filename[256];
public:
  PngLoader(char *file,int ID);
  void PngLoad();
  ~PngLoader();
  unsigned int getID();
  unsigned int getWidth();
  unsigned int getHeight();
  unsigned char *getRawdata();
  
  unsigned int* setTexname();
  unsigned int getTexname();
};


#endif
