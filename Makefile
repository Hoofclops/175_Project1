makefile:
all: project1

project1: project1.o
	g++ -lglut -lGL -Wall Color.cpp Line.cpp Vector2i.cpp Polygon.cpp GraphicsAlgorithm.cpp Vector3.cpp ObjectEditor.cpp Renderer.cpp InputOutputUtility.cpp main.cpp Point.cpp -o project1.o
	
clean:
	-rm project1.o
