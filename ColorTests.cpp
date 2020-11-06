#include <iostream>
#include "Defs.h"
#include "Light.h"
#include "Camera.h"

int main(int argc, char* argv[]) {
	dvec3 eyePos(3.0, 0.0, 1.0);

	dvec3 interceptPt(5.0, 2.0, -3.0);
	dvec3 pointToRight(4.0, 4.0, 0.0);
	dvec3 pointToLeft(0.0, 0.0, 0.0);

	color L1amb(0.3, 0.2, 0.1);
	color L1diff(1.0, 1.0, 1.0);
	color L1spec(0.5, 0.6, 0.7);
	dvec3 L1pos(6.0, 1.0, 0.0);

	color mat1amb(0.4, 0.5, 0.6);
	color mat1diff(0.9, 1.0, 0.9);
	color mat1spec(0.9, 0.8, 0.7);

	dvec3 V1 = pointToRight - interceptPt;
	dvec3 V2 = pointToLeft - interceptPt;
	dvec3 n = glm::normalize(glm::cross(V1, V2));
	dvec3 v = glm::normalize(eyePos - interceptPt);
	dvec3 l = glm::normalize(L1pos - interceptPt);
	dvec3 r = glm::normalize(2.0 * glm::dot(l, n) * n - l);

	cout << "n: " << n << endl;
	cout << "v: " << v << endl;
	cout << "l: " << l << endl;
	cout << "r: " << r << endl;
	cout << endl;

	cout << "Ambient: " << ambientColor(mat1amb, L1amb) << endl;
	cout << "Diffuse: " << diffuseColor(mat1diff, L1diff, l, n) << endl;
	cout << "Specular: " << specularColor(mat1spec, L1spec, 1.0, r, v) << endl;

	LightColor L1color(L1amb, L1diff, L1spec);
	PositionalLight L1(L1pos, L1color);
	Material mat1(mat1amb, mat1diff, mat1spec, 1.0);
	LightATParams atParams(1.0, 2.0, 0.0);
	bool useAttenuation = false;

	cout << "Total: " << totalColor(mat1, L1color, v, n, L1pos, interceptPt, useAttenuation, atParams) << endl;
	cout << endl;

	cout << "Attenuation factor: " << atParams.factor(glm::distance(L1pos, interceptPt)) << endl;

	cout << endl;

	PositionalLight light1(L1pos, L1color);

	bool interceptIsInShadow = false;
	PerspectiveCamera pCamera(eyePos, interceptPt, Y_AXIS, PI_2);

	cout << "Normal light: " << light1.illuminate(interceptPt, n, mat1, pCamera.cameraFrame, false) << endl;
	cout << "In shadow: " << light1.illuminate(interceptPt, n, mat1, pCamera.cameraFrame, true) << endl;
	light1.isOn = false;
	cout << "Off: " << light1.illuminate(interceptPt, n, mat1, pCamera.cameraFrame, true) << endl;

	return 0;
}
/*
n: [ 0.57735 -0.57735 0.57735 ]
v: [ -0.408248 -0.408248 0.816497 ]
l: [ 0.301511 -0.301511 0.904534 ]
r: [ 0.703526 -0.703526 0.100504 ]

Ambient: [ 0.12 0.1 0.06 ]
Diffuse: [ 0.783349 0.870388 0.783349 ]
Specular: [ 0.0369274 0.0393893 0.0402099 ]
Total: [ 0.940277 1 0.883559 ]

Attenuation factor: 0.131006

Normal light: [ 0.940277 1 0.883559 ]
In shadow: [ 0.12 0.1 0.06 ]
Off: [ 0 0 0 ]
*/