/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/


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

Image im1("usflag.ppm");

int currLight = 0;
double angle = 0.5;
double z = 0.0;
double inc = 0.5;
bool isAnimated = false;
int numReflections = 0;
int antiAliasing = 1;
bool twoViewOn = false;

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

	if (twoViewOn || !twoViewOn) {
		pCamera.calculateViewingParameters(frameBuffer.getWindowWidth(), frameBuffer.getWindowHeight());
		rayTrace.raytraceScene(frameBuffer, numReflections, scene);
	}

	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	double totalTimeSec = ((double)frameEndTime - frameStartTime) / 1000.0;
	cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	pCamera.calculateViewingParameters(width, height);
	glutPostRedisplay();
} 

IPlane* plane1 = new IPlane(dvec3(0.0, -2.0, 0.0), dvec3(0.0, 1.0, 0.0));
IPlane* plane2 = new IPlane(dvec3(0.0, -1.0, 0.0), dvec3(0.0, 1.0, 0.0));
ISphere* sphere1 = new ISphere(dvec3(0.0, 0.0, 0.0), 2.0);
ISphere* sphere2 = new ISphere(dvec3(-2.0, 0.0, -8.0), 2.0);
IEllipsoid* ellipsoid = new IEllipsoid(dvec3(4.0, 0.0, 3.0), dvec3(2.0, 1.0, 2.0));
IDisk* disk = new IDisk(dvec3(15.0, 0.0, 0.0), dvec3(0.0, 0.0, 1.0), 5.0);
ICylinderZ* cylinderZ = new ICylinderZ(dvec3(20.0, 5.0, -13.0), 5.0, 8.0);

void buildScene() {
	scene.addOpaqueObject(new VisibleIShape(plane1, tin));
	//scene.addOpaqueObject(new VisibleIShape(plane2, green));
	scene.addOpaqueObject(new VisibleIShape(sphere1, silver));
	scene.addOpaqueObject(new VisibleIShape(sphere2, bronze));
	scene.addOpaqueObject(new VisibleIShape(ellipsoid, redPlastic));
	//scene.addOpaqueObject(new VisibleIShape(disk, polishedGold));
	// scene.addOpaqueObject(new VisibleIShape(cylinderZ, yellowRubber));

	VisibleIShape* p;
	VisibleIShape* p2;
	scene.addOpaqueObject(p = new VisibleIShape(cylinderZ, chrome));
	scene.addOpaqueObject(p2 = new VisibleIShape(disk, polishedGold));
	//p->setTexture(&im1);
	p2->setTexture(&im1);
	// cylinderZ->setTexture(&im1);

	//scene.addTransparentObject(new VisibleIShape(plane2, green), 0.5);
	//scene.addTransparentObject(new VisibleIShape(ellipsoid, red), 0.5);

	 scene.addLight(lights[0]);
	 // scene.addLight(lights[1]);
}

void incrementClamp(double &v, double delta, double lo, double hi) {
	v = glm::clamp(v + delta, lo, hi);
}

void incrementClamp(int &v, int delta, int lo, int hi) {
	v = glm::clamp(v + delta, lo, hi);
}

void timer(int id) {
	if (isAnimated) {
		z += inc;
		if (z <= -5.0) {
			inc = -inc;
		} else if (z >= 5.0) {
			inc = -inc;
		}
	}
	sphere1->center = dvec3(0, 0, z);
	if (isAnimated) {
		glutTimerFunc(TIME_INTERVAL, timer, 0);
	}
	cout << isAnimated << endl;
	glutPostRedisplay();
}

void changeLightPos() {
	if (posLight->isTiedToWorld) {	
		posLight->pos = dvec3(10, 10, 10);
	}
	if (!posLight->isTiedToWorld) {
		lights[0]->pos = pCamera.cameraFrame.origin;
	}
}

void keyboard(unsigned char key, int x, int y) {
	int W, H;
	const double INC = 0.5;
	switch (key) {
	case 'A':
	case 'a':	currLight = 0;
				cout << *lights[0] << endl;
				break;
	case 'B':	
	case 'b':	currLight = 1;
				cout << *lights[1] << endl;
				break;
	case 'O':
	case 'o':	lights[currLight]->isOn = !lights[currLight]->isOn;
				cout << (lights[currLight]->isOn ? "ON" : "OFF") << endl;
				break;
	case 'V':
	case 'v':	lights[currLight]->isTiedToWorld = !lights[currLight]->isTiedToWorld;
				changeLightPos();
				cout << (lights[currLight]->isTiedToWorld ? "World" : "Camera") << endl;
				break;
	case 'Q':
	case 'q':	lights[currLight]->attenuationIsTurnedOn = !lights[currLight]->attenuationIsTurnedOn;
				cout << (lights[currLight]->attenuationIsTurnedOn ? "Atten ON" : "Atten OFF") << endl;
				break;
	case 'W':
	case 'w':	incrementClamp(lights[currLight]->atParams.constant, isupper(key) ? 0.1 : -0.1, 0.0, 10.0);
				cout << lights[currLight]->atParams << endl;
				break;
	case 'E':
	case 'e':	incrementClamp(lights[currLight]->atParams.linear, isupper(key) ? 0.1 : -0.1, 0.0, 10.0);
				cout << lights[currLight]->atParams << endl;
				break;
	case 'R':
	case 'r':	incrementClamp(lights[currLight]->atParams.quadratic, isupper(key) ? 0.1 : -0.1, 0.0, 10.0);
				cout << lights[currLight]->atParams << endl;
				break;
	case 'X':
	case 'x': lights[currLight]->pos.x += (isupper(key) ? INC : -INC);
				cout << lights[currLight]->pos << endl;
				break;
	case 'Y':
	case 'y': lights[currLight]->pos.y += (isupper(key) ? INC : -INC);
				cout << lights[currLight]->pos << endl;
				break;
	case 'Z':
	case 'z': lights[currLight]->pos.z += (isupper(key) ? INC : -INC);
				cout << lights[currLight]->pos << endl;
				break;
	//case 'J':// J, K, and L commands always apply to the spotlight
	//case 'j':spotLight->spotDir.x += (isupper(key) ? INC : -INC);
	//			cout << spotLight->spotDir << endl;
	//			break;
	//case 'K':
	//case 'k': spotLight->spotDir.y += (isupper(key) ? INC : -INC);
	//			cout << spotLight->spotDir << endl;
	//			break;
	//case 'L':
	//case 'l': spotLight->spotDir.z += (isupper(key) ? INC : -INC);
	//			cout << spotLight->spotDir << endl;
	//			break;
	//case 'F':	
	//case 'f':	incrementClamp(spotLight->fov, isupper(key) ? 0.2 : -0.2, 0.1, PI);
	//			cout << spotLight->fov << endl;
	//			break;
	//case 'P':
	//case 'p':	isAnimated = !isAnimated;
	//			if (isAnimated) {
	//				glutTimerFunc(TIME_INTERVAL, timer, 0);
	//			}
	//			break;
	case 'C':
	case 'c':	
				break;
	case 'U':
	case 'u':	incrementClamp(pCamera.fov, isupper(key) ? 0.2 : -0.2, glm::radians(10.0), glm::radians(160.0));
				W = frameBuffer.getWindowWidth();
				H = frameBuffer.getWindowWidth();
				pCamera.calculateViewingParameters(W, H);
				cout << pCamera.fov << endl;
				break;
	case 'M':
	case 'm':	break;
	case '+':	antiAliasing = 3; 
				cout << "Anti aliasing: " << antiAliasing << endl;
				break;
	case '-':	antiAliasing = 1;
				cout << "Anti aliasing: " << antiAliasing << endl;
				break;

	case '?':	twoViewOn = !twoViewOn;
				break;
	case '0':	
	case '1':	
	case '2':	numReflections = key - '0';
				cout << "Num reflections: " << numReflections << endl;
				break;
	case 'd':	isAnimated = !isAnimated;
				break;
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
	glutTimerFunc(TIME_INTERVAL, timer, 0);
	buildScene();

	glutMainLoop();
	return 0;
}