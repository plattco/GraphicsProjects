/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE: 
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#pragma once
#include <iostream>
#include "IShape.h"

/**
 * @struct	RaytracingCamera
 * @brief	Base class for cameras in raytracing applications.
 */

struct RaytracingCamera {
	Frame cameraFrame;					//!< The camera's frame
	double left, right, bottom, top;	//!< The camera's vertical field of view
	double nx, ny;						//!< Window size
	RaytracingCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up);
	void changeConfiguration(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up);
	dvec2 getProjectionPlaneCoordinates(double x, double y) const;
	virtual void calculateViewingParameters(int width, int height) = 0;
	virtual Ray getRay(double x, double y) const = 0;
	friend ostream &operator << (ostream &os, const RaytracingCamera &camera);
};

/**
 * @struct	PerspectiveCamera
 * @brief	Encapsulates a perspective camera for raytracing applications.
 */

struct PerspectiveCamera : public RaytracingCamera {
	double fov;						//!< The camera's field of view
	double distToPlane;				//!< Distance to image plane
	PerspectiveCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up, double FOVRads);
	virtual void calculateViewingParameters(int width, int height);
	virtual Ray getRay(double x, double y) const;
	void setFOV(double FOV, int W, int H);
};

/**
 * @struct	OrthographicCamera
 * @brief	Encapsulates a orthographic camera for raytracing applications.
 */

struct OrthographicCamera : public RaytracingCamera {
	double pixelsPerWorldUnit;		//!< Controls the size of the image plane.
	OrthographicCamera(const dvec3 &pos, const dvec3 &lookAtPt, const dvec3 &up, double ppwu);
	virtual void calculateViewingParameters(int width, int height);
	virtual Ray getRay(double x, double y) const;
};