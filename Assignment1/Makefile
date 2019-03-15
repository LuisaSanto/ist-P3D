CC=g++ -std=c++11

CFLAGS=-c 
OPENGLFLAGS= -lglut -lGLU -lGL -lGLEW

all: Point.o Ray.o Camera.o Color.o Light.o Material.o Sphere.o Plane.o Cylinder.o Scene.o main.o
	$(CC) Point.o Ray.o Color.o Camera.o Light.o Material.o Sphere.o Plane.o Cylinder.o Scene.o main.o -o main $(OPENGLFLAGS) 


Point.o: Assets/Point.cpp
	$(CC) $(CFLAGS) Assets/Point.cpp

Color.o: Assets/Color.cpp
	$(CC) $(CFLAGS) Assets/Color.cpp

Ray.o: Assets/Ray.cpp
	$(CC) $(CFLAGS) Assets/Ray.cpp

Camera.o: Assets/Camera.cpp
	$(CC) $(CFLAGS) Assets/Camera.cpp

Light.o: Assets/Light.cpp
	$(CC) $(CFLAGS) Assets/Light.cpp

Material.o: Assets/Material.cpp
	$(CC) $(CFLAGS) Assets/Material.cpp

Sphere.o: Assets/Sphere.cpp
	$(CC) $(CFLAGS) Assets/Sphere.cpp

Plane.o: Assets/Plane.cpp
	$(CC) $(CFLAGS) Assets/Plane.cpp	

Cylinder.o: Assets/Cylinder.cpp
	$(CC) $(CFLAGS) Assets/Cylinder.cpp

Scene.o: Assets/Scene.cpp
	$(CC) $(CFLAGS) Assets/Scene.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp



clean:
	rm -rf *o main
