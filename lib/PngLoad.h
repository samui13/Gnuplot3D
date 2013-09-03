// -*- coding: utf-8 -*-
// Last-Updated : <2013/09/03 09:03:31 by samui>

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
  void PngReload(int mode);
  ~PngLoader();
  unsigned int getID();
  unsigned int getWidth();
  unsigned int getHeight();
  double getRateX();
  double getRateY();
  unsigned char *getRawdata();
  
  unsigned int* setTexname();
  unsigned int getTexname();
};


#endif
