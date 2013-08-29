// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/30 05:27:51 by samui>

#ifndef __VIEW_CLASS__
#define __VIEW_CLASS__
class View{
public:
  float rotX,rotY;
  float bgn_y,bgn_x;
  int mouseX,mouseY;
  int fX,fY;
  float posX,posY,posZ;
  float rot;
  float scale;
  
private:
  int N;
  int view_count;
public:
  View();
  void setN(int n);
  int getN();
  void setVC(int n);
  int getVC();
};
#endif
