// -*- coding: utf-8 -*-
// Last-Updated : <2013/08/25 23:46:54 by samui>

#include <iostream>
#include "./PngLoad.h"

unsigned char *PngLoader::getRawdata(){
  return raw_data;
}
unsigned int PngLoader::getTexname(){
  return tex_name;
}
unsigned int* PngLoader::setTexname(){
  return &tex_name;
}
PngLoader::PngLoader(char *file,int ID){
  strcpy(filename,file);
  id = ID;
  //PngLoad();
}
void PngLoader::PngLoad(){
  int i,j;
  FILE *fp = fopen(filename,"rb");
  png_structp png_sp;
  png_infop png_ip;
  if(!fp){
    std::cout<<"Cannot open file:"<<filename<<std::endl;
    return;
  }

  png_sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_ip = png_create_info_struct(png_sp);
  
  if(setjmp(png_jmpbuf(png_sp))){
    png_destroy_read_struct(&png_sp,&png_ip,NULL);
    return;
  }
  
  png_init_io(png_sp,fp);
  png_read_png(png_sp,png_ip,PNG_TRANSFORM_EXPAND,NULL);
 
  png_byte** row_pointers = png_get_rows (png_sp,png_ip);
  width = 640;
  height = 480;
  bpp = 3;

  raw_data = new unsigned char[width*height*bpp];
  /*
  for(j = 0; j < height; j++){
    for(i = 0; i < width; i++){
      raw_data[j*height+i][0] = row_pointers[j*height+i][0];
      raw_data[j*height+i][1] = row_pointers[j*height+i][1];
      raw_data[j*height+i][2] = row_pointers[j*height+i][2];
    }
  }
*/

  for(i = 0; i < height; i++){
    memcpy(raw_data+(i*width*bpp),row_pointers[height-i-1],width*bpp);
  }

  fclose(fp);
  png_destroy_read_struct(&png_sp,&png_ip,NULL);
}

PngLoader::~PngLoader(){
  delete raw_data;
}
unsigned int PngLoader::getID(){
  return id;
}
unsigned int PngLoader::getWidth(){
  return width;
}
unsigned int PngLoader::getHeight(){
  return height;
}
