#include "Defs.h"
#include "Camera.h"

void checkOrthographicCamera(const dvec3& cameraPos, const dvec3& focusPt,
							int NX, int NY, const glm::ivec2& pixel1, const glm::ivec2& pixel2) {
	cout << "Orthographic camera and viewing rays checks:" << endl;
	cout << "-------------------------------" << endl;

	const int PIXELS_PER_WORLD_UNITS = 1;
	OrthographicCamera oCamera(cameraPos, focusPt, dvec3(0, 1, 0), PIXELS_PER_WORLD_UNITS); // Basically ignore last parameter

	oCamera.calculateViewingParameters(NX, NY);
	cout << "Frame: " << oCamera.cameraFrame << endl;
	//cout << "distance to plane: " << oCamera.distToPlane << endl;  // There is no distToPlane for orthographic cameras
	cout << "nx/ny: " << oCamera.nx << ' ' << oCamera.ny << endl;
	cout << "l/r/b/t: " << oCamera.left << ' ' << oCamera.right << ' ' << oCamera.bottom << ' ' << oCamera.top << endl;

	cout << "Proj plane coords for pixel #1 " << oCamera.getProjectionPlaneCoordinates(pixel1.x, pixel1.y) << endl;
	cout << "Proj plane coords for pixel #2: " << oCamera.getProjectionPlaneCoordinates(pixel2.x, pixel2.y) << endl;
	cout << "nx/ny: " << oCamera.nx << ' ' << oCamera.ny << endl;

	Ray viewingRay1 = oCamera.getRay(pixel1.x, pixel1.y);
	Ray viewingRay2 = oCamera.getRay(pixel2.x, pixel2.y);
	cout << "Viewing ray for pixel #1: " << viewingRay1.origin << ' ' << viewingRay1.dir << endl;
	cout << "Viewing ray for pixel #2: " << viewingRay2.origin << ' ' << viewingRay2.dir << endl;
}

void checkPerspectiveCamera(const dvec3& cameraPos, const dvec3& focusPt,
							double FOV, int NX, int NY, const glm::ivec2 &pixel1, const glm::ivec2 &pixel2) {
	cout << "Perspective camera and viewing rays checks:" << endl;
	cout << "-------------------------------" << endl;

	PerspectiveCamera pCamera(cameraPos, focusPt, dvec3(0, 1, 0), FOV);

	pCamera.calculateViewingParameters(NX, NY);
	cout << "Frame: " << pCamera.cameraFrame << endl;
	cout << "distance to plane: " << pCamera.distToPlane << endl;
	cout << "nx/ny: " << pCamera.nx << ' ' << pCamera.ny << endl;
	cout << "l/r/b/t: " << pCamera.left << ' ' << pCamera.right << ' ' << pCamera.bottom << ' ' << pCamera.top << endl;

	cout << "Proj plane coords for pixel #1 " << pCamera.getProjectionPlaneCoordinates(pixel1.x, pixel1.y) << endl;
	cout << "Proj plane coords for pixel #2: " << pCamera.getProjectionPlaneCoordinates(pixel2.x, pixel2.y) << endl;

	Ray viewingRay1 = pCamera.getRay(pixel1.x, pixel1.y);
	Ray viewingRay2 = pCamera.getRay(pixel2.x, pixel2.y);
	cout << "Viewing ray for pixel #1: " << viewingRay1.origin << ' ' << viewingRay1.dir << endl;
	cout << "Viewing ray for pixel #2: " << viewingRay2.origin << ' ' << viewingRay2.dir << endl;
}

/*int main(int argc, char* argv[]) {
	// These examples are worked out on the worksheets during class.
	// The expected output is shown below.

	checkOrthographicCamera(dvec3(0, 0, 0), dvec3(0, 0, -2), 200, 200, glm::ivec2(0, 0), glm::ivec2(100, 100));
	checkOrthographicCamera(dvec3(5, 5, 0), dvec3(4, 5, 0), 200, 400, glm::ivec2(0, 0), glm::ivec2(100, 200));

	checkPerspectiveCamera(dvec3(0, 0, 0), dvec3(0, 0, -2), PI_4, 200, 200, glm::ivec2(0, 0), glm::ivec2(100, 100));
	checkPerspectiveCamera(dvec3(5, 5, 0), dvec3(4, 5, 0), PI_4, 200, 400, glm::ivec2(0, 0), glm::ivec2(100, 200));

	return 0;
}

/* Output
* Orthographic camera and viewing rays checks:
-------------------------------
Frame: Pos: [ 0 0 0 ]
U: [ 1 -0 0 ]
V: [ 0 1 0 ]
W: [ -0 -0 1 ]

nx/ny: 200 200
l/r/b/t: -100 100 -100 100
Proj plane coords for pixel #1 [ -99.5 -99.5 ]
Proj plane coords for pixel #2: [ 0.5 0.5 ]
Viewing ray for pixel #1: [ -99.5 -99.5 0 ] [ 0 0 -1 ]
Viewing ray for pixel #2: [ 0.5 0.5 0 ] [ 0 0 -1 ]
Orthographic camera and viewing rays checks:
-------------------------------
Frame: Pos: [ 5 5 0 ]
U: [ 0 0 -1 ]
V: [ 0 1 0 ]
W: [ 1 -0 -0 ]

nx/ny: 200 400
l/r/b/t: -100 100 -200 200
Proj plane coords for pixel #1 [ -99.5 -199.5 ]
Proj plane coords for pixel #2: [ 0.5 0.5 ]
Viewing ray for pixel #1: [ 5 -194.5 99.5 ] [ -1 0 0 ]
Viewing ray for pixel #2: [ 5 5.5 -0.5 ] [ -1 0 0 ]
Perspective camera and viewing rays checks:
-------------------------------
Frame: Pos: [ 0 0 0 ]
U: [ 1 -0 0 ]
V: [ 0 1 0 ]
W: [ -0 -0 1 ]

distance to plane: 2.41421
nx/ny: 200 200
l/r/b/t: -1 1 -1 1
Proj plane coords for pixel #1 [ -0.995 -0.995 ]
Proj plane coords for pixel #2: [ 0.005 0.005 ]
Viewing ray for pixel #1: [ 0 0 0 ] [ -0.356074 -0.356074 -0.863958 ]
Viewing ray for pixel #2: [ 0 0 0 ] [ 0.00207106 0.00207106 -0.999996 ]
Perspective camera and viewing rays checks:
-------------------------------
Frame: Pos: [ 5 5 0 ]
U: [ 0 0 -1 ]
V: [ 0 1 0 ]
W: [ 1 -0 -0 ]

distance to plane: 2.41421
nx/ny: 200 400
l/r/b/t: -0.5 0.5 -1 1
Proj plane coords for pixel #1 [ -0.4975 -0.9975 ]
Proj plane coords for pixel #2: [ 0.0025 0.0025 ]
Viewing ray for pixel #1: [ 5 5 0 ] [ -0.907898 -0.375124 0.187092 ]
Viewing ray for pixel #2: [ 5 5 0 ] [ -0.999999 0.00103553 -0.00103553 ]

C:\Users\zmuda\OneDrive\Desktop\Courses\CSE386CodeBase\x64\Debug\CSE386Fall2020.exe (process 23368) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/