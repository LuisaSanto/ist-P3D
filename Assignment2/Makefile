CC=g++ -g -std=c++11

CFLAGS=-c 
OPENGLFLAGS= -lglut -lGLU -lGL -lGLEW

all: Point.o Object.o Ray.o Camera.o Color.o Light.o Material.o Sphere.o Plane.o Polygon.o Cylinder.o BoundingBox.o Scene.o main.o
	$(CC) Point.o Object.o Ray.o Color.o Camera.o Light.o Material.o Sphere.o Plane.o Polygon.o Cylinder.o BoundingBox.o Scene.o main.o -o main $(OPENGLFLAGS)


Point.o: Assets/Point.cpp
	$(CC) $(CFLAGS) Assets/Point.cpp

Object.o: Assets/Object.cpp
	$(CC) $(CFLAGS) Assets/Object.cpp

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

Polygon.o: Assets/Polygon.cpp
	$(CC) $(CFLAGS) Assets/Polygon.cpp	

Cylinder.o: Assets/Cylinder.cpp
	$(CC) $(CFLAGS) Assets/Cylinder.cpp

BoundingBox.o: Assets/BoundingBox.cpp
	$(CC) $(CFLAGS) Assets/BoundingBox.cpp

Scene.o: Assets/Scene.cpp
	$(CC) $(CFLAGS) Assets/Scene.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp



clean:
	rm -rf *o main
