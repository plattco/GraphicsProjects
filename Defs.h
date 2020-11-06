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
#include <vector>
#include <cmath>
#include <memory>
#include <limits>

// Glut takes care of all the system-specific chores required for creating windows, 
// initializing OpenGL contexts, and handling input events
#include <GL/freeglut.h>

#define GLM_FORCE_CTOR_INIT
#define GLM_FORCE_SWIZZLE  // Enable GLM "swizzle" operators

// Basic GLM functionality
#include <glm/glm.hpp> 
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using std::cout;
using std::endl; 
using std::vector;
using std::ostream;
using std::string;

using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::dmat2;
using glm::dmat3;
using glm::dmat4;
using glm::dmat4x2;
using glm::dmat2x4;

const std::string username = "plattcr";
const double EPSILON = 1.0E-3;		//!< default value used for "SMALL" tolerances.

const int TIME_INTERVAL = 100;		//!< default time interval used timers.
const int WINDOW_WIDTH = 500;		//!< default window width.
const int WINDOW_HEIGHT = 250;		//!< default window height.
const unsigned char ESCAPE = 27;	//!< escape key.
const int SLICES = 8;				//!< default value used when slicing up a curved object.
const int STACKS = 8;				//!< default value used when slicing up a curved object - vertically

const double PI = 3.14159265358979323846264338327950288419716939937510582097494;	//!< pi
const double TWO_PI = 2 * PI;		//!< 2pi	(360 degrees)
const double PI_2 = PI / 2.0;		//!< pi/2	(90 degrees)
const double PI_3 = PI / 3.0;		//!< pi/3	(60 degrees)
const double PI_4 = PI / 4.0;		//!< pi/4	(45 degrees)
const double PI_6 = PI / 6.0;		//!< pi/6	(30 degrees)

const dvec3 ORIGIN3D(0.0, 0.0, 0.0);			//!< (0, 0, 0)
const dvec4 ORIGIN3DHOMO(0.0, 0.0, 0.0, 1.0);	//!< (0, 0, 0, 1)
const dvec2 ORIGIN2D(0.0, 0.0);					//!< (0, 0)
const dvec3 ORIGIN2DHOMO(0.0, 0.0, 1.0);		//!< (0, 0, 1)

const dvec3 ZEROVEC(0.0, 0.0, 0.0);			//!< <0, 0, 0>
const dvec3 X_AXIS(1.0, 0.0, 0.0);			//!< <1, 0, 0>
const dvec3 Y_AXIS(0.0, 1.0, 0.0);			//!< <0, 1, 0>
const dvec3 Z_AXIS(0.0, 0.0, 1.0);			//!< <0, 0, 1>

/**
 * @struct	Window
 * @brief	Represents a positionless rectangle, with a particular dimension
 */

struct Window {
	int width;			//!< width of window
	int height;			//!< height of window
	Window(int W, int H);
	int area() const;
	double aspectRatio() const;
};

/**
 * @class	BoundingBox
 * @brief	A bounding box in 2D.
 */

template <class T> struct BoundingBox {
	T lx;		//!< lower left corner's x value
	T ly;		//!< lower left corner's y value
	T rx;		//!< upper right corner's x value
	T ry;		//!< upper right corner's y value
	BoundingBox(T left, T right, T bottom, T top) {
		lx = left;
		rx = right;
		ly = bottom;
		ry = top;
	}
	T width() const {
		return rx - lx;
	}
	T height() const {
		return ry - ly;
	}
	double aspectRatio() const {
		return (double)width() / height();
	}
};

typedef BoundingBox<double> BoundingBoxd;
typedef BoundingBox<int>BoundingBoxi;

/**
 * @struct	BoundingBox3D
 * @brief	Represents a bounding box in 3D.
 */

struct BoundingBox3D {
	double lx;	//!< lower left x
	double ly;	//!< lower left y
	double lz;	//!< lower left z
	double rx;	//!< upper right x
	double ry;	//!< upper right y
	double rz;	//!< upper right z
	BoundingBox3D(double left, double right, double bottom, double top, double back, double front);
	double width() const;
	double height() const;
	double depth() const;
};

/**
 * @struct	Frame
 * @brief	Represents a coordinate frame
 */

struct Frame {
	dvec3 u;		//!< frame's "x" axis
	dvec3 v;		//!< frame's "y" axis
	dvec3 w;		//!< frame's "z" axis
	dvec3 origin;	//!< location of frame's origin
	dmat4 inverse;	//!< The inverse of the frame's transformation
	Frame();
	Frame(const dvec3 &O, const dvec3 &U, const dvec3 &V, const dvec3 &W);
	dvec3 toFrameCoords(const dvec3 &pt) const;
	dvec3 toWorldCoords(const dvec3 &pt) const;
	dvec3 toFrameVector(const dvec3 &pt) const;
	dvec3 toWorldVector(const dvec3 &pt) const;
	void setFrame(const dvec3 &O, const dvec3 &U, const dvec3 &V, const dvec3 &W);
	static Frame createOrthoNormalBasis(const dvec3 &pos, const dvec3 &w, const dvec3 &up);
	static Frame createOrthoNormalBasis(const dmat4 &viewingMatrix);
	dmat4 toViewingMatrix() const;
	friend ostream &operator <<(ostream &os, const Frame &frame);
protected:
	void setInverse();
};
