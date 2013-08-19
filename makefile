all: main.cpp ./pngload.o
	g++ -framework OpenGL -framework GLUT -framework Foundation -lpng main.cpp ./lib/PngLoad.o
pngload.o: ./lib/PngLoad.cpp
	g++ -o ./lib/PngLoad.o -c ./lib/PngLoad.cpp
test: test.cpp
	g++ -framework OpenGL -framework GLUT -framework Foundation -lpng test.cpp
