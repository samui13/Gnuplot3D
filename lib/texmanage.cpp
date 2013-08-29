// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/29 23:35:31 by samui>

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

  glGenTextures(1, png_load->setTexname());
  glBindTexture(GL_TEXTURE_2D, png_load->getTexname());
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, png_load->getWidth(), png_load->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)png_load->getRawdata());
  
  /*
  

  glBindTexture(GL_TEXTURE_2D, png_load->getTexname());
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, png_load->getWidth(), png_load->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)png_load->getRawdata());
  */
  list.push_back(png_load);
}

PngLoader* TexManage::getPng(int id){
  return list[id];
}

