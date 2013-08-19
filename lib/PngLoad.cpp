// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/19 03:27:17 by samui>

#include <iostream>
#include <cstdio>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cstring>
#include "./PngLoad.h"
#include "png.h"
using namespace std;


PngLoad::PngLoad(){

}
PngLoad::PngLoad(const char *file,unsigned int ID){
  strcpy(filename,file);
  id = ID;
  //画像ファイルをロードしていく。
  png_structp png_sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop png_ip = png_create_info_struct(png_sp);
  FILE *fp = fopen(file, "rb");
  if (!fp){
    perror(filename);
  }
  png_init_io(png_sp,fp);
  png_read_info(png_sp, png_ip);
  //情報取得,width,height,depthなど
  png_get_IHDR(png_sp, png_ip, (png_uint_32*)&width, (png_uint_32*)&height,&depth, &color_type, &interlace_type, NULL, NULL);
  //メモリ領域の確保
  int rb = png_get_rowbytes(png_sp, png_ip);
  raw_data = new ubyte_t[height * rb];
  ubyte_t **recv = new ubyte_t*[height];
  for (int i = 0; i < height; i++)
    recv[i] = &raw_data[i * rb];
  png_read_image(png_sp, recv);
  png_read_end(png_sp, png_ip);
  png_destroy_read_struct(&png_sp, &png_ip, NULL);
  fclose(fp);
  delete[] recv;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, raw_data);
}
PngLoad::~PngLoad(){
  free(raw_data);
}
  
ubyte_t* PngLoad::rawData(){
  return raw_data;
}
unsigned int PngLoad::getID(){
  return id;
}
unsigned int PngLoad::getWidth(){
  return width;
}
unsigned int PngLoad::getHeight(){
  return height;
}

