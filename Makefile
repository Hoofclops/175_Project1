OBJS = main.o Renderer.o DataParser.o DataSerializer.o \
       Line.o Polygon.o Point.o Vector3.o Vector2i.o \
       Color.o GraphicsAlgorithm.o

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
    $(CC) $(LFLAGS) $(OBJS) -o p1

main.o : main.cpp OpenGL/gl.h OpenGL/glu.h GLUT/glut.h Vector2i.h Color.h Renderer.h
    $(CC) $(CFLAGS) main.cpp

Renderer.o : Renderer.h Renderer.cpp OpenGL/gl.h OpenGL/glu.h GLUT/glut.h Vector2i.h Color.h Point.h Line.h Polygon.h GraphicsAlgorithm.h
	$(CC) $(CFLAGS) Renderer.cpp

DataParser.o : DataParser.h DataParser.cpp 
	$(CC) $(CFLAGS) DataParser.cpp



clean:
    \rm *.o *~ p1