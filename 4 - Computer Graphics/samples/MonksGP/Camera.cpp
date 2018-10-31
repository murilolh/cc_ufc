#include "Camera.h"

void Camera :: setPosicao(float ox, float oy, float oz){
	this->ox = ox;
	this->oy = oy;
	this->oz = oz;
}

void Camera :: setNormal(float ax, float ay, float az){
	this->nx = nx;
	this->ny = ny;
	this->nz = nz;
}

void Camera :: setDirecao(float nx, float ny, float nz){
	this->ax = ax;
	this->ay = ay;
	this->az = az;
}

Camera :: Camera(void){
	ox = 0.0;
	oy = -50.0;
	oz = 50.0;
	ax = 0.0;
	ay = 0.0;
	az = 0.0;
	nx = 0.0;
	ny = 0.0;
	nz = 1.0;	
}

Camera :: Camera(float ox, float oy, float oz, float ax, float ay, float az, float nx, float ny, float nz){
	
	this->ox = ox;
	this->oy = oy;
	this->oz = oz;
	this->ax = ax;
	this->ay = ay;
	this->az = az;
	this->nx = nx;
	this->ny = ny;
	this->nz = nz;
}
