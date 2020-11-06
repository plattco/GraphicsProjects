/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

/*
#include <ctime>
#include "Defs.h"
#include "IShape.h"
#include "FrameBuffer.h"
#include "RayTracer.h"
#include "IScene.h"
#include "Light.h"
#include "Image.h"
#include "Camera.h"
#include "Rasterization.h"

double z = 0.0;
double inc = 0.2;

PositionalLight posLight(dvec3(-10, 10, 10), pureWhiteLight);

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(lightGray);
PerspectiveCamera pCamera(dvec3(0, 10, 10), dvec3(0, 0, 0), Y_AXIS, PI_2);
IScene scene(&pCamera);

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);

	double N = 10.0;
	rayTrace.raytraceScene(frameBuffer, 0, scene);

	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;
	cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	pCamera.calculateViewingParameters(width, height);
	glutPostRedisplay();
	cout << pCamera.getProjectionPlaneCoordinates(0, 0) << endl;
}

IDisk *bronzeDisk = new IDisk(dvec3(-6, 0, -5), dvec3(0, 0, 1), 3);
IDisk *tinDisk = new IDisk(dvec3(-8, 0, -4), dvec3(0, 0, 1), 3);
ICylinderY *cylinder = new ICylinderY(dvec3(4.0, 0.0, -1.0), 5.0, 3.0);
ICylinderZ* cylinderZ = new ICylinderZ(dvec3(12.0, 0.0, -8.0), 5.0, 3.0);
IClosedCylinderY* closedCylinder = new IClosedCylinderY(dvec3(-5.0, 0.0, 0.0), 2.0, 5.0);
void buildScene() {
	scene.addOpaqueObject(new VisibleIShape(bronzeDisk, bronze));
	scene.addOpaqueObject(new VisibleIShape(tinDisk, tin));
	scene.addOpaqueObject(new VisibleIShape(cylinder, gold));
	scene.addOpaqueObject(new VisibleIShape(cylinderZ, pewter));
	scene.addOpaqueObject(new VisibleIShape(closedCylinder, polishedCopper));
	scene.addLight(&posLight);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		cout << (int)key << "unmapped key pressed." << endl;
	}

	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	graphicsInit(argc, argv, __FILE__);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseUtility);
	buildScene();

	rayTrace.defaultColor = gray;
	glutMainLoop();

	return 0;
}
*/

