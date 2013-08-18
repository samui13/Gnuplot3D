#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Last-Updated : <2013/08/18 22:47:11 by samui>

import sys,os

def mkdir(folder):
    if not os.path.isdir(folder):
        os.system("mkdir {0}".format(folder))


if __name__  == "__main__":
    data_file = os.path.abspath(sys.argv[1])
    root,ext = os.path.splitext(os.path.basename(data_file))
    data_folder = os.path.join(os.path.dirname(data_file),"split-{0}".format(root))
    sdata_folder = os.path.join(os.path.dirname(data_file),"split-{0}".format(root),"data")
    png_folder = os.path.join(data_folder,"png")
    
    gnuplot_file = os.path.join(data_folder,"gnuplot.txt")
    

    mkdir(data_folder)
    mkdir(png_folder)
    mkdir(sdata_folder)

    #Split Phase
    Nx = 50
    Ny = 50
    Nz = 50
    data = open(data_file,"r")
    data_list = []
    for k in range(Nz+1):
        out_data = os.path.join(sdata_folder,"data{0}.txt".format(k))
        data_list.append(out_data)
        out_file = open(out_data,"w");
        for j in range(0,Ny+1):
            for i in range(0,Nx+1):
                out_file.write(data.readline())
            out_file.write(data.readline())
        out_file.close()
        data.readline()        
    data.close()

    # Gnuplot File Output
    gnup_file = open(gnuplot_file,"w")
    gnup_file.write("set pm3d map\n")
    gnup_file.write("set cbrange[0:1.0]\n")
    gnup_file.write("set term png\n")
    
    for data in (data_list):
        root,ext = os.path.splitext(os.path.basename(data))
        gnup_file.write("set output \"{0}\"\n".format(os.path.join(png_folder,"{0}.png".format(root))))
        gnup_file.write("splot \"{0}\" title \"\"\n".format(data))
    gnup_file.close()
    # Gnuplot Image file
    os.system("gnuplot {0}".format(gnuplot_file))
