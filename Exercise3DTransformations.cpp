/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <ctime> 
#include <iostream>
#include <vector>
#include "EShape.h"
#include "Light.h"
#include "VertexOps.h"

PositionalLightPtr theLight = new PositionalLight(dvec3(2, 1, 3), pureWhiteLight);
vector<LightSourcePtr> lights = { theLight };

const double WIDTH = 10.0;
const int DIV = 20;

dvec3 position(0, 1, 5);
double angle = 0;
bool isMoving = true;
const double SPEED = 0.1;

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

EShapeData plane = EShape::createECheckerBoard(copper, polishedCopper, 5, 5, 10);
EShapeData cone1 = EShape::createECone(gold, 2.0, 1.0, 8);
EShapeData cone2 = EShape::createECone(brass, 0.5, 0.5, 8);
EShapeData disk = EShape::createEDisk(greenPlastic, 0.5, 8);
EShapeData cyl1 = EShape::createECylinder(silver, 0.5, 1, 8);
EShapeData cyl2 = EShape::createECylinder(silver, 0.5, 1, 8);
EShapeData tri = EShape::createETriangle(cyanPlastic,
	dvec4(0, 0, 0, 1), dvec4(1, 0, 0, 1), dvec4(1, 1, 0, 1));

void renderObjects() {
	VertexOps::render(frameBuffer, plane, lights, dmat4());
	VertexOps::render(frameBuffer, cone1, lights, T(-1, 2, 0) * S(0.25) * Rx(angle));
	VertexOps::render(frameBuffer, cone2, lights, Ry(angle) * T(2, 1, 0) * Rx(angle));
	VertexOps::render(frameBuffer, disk, lights, T(0, 1, 0) * Ry(angle) * S(0.5));
	VertexOps::render(frameBuffer, cyl1, lights, T(2, 1, 0));
	VertexOps::render(frameBuffer, cyl2, lights, T(-2, 1, 0) * Rx(PI_2));
	VertexOps::render(frameBuffer, tri, lights, T(0, 2, 0) * Rx(angle));
}

static void render() {
	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	VertexOps::viewingTrans = glm::lookAt(position, ORIGIN3D, Y_AXIS);
	double AR = (double)width / height;
	VertexOps::projectionTrans = glm::perspective(PI_3, AR, 0.5, 80.0);
	VertexOps::setViewport(0, width - 1, 0, height - 1);
	renderObjects();
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	double AR = (double)width / height;

	VertexOps::setViewport(0, width - 1, 0, height - 1);
	VertexOps::projectionTrans = glm::perspective(PI_3, AR, 0.5, 80.0);

	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	const double INC = 0.5;
	switch (key) {
	case 'X':
	case 'x': theLight->pos.x += (isupper(key) ? INC : -INC);
		cout << theLight->pos << endl;
		break;
	case 'Y':
	case 'y': theLight->pos.y += (isupper(key) ? INC : -INC);
		cout << theLight->pos << endl;
		break;
	case 'Z':
	case 'z': theLight->pos.z += (isupper(key) ? INC : -INC);
		cout << theLight->pos << endl;
		break;
	case 'P':
	case 'p':	isMoving = !isMoving;
		break;
	case 'C':
	case 'c':	break;
	case ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		cout << (int)key << "unmapped key pressed." << endl;
	}

	glutPostRedisplay();
}

static void timer(int id) {
	if (isMoving) {
		angle += glm::radians(5.0);
	}
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	VertexOps::renderBackFaces = true;
	graphicsInit(argc, argv, __FILE__);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouseUtility);
	frameBuffer.setClearColor(lightGray);

	glutMainLoop();

	return 0;
}
