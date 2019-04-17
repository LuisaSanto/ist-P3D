#include "Grid.h"

void Grid::computeBoundingBox(std::vector<Object*> objects) {

	float epsilon = 0.00001;

	Point p0 = Point(kMin,kMin,kMin);
	Point p1 = Point(kMax,kMax,kMax);

	for(int j = 0; j < number_objects; j++){
		BoundingBox box = objects[j]->getBoundingBox();

		if(box.getMin().x() < p0.x()){
			p0.setX(box.getMin().x());
		}
		if(box.getMin().y() < p0.y()){
			p0.setY(box.getMin().y());
		}
		if(box.getMin().z() < p0.z()){
			p0.setZ(box.getMin().z());
		}

		if(box.getMax().x() < p1.x()){
			p1.setX(box.getMax().x());
		}
		if(box.getMax().y() < p1.y()){
			p1.setY(box.getMax().y());
		}
		if(box.getMax().z() < p1.z()){
			p1.setZ(box.getMax().z());
		}
	}
	p0.setPlusX(epsilon); p0.setPlusY(epsilon); p0.setPlusZ(epsilon);
	p1.setPlusX(epsilon); p1.setPlusY(epsilon); p1.setPlusZ(epsilon);

	box = BoundingBox(p0, p1);
	
}

void Grid::initializeGridCells(std::vector<Object*> objects) {
	float wx = box.getMax().x() - box.getMin().x();
	float wy = box.getMax().y() - box.getMin().y();
	float wz = box.getMax().z() - box.getMin().z();

	float s = pow((wx * wy * wz) / number_objects, 1/3);

	nx = trunc(m * wx / s) + 1;
	ny = trunc(m * wy / s) + 1;
	nz = trunc(m * wz / s) + 1;

	int number_cells = nx * ny * nz;

	int xmin, xmax, ymin, ymax, zmin, zmax;

	for(int j = 0; j < number_objects; j++){
		BoundingBox box1 = objects[j]->getBoundingBox();

		xmin = clamp((box1.getMin().x() - box.getMin().x()) * nx / (box1.getMax().x() - box.getMin().x()),0, nx - 1);
		ymin = clamp((box1.getMin().y() - box.getMin().y()) * ny / (box1.getMax().y() - box.getMin().y()),0, ny - 1);
		zmin = clamp((box1.getMin().z() - box.getMin().z()) * nz / (box1.getMax().z() - box.getMin().z()),0, nz - 1);

		xmax = clamp((box1.getMax().x() - box.getMin().x()) * nx / (box1.getMax().x() - box.getMin().x()),0, nx - 1);
		ymax = clamp((box1.getMax().y() - box.getMin().y()) * ny / (box1.getMax().y() - box.getMin().y()),0, ny - 1);
		zmax = clamp((box1.getMax().z() - box.getMin().z()) * nz / (box1.getMax().z() - box.getMin().z()),0, nz - 1);

		for(int z = zmin; z <= zmax; z++){
			for(int y = ymin; y <= ymax; y++){
				for(int x = xmin; x <= xmax; x++){
					int idx = x + nx * y + nx * ny * z;
					cells[idx].push_back(objects[j]);

				}
			}
		}

	}
}