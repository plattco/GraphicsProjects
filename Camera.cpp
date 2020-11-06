/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "Camera.h"

/**
 * @fn	RaytracingCamera::RaytracingCamera(const dvec3 &viewingPos, const dvec3 &lookAtPt, const dvec3 &up)
 * @brief	Constructs a raytracing camera.
 * @param	viewingPos	Location of camera.
 * @param	lookAtPt  	A focus point in front of the camera..
 * @param	up		  	Up vector.
 */

RaytracingCamera::RaytracingCamera(const dvec3 &viewingPos, const dvec3 &lookAtPt, const dvec3 &up) {
	changeConfiguration(viewingPos, lookAtPt, up);
}

/**
 * @fn	void RaytracingCamera::changeConfiguration(const dvec3 &viewingPos, const dvec3 &lookAtPt, const dvec3 &up)
 * @brief	Change configuration parameters of this camera.
 * @param	viewingPos	The new viewing position.
 * @param	lookAtPt  	A new focus point point.
 * @param	up		  	Up vector.
 */

void RaytracingCamera::changeConfiguration(const dvec3 &viewingPos, const dvec3 &lookAtPt, const dvec3 &up) {
	/* CSE 386 - todo  */
	dvec3 viewingDirection = lookAtPt - viewingPos;

	dvec3 w = glm::normalize(-viewingDirection);
	dvec3 u = glm::normalize(cross(up, w));
	dvec3 v = glm::normalize(cross(w, u));
	cameraFrame.setFrame(viewingPos, u, v, w);
}

/**
 * @fn	PerspectiveCamera::PerspectiveCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up, double FOVRads)
 * @brief	Constructs a perspective camera.
 * @param	pos			The position of the camera.
 * @param	lookAtPt	A focus point in front of the camera.
 * @param	up			Up vector.
 * @param	FOVRads 	The field of view in radians.
 */

PerspectiveCamera::PerspectiveCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up, double FOVRads)
	: RaytracingCamera(pos, lookAtPt, up) {
	distToPlane = 0;
	fov = FOVRads;
}

/**
 * @fn	OrthographicCamera::OrthographicCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up, double ppwu)
 * @brief	Constructs an orthographic camera.
 * @param	pos			Position of camera.
 * @param	lookAtPt	A focus point in front of the camera.
 * @param	up			Up vector.
 * @param	ppwu		Pixels per world unit.
 */

OrthographicCamera::OrthographicCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up, double ppwu)
	: RaytracingCamera(pos, lookAtPt, up) {
	pixelsPerWorldUnit = ppwu;
}

/**
 * @fn	dvec2 RaytracingCamera::getProjectionPlaneCoordinates(double x, double y) const
 * @brief	Gets projection plane coordinates at (x, y).
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	Projection plane coordinates.
 */

dvec2 RaytracingCamera::getProjectionPlaneCoordinates(double x, double y) const {
	/* CSE 386 - todo  */
	double width = right - left;
	double height = top - bottom;
	dvec2 s;
	s.x = ((x + 0.5) * ((width) / nx) + left);
	s.y = ((y + 0.5) * ((height) / ny) + bottom);
	return s;
}

/**
 * @fn	void PerspectiveCamera::calculateViewingParameters(int W, int H)
 * @brief	Calculates the viewing parameters associated with this camera.
 * @param	W	The width of window.
 * @param	H	The height of window.
 */

void PerspectiveCamera::calculateViewingParameters(int W, int H) {
	/* CSE 386 - todo  */
	/* fill in nx, ny, distToPlane, top, bottom, left, and right */
	nx = (double)W;
	ny = (double)H;

	double fov_2 = fov / 2.0;
	distToPlane = 1.0 / std::tan(fov_2);

	top = 1.0;
	bottom = -top;

	right = top * ((double)W / H);
	left = -right;

	
}

/**
 * @fn	void OrthographicCamera::calculateViewingParameters(int W, int H)
 * @brief	Calculates the viewing parameters associated with this camera.
 * @param	W	The width of window.
 * @param	H	The height of window.
 */

void OrthographicCamera::calculateViewingParameters(int W, int H) {
	/* CSE 386 - todo  */
	/* fill in nx, ny, distToPlane, top, bottom, left, and right */

	/*nx = (double)W;
	ny = (double)H;
	top = ny / 2;
	right = top * (nx / ny);
	bottom = -top;
	left = -right;*/

	nx = (double)W;
	ny = (double)H;

	top = H / 2.0;
	bottom = -top;

	right = top * (double)W / H;
	left = -right;


	//distToPlane = (1 / tan(fov / 2)); // there does not seem to be a distToPlane variable or method for ortho.
}

/**
 * @fn	Ray OrthographicCamera::getRay(double x, double y) const
 * @brief	Determines camera ray going through projection plane at (x, y), in direction -w.
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	The ray through the projection plane at (x, y), in direction -w.
 */

Ray OrthographicCamera::getRay(double x, double y) const {
	/* CSE 386 - todo  */
	dvec2 uv = getProjectionPlaneCoordinates(x, y);
	
	dvec3 rayOrigin = cameraFrame.origin + uv.x * cameraFrame.u +	uv.y * cameraFrame.v; // Page 76
	return Ray(rayOrigin, -cameraFrame.w);
}

/**
 * @fn	Ray PerspectiveCamera::getRay(double x, double y) const
 * @brief	Determines ray eminating from camera through the projection plane at (x, y).
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	The ray eminating from camera through the projection plane at (x, y).
 */

Ray PerspectiveCamera::getRay(double x, double y) const {
	dvec2 uv = getProjectionPlaneCoordinates(x, y);
	dvec3 rayDirection = glm::normalize(-distToPlane * cameraFrame.w +
											uv.x * cameraFrame.u + 
											uv.y * cameraFrame.v); // Page 76
	return Ray(cameraFrame.origin, rayDirection);
}

/**
 * @fn	void PerspectiveCamera::setFOV(double FOV, int W, int H)
 * @brief	Sets a camera's field of view.
 * @param	FOV	The field of view.
 * @param	W  	Width of window.
 * @param	H  	Height of window.
 */

void PerspectiveCamera::setFOV(double FOV, int W, int H) {
	fov = FOV;
	calculateViewingParameters(W, H);
}

/**
* @fn	ostream &operator << (ostream &os, const RaytracingCamera &camera)
* @brief	Output stream for cameras.
* @param	os		Output stream.
* @param	camera  The camera.
*/

ostream &operator << (ostream &os, const RaytracingCamera &camera) {
	os << "Camera info:" << endl;
	os << "Frame" << endl;
	os << camera.cameraFrame << endl;
	return os;
}
