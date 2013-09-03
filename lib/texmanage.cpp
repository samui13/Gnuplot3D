// -*- coding: utf-8 -*-
// Last-Updated : <2013/09/03 10:11:38 by samui>

#include <iostream>
#include <cstdio>
#include "texmanage.h"

TexManage::TexManage(int n){
  N = n;
  tex_ID = new GLuint[N];

}

void TexManage::addPng(char *file){
  int tid = list.size();
  PngLoader *png_load = new PngLoader(file,list.size());
  png_load->PngLoad();
  registPng(png_load);
  list.push_back(png_load);
}

void TexManage::ChangeMode(int mode,int n){
  PngLoader *png = list[n];
  if(png == NULL){
    exit(1);
  }
  png->PngReload(mode);
  registPng(png);
}

void TexManage::registPng(PngLoader *png_obj){
  glGenTextures(1, png_obj->setTexname());
  glBindTexture(GL_TEXTURE_2D, png_obj->getTexname());
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  /*
    //拡大対策
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
  */
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Alpha値なし。
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, png_load->getWidth(), png_load->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)png_load->getRawdata());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png_obj->getWidth(), png_obj->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)png_obj->getRawdata());
  
}
PngLoader* TexManage::getPng(int id){
  return list[id];
}

int TexManage::getN(){
  return N;
}
