/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#pragma once

#include "Defs.h"
#include "IShape.h"
#include "ColorAndMaterials.h"

#ifndef WINDOWS
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

const int BYTES_PER_PIXEL = 3;			//!< RGB requires 3 bytes.

/**
 * @struct	FrameBuffer
 * @brief	Represents a framebuffer. Two identically sized 2D arrays. The color
 * 			buffer stores the colors and the depth buffer stores the corresponding
 * 			depth at each pixel.
 */

struct FrameBuffer {
	FrameBuffer(const int width, const int height);
	~FrameBuffer();
	void setFrameBufferSize(int width, int height);
	void setClearColor(const color &clearColor);
	void setColor(int x, int y, const color &C);
	color getColor(int x, int y) const;

	void clearColorAndDepthBuffers();
	void showColorBuffer() const;
	int getWindowWidth() const { return window.width; }
	int getWindowHeight() const { return window.height; }

	void setDepth(double x, double y, double depth);
	void setDepth(int x, int y, double depth);
	double getDepth(int x, int y) const;
	double getDepth(double x, double y) const;

	void showAxes(int x, int y, const Ray &ray, double thickness);
	void showAxes(const dmat4 &VM, const dmat4 &PM, const dmat4 &VPM,
					const BoundingBoxi &viewport, double thickness);
	void setPixel(int x, int y, const color &C, double depth);
protected:
	bool checkInWindow(int x, int y) const;
	Window window;							//!< Dimensions of framebuffer
	GLubyte clearColorUB[BYTES_PER_PIXEL];	//!< Clear color, as unsigned bytes
	color clearColor;						//!< Clear color
	GLubyte *colorBuffer;					//!< 2D array for holding colors
	double *depthBuffer;					//!< 2D array for holding depths
};
