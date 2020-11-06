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
#include <vector>
#include "Defs.h"
#include "Utilities.h"
#include "FrameBuffer.h"
#include "ColorAndMaterials.h"
#include "Rasterization.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

// should work, unable to test
void closed5x5Square(int x, int y, color C) {
	for (int i = -1; i <= 2; i++) {
		drawLine(frameBuffer, x - 2, y, x + 2, y, C);
	}
}
// should work, unable to test
void closed5x5Square(const dvec2 &centerPt, color C) {
	for (int i = -1; i <= 2; i++) {
		drawLine(frameBuffer, centerPt.x - 2, centerPt.y, centerPt.x + 2, centerPt.y, C);
	}
}

// unsure of how to draw open square since I cannot test it due to build issues.
void open5x5Square(const dvec2 &centerPt, color C) {
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y, centerPt.x + 2, centerPt.y, C);
}

void pieChart(const dvec2 &centerPt, double radius, double percentage, const color &C1, const color &C2) {

}

void render() {
	const dvec2 x(100, 100);

	frameBuffer.clearColorAndDepthBuffers();
	closed5x5Square(50, 50, red);
	closed5x5Square(x, blue);
	open5x5Square(x, green);

	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, green);

	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ESCAPE:	glutLeaveMainLoop();
					break;
	}
}

int main2(int argc, char* argv[]) {
	std::cout << approximatelyEqual(1.0, 1.000001) << std::endl;
	return 0;
}*/


//int main(int argc, char *argv[]) {
//
//    graphicsInit(argc, argv, __FILE__);
//        
//	
//
//	glutDisplayFunc(render);
//	glutReshapeFunc(resize);
//	glutKeyboardFunc(keyboard);
//	glutMouseFunc(mouseUtility);
//
//	frameBuffer.setClearColor(white);
//
//	glutMainLoop();
//
//	return 0;
//}
