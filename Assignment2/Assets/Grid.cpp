#include "Grid.h"

void Grid::computeBoundingBox(std::vector<Object*> objects) {

	float epsilon = 0.00001;
	BoundingBox bb;

	Point p0 = Point(kMin,kMin,kMin);
	Point p1 = Point(kMax,kMax,kMax);

	for(int j = 0; j < objects.size(); j++){
		bb = objects[j]->getBoundingBox();

		if(bb.getMin().x() < p0.x()){
			p0.setX(bb.getMin().x());
		}
		if(bb.getMin().y() < p0.y()){
			p0.setY(bb.getMin().y());
		}
		if(bb.getMin().z() < p0.z()){
			p0.setZ(bb.getMin().z());
		}

		if(bb.getMax().x() > p1.x()){
			p1.setX(bb.getMax().x());
		}
		if(bb.getMax().y() > p1.y()){
			p1.setY(bb.getMax().y());
		}
		if(bb.getMax().z() > p1.z()){
			p1.setZ(bb.getMax().z());
		}
	}
	p0.setLessX(epsilon); p0.setLessY(epsilon); p0.setLessZ(epsilon);
	p1.setPlusX(epsilon); p1.setPlusY(epsilon); p1.setPlusZ(epsilon);


	box = BoundingBox(p0, p1);
	
}

void Grid::initializeGridCells(std::vector<Object*> objects) {
	float wx = box.getMax().x() - box.getMin().x();
	float wy = box.getMax().y() - box.getMin().y();
	float wz = box.getMax().z() - box.getMin().z();

	float s = pow((wx * wy * wz) / objects.size(), 1/3);
cout << "s " << s << endl;
	nx = trunc(m * wx / s) + 1;
	ny = trunc(m * wy / s) + 1;
	nz = trunc(m * wz / s) + 1;
	cout << "nx " << wx << endl;
	cout << "ny " << wy << endl;
	cout << "nz " << wz << endl;

	int number_cells = nx * ny * nz;
	cout << "Cells " << number_cells << endl;


	vector<Object*> empty;
	for (int i = 0; i < number_cells; i++)
		cells.push_back(empty);

	int xmin, xmax, ymin, ymax, zmin, zmax;

	for(auto &obj : objects){
		BoundingBox box1 = obj->getBoundingBox();

		xmin = clamp((box1.getMin().x() - box.getMin().x()) * nx / (box.getMax().x() - box.getMin().x()),0, nx - 1);
		ymin = clamp((box1.getMin().y() - box.getMin().y()) * ny / (box.getMax().y() - box.getMin().y()),0, ny - 1);
		zmin = clamp((box1.getMin().z() - box.getMin().z()) * nz / (box.getMax().z() - box.getMin().z()),0, nz - 1);

		xmax = clamp((box1.getMax().x() - box.getMin().x()) * nx / (box.getMax().x() - box.getMin().x()),0, nx - 1);
		ymax = clamp((box1.getMax().y() - box.getMin().y()) * ny / (box.getMax().y() - box.getMin().y()),0, ny - 1);
		zmax = clamp((box1.getMax().z() - box.getMin().z()) * nz / (box.getMax().z() - box.getMin().z()),0, nz - 1);
		
		for(int z = zmin; z <= zmax; z++){
			for(int y = ymin; y <= ymax; y++){
				for(int x = xmin; x <= xmax; x++){
					int idx = x + nx * y + nx * ny * z;
					cout << "Fifth " << idx << endl;
					cells[idx].push_back(obj);
					cout << "Six" << endl;

				}
			}
		}

	}

}

Object* Grid::traverse(Ray ray) {

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

	float a = 1.0 / dx;
	if(a >= 0){
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else{
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	float b = 1.0 / dy;
	if(b >= 0){
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else{
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	float c = 1.0 / dz;
	if(c >= 0){
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else{
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}
	

	float t0, t1;


	//find largest entering t value
	if(tx_min > ty_min){
		t0 = tx_min;
	}
	else{
		t0 = ty_min;
	}
	if(tz_min > t0){
		t0 = tz_min;
	}

	//find smallest exiting t value
	if(tx_max < ty_max){
		t1 = tx_max;
	}
	else{
		t1 = ty_max;
	}
	if(tz_max < t1){
		t1 = tz_max;
	}

	//Se descomentar da background color
	/*if(t0 > t1){
		//return false;
		return nullptr;
	}*/

	int ix, iy, iz;

	//starting cell
	if(box.inside(ray.getOrigin())){
		
		ix = clamp((ox - x0) * nx / (x1 - x0),0,nx-1);
		iy = clamp((oy - y0) * ny / (y1 - y0),0,ny-1);
		iz = clamp((oz - z0) * nz / (z1 - z0),0,nz-1);
		
	}
	else{
		Point p = ray.getOrigin() + ray.getDirection().operator*(t0);
		ix = clamp((p.x() - x0) * nx / (x1 - x0),0,nx-1);
		iy = clamp((p.y() - y0) * ny / (y1 - y0),0,ny-1);
		iz = clamp((p.z() - z0) * nz / (z1 - z0),0,nz-1);
	}

	//stepping through the grid

	float dtx = (tx_max - tx_min) / nx;
	float dty = (ty_max - ty_min) / ny;
	float dtz = (tz_max - tz_min) / nz;

	float tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;

	//cout << "First" << endl;
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

	std::vector<Object*> object_ptr;

	while(true){
		object_ptr = cells[ix + nx * iy + nx * ny * iz];
		//cout << "Second" << endl;

		if(object_ptr.size() != 0 ){
			for(int k = 0; k < object_ptr.size(); k++){
				if(object_ptr[k]->checkRayCollision(ray) < kMax){
					//return true;
					//cout << "ola" << object_ptr[k]->checkRayCollision(ray) << endl;
					return object_ptr[k];
				}

			}
		}
		
		if(tx_next < ty_next && tx_next < tz_next){
			
			

			tx_next += dtx;
			ix += ix_step;

			if(ix == ix_stop){
				//return false;
				return nullptr;
			}

		}
		else{
			if(ty_next < tz_next){
				
				
				ty_next += dty;
				iy += iy_step;

				if(iy == iy_stop){
					//return false;
					return nullptr;
				}
			}
			else{

				tz_next += dtz;
				iz += iz_step;

				if(iz == iz_stop){
					//return false;
					return nullptr;
				}

			}

		}
	}

}