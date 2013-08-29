// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/30 05:48:10 by samui>



#include <iostream>
#include "./view.h"

View::View(){
  scale = 1.0;
  posX = 0.0;
  posY = 0.0;
  posZ = 0.0;

//std::cout<<"H"<<std::endl;
}
void View::setN(int n){
  N = n;
  view_count = n;
}
int View::getN(){
  return N;
}
void View::setVC(int n){
  if(n > N || n < 0)
    view_count = N;
  else
    view_count = n;
}
int View::getVC(){
  return view_count;
}
