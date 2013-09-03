// -*- coding: utf-8 -*-
// Last-Updated : <2013/09/03 10:21:09 by samui>

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
 
  png_byte** raw_pointers = png_get_rows (png_sp,png_ip);
  width = 640;
  height = 480;
  bpp = 4;

  raw_data = new unsigned char[width*height*bpp];
  
  for(j = 0; j < height; j++){
    for(i = 0; i < width; i++){
      //テクスチャにAlpha値を入れる場合
      raw_data[j*width*4+(i*4)+0] = raw_pointers[height-j-1][i*3];
      raw_data[j*width*4+(i*4)+1] = raw_pointers[height-j-1][i*3+1];
      raw_data[j*width*4+(i*4)+2] = raw_pointers[height-j-1][i*3+2];
      raw_data[j*width*4+(i*4)+3] = 255;
      if(raw_data[j*width*4+(i*4)+0] == 255 && raw_data[j*width*4+(i*4)+1] == 255 && raw_data[j*width*4+(i*4)+2] == 255){
	raw_data[j*width*4+(i*4)+3] = 0;
      }
      /*
      if(raw_data[j*width*4+(i*4)+0] == 0 && raw_data[j*width*4+(i*4)+1] == 0 && raw_data[j*width*4+(i*4)+2] == 0){
	raw_data[j*width*4+(i*4)+3] = 0;
      }
      */
      /*
      if(i%4 == 0)
	raw_data[j*width*4+i] = 0;
      else if(i%4 == 1)
	raw_data[j*width*4+i] = 255;
      else if(i%4  == 2)
	raw_data[j*width*4+i] = 0;
      else
	raw_data[j*width*4+i] = 128.0; //これより低い値では表示しない
      */
    }
  }

  /*
    Alpha値がない場合はこれでいい
  for(j = 0; j < height; j++){
    for(i = 0; i < width*3; i++){
      raw_data[j*width*3+i] = raw_pointers[height-j-1][i];
    }
  }

  for(i = 0; i < height; i++){
    memcpy(raw_data+(i*width*bpp),raw_pointers[height-i-1],width*bpp);
  }
  */

  fclose(fp);
  png_destroy_read_struct(&png_sp,&png_ip,NULL);
}

void PngLoader::PngReload(int mode){
  int i,j;
  unsigned char average;
  for(j = 0; j < height; j++){
    for(i = 0; i < width; i++){
      if(mode == 0){
	raw_data[j*width*4+(i*4)+3] = 255;
      }
      
      if(raw_data[j*width*4+(i*4)+0] == 255 && raw_data[j*width*4+(i*4)+1] == 255 && raw_data[j*width*4+(i*4)+2] == 255){
	raw_data[j*width*4+(i*4)+3] = 0;
      }

      average = (raw_data[j*width*4+(i*4)+0]/3+raw_data[j*width*4+(i*4)+1]/3+raw_data[j*width*4+(i*4)+2]/3);
      if(mode == 1 && average > raw_data[j*width*4+(i*4)+0]){
	raw_data[j*width*4+(i*4)+3] = 0;
      }
      if(mode == 2 && average > raw_data[j*width*4+(i*4)+1]){
	raw_data[j*width*4+(i*4)+3] = 0;
      }
      if(mode == 3 && average > raw_data[j*width*4+(i*4)+2]){
	raw_data[j*width*4+(i*4)+3] = 0;
      }
    }

  }
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
double PngLoader::getRateX(){
  return (double)width/(double)height;
}
double PngLoader::getRateY(){
  return (double)height/(double)width;
}
