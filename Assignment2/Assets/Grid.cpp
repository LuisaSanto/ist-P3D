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

float Grid::traverse(Ray ray) {

	float ox = ray.getOrigin().x();
	float oy = ray.getOrigin().y();
	float oz = ray.getOrigin().z();

	float dx = ray.getDirection().x();
	float dy = ray.getDirection().y();
	float dz = ray.getDirection().z();

	float x0 = box.getMin().x();
	float y0 = box.getMin().y();
	float z0 = box.getMin().z();

	float x1 = box.getMax().x();
	float y1 = box.getMax().y();
	float z1 = box.getMax().z();

	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;

	int ix, iy, iz;
	float t0, t1;

	//starting cell
	if(box.inside(ray.getOrigin())){
		ix = clamp((ox - x0) * nx / (x1/x0),0,nx-1);
		iy = clamp((oy - y0) * ny / (y1/y0),0,ny-1);
		iz = clamp((oz - z0) * nz / (z1/z0),0,nz-1);
	}
	else{
		Point p = ray.getOrigin() + ray.getDirection().operator*(t0);
		ix = clamp((p.x() - x0) * nx / (x1/x0),0,nx-1);
		iy = clamp((p.y() - y0) * ny / (y1/y0),0,ny-1);
		iz = clamp((p.z() - z0) * nz / (z1/z0),0,nz-1);
	}

	//stepping through the grid

	float dtx = (tx_max - tx_min) / nx;
	float dty = (ty_max - ty_min) / ny;
	float dtz = (tz_max - tz_min) / nz;

	float tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;


	if(dx > 0){
		tx_next = tx_min + (ix + 1 ) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else{
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}
	if(dx == 0.0){
		tx_next = kMax;
		ix_step = -1;
		ix_stop = -1;
	}

	if(dy > 0){
		ty_next = ty_min + (iy + 1 ) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else{
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}
	if(dy == 0.0){
		ty_next = kMax;
		iy_step = -1;
		iy_stop = -1;
	}

	if(dz > 0){
		tz_next = tz_min + (iz + 1 ) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else{
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}
	if(dz == 0.0){
		tz_next = kMax;
		iz_step = -1;
		iz_stop = -1;
	}


}