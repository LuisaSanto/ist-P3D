CC=g++

CFLAGS=-c

all: Point.o Camera.o Light.o Material.o Sphere.o Cylinder.o Scene.o main.o
	$(CC) Point.o Camera.o Light.o Material.o Sphere.o Cylinder.o Scene.o main.o -o main


Point.o: Assets/Point.cpp
	$(CC) $(CFLAGS) Assets/Point.cpp

Camera.o: Assets/Camera.cpp
	$(CC) $(CFLAGS) Assets/Camera.cpp

Light.o: Assets/Light.cpp
	$(CC) $(CFLAGS) Assets/Light.cpp

Material.o: Assets/Material.cpp
	$(CC) $(CFLAGS) Assets/Material.cpp

Sphere.o: Assets/Sphere.cpp
	$(CC) $(CFLAGS) Assets/Sphere.cpp

Cylinder.o: Assets/Cylinder.cpp
	$(CC) $(CFLAGS) Assets/Cylinder.cpp

Scene.o: Assets/Scene.cpp
	$(CC) $(CFLAGS) Assets/Scene.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp



clean:
	rm -rf *o main
