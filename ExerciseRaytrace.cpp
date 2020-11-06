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

int currLight = 0;
double z = 0.0;
double inc = 0.2;

vector<PositionalLightPtr> lights = {
						new PositionalLight(dvec3(10, 10, 10), pureWhiteLight),
						new SpotLight(dvec3(2, 5, -2), dvec3(0,-1,0), glm::radians(45.0), pureWhiteLight)
};

PositionalLightPtr posLight = lights[0];
SpotLightPtr spotLight = (SpotLightPtr)lights[1];

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(lightGray);
PerspectiveCamera pCamera(dvec3(0, 5, 10), dvec3(0, 5, 0), Y_AXIS, PI_2);
IScene scene(&pCamera);

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);

	double N = 10.0;
	pCamera.changeConfiguration(dvec3(0, 5, 10), dvec3(0, 5, 0), Y_AXIS);
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

void buildScene() {
	IShape *plane = new IPlane(dvec3(0.0, -2.0, 0.0), dvec3(0.0, 1.0, 0.0));
	ISphere *sphere1 = new ISphere(dvec3(0.0, 0.0, 0.0), 2.0);
	ISphere *sphere2 = new ISphere(dvec3(-2.0, 0.0, -8.0), 2.0);
	IEllipsoid *ellipsoid = new IEllipsoid(dvec3(4.0, 0.0, 3.0), dvec3(2.0, 1.0, 2.0));
	IDisk *disk = new IDisk(dvec3(15.0, 0.0, 0.0), dvec3(0.0, 0.0, 1.0), 5.0);

	scene.addOpaqueObject(new VisibleIShape(plane, tin));
	scene.addOpaqueObject(new VisibleIShape(sphere1, silver));
	scene.addOpaqueObject(new VisibleIShape(sphere2, bronze));
	scene.addOpaqueObject(new VisibleIShape(ellipsoid, redPlastic));
	scene.addOpaqueObject(new VisibleIShape(disk, cyanPlastic));

	scene.addLight(lights[0]);
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
	// hmm
}
*/
