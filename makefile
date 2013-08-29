all: main.cpp ./obj/pngload.o ./obj/texmanage.o ./obj/view.o
	g++ -framework OpenGL -framework GLUT -framework Foundation -lpng main.cpp ./obj/pngload.o ./obj/texmanage.o ./obj/view.o
./obj/pngload.o: ./lib/PngLoad.cpp
	g++ -o ./obj/PngLoad.o -c ./lib/PngLoad.cpp

./obj/texmanage.o: ./lib/texmanage.cpp
	g++ -o ./obj/texmanage.o -c ./lib/texmanage.cpp 
./obj/view.o: ./src/view.cpp
	g++ -o ./obj/view.o -c ./src/view.cpp


test02: test02.cpp 
	g++ -framework OpenGL -framework GLUT -framework Foundation -lpng test02.cpp ./obj/pngload.o ./obj/texmanage.o
