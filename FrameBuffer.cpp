/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "Defs.h"
#include "Utilities.h"
#include "FrameBuffer.h"

/**
 * @fn	FrameBuffer::FrameBuffer(const int width, const int height)
 * @brief	Constructor
 * @param	width 	The width.
 * @param	height	The height.
 */

FrameBuffer::FrameBuffer(const int width, const int height) : window(width, height) {
	setFrameBufferSize(width, height);
}

/**
 * @fn	FrameBuffer::~FrameBuffer()
 * @brief	Destructor
 */

FrameBuffer::~FrameBuffer() {
	delete[] colorBuffer;
	delete[] depthBuffer;
}

/**
 * @fn	void FrameBuffer::setFrameBufferSize(int width, int height)
 * @brief	Sets frame buffer size
 * @param	width 	The width.
 * @param	height	The height.
 * @see https://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/
 */

void FrameBuffer::setFrameBufferSize(int width, int height) {
    window = Window(width, height);

	delete [] colorBuffer;
	delete [] depthBuffer;

	colorBuffer = new GLubyte[window.area() * BYTES_PER_PIXEL];
	depthBuffer = new double[window.area()];
}

/**
 * @fn	void FrameBuffer::setClearColor(const color &clear)
 * @brief	Sets clear color.
 * @param	clear	Clear color.
 */

void FrameBuffer::setClearColor(const color &clear) {
	clearColorUB[0] = (GLubyte)(clear.r * 255.0);
	clearColorUB[1] = (GLubyte)(clear.g * 255.0);
	clearColorUB[2] = (GLubyte)(clear.b * 255.0);
	clearColor = color(clearColorUB[0], clearColorUB[1], clearColorUB[2]);
}

/**
 * @fn	void FrameBuffer::clearColorAndDepthBuffers()
 * @brief	Clears the color and depth buffers
 */

void FrameBuffer::clearColorAndDepthBuffers() {
	for (int y = 0; y < window.height; ++y) {
		for (int x = 0; x < window.width; ++x) {
			std::memcpy(colorBuffer + BYTES_PER_PIXEL * (x + y * window.width),
				clearColorUB, BYTES_PER_PIXEL);
		}
	}
	const int SZ = window.area();
	std::fill(depthBuffer, depthBuffer + SZ, 1.0);
}

/**
 * @fn	void FrameBuffer::showColorBuffer() const
 * @brief	Shows the contents of the color buffer to screen.
 */

void FrameBuffer::showColorBuffer() const {
	glRasterPos2d(-1, -1);
	glDrawPixels(window.width, window.height, GL_RGB, GL_UNSIGNED_BYTE, colorBuffer);
	glFlush();
}

/**
 * @fn	void FrameBuffer::setColor(int x, int y, const color &rgb)
 * @brief	Sets a color at (x, y)
 * @param	x  	The x coordinate.
 * @param	y  	The y coordinate.
 * @param	rgb	The new RGB value.
 */

void FrameBuffer::setColor(int x, int y, const color &rgb) {
	if (x < 0 || x >= window.width || y < 0 || y >= window.height) {
		return;
	}

	color clampedColor = glm::clamp(rgb, 0.0, 1.0);

	GLubyte c[] = { (GLubyte)(clampedColor.r * 255),
					(GLubyte)(clampedColor.g * 255),
					(GLubyte)(clampedColor.b * 255) };

	std::memcpy(colorBuffer + BYTES_PER_PIXEL * (x + y * window.width), c, BYTES_PER_PIXEL);
}

/**
 * @fn	color FrameBuffer::getColor(int x, int y) const
 * @brief	Gets the color at (x, y)
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	The color at (x, y)
 */

color FrameBuffer::getColor(int x, int y) const {
	double red, green, blue;

	if (checkInWindow(x, y)) {
		GLubyte c[BYTES_PER_PIXEL];

		// Retrieve color values from the color buffer
		std::memcpy(c, colorBuffer + BYTES_PER_PIXEL * (x + y * window.width), BYTES_PER_PIXEL);

		// Convert individual color components back to doubleing point values
		red = c[0] / 255.0;
		green = c[1] / 255.0;
		blue = c[2] / 255.0;
	} else {
		red = clearColorUB[0] / 255.0;
		green = clearColorUB[1] / 255.0;
		blue = clearColorUB[2] / 255.0;
	}
	return color(red, green, blue);
}

/**
* @fn	void FrameBuffer::setDepth(int x, int y, double depth)
* @brief	Sets a depth at (x, y)
* @param	x	 	The x coordinate.
* @param	y	 	The y coordinate.
* @param	depth	The new depth.
*/

void FrameBuffer::setDepth(double x, double y, double depth) {
	setDepth((int)(x), (int)(y), depth);
}

/**
 * @fn	void FrameBuffer::setDepth(int x, int y, double depth)
 * @brief	Sets a depth at (x, y)
 * @param	x	 	The x coordinate.
 * @param	y	 	The y coordinate.
 * @param	depth	The new depth.
 */

void FrameBuffer::setDepth(int x, int y, double depth) {
	if (checkInWindow(x, y)) {
		depthBuffer[y * window.width + x] = depth;
	}
}

/**
* @fn	double FrameBuffer::getDepth(double x, double y) const
* @brief	Gets a depth at (x, y)
* @param	x	The x coordinate.
* @param	y	The y coordinate.
* @return	The depth at (x, y).
*/

double FrameBuffer::getDepth(int x, int y) const {
	if (checkInWindow(x, y)) {
		return depthBuffer[y * window.width + x];
	} else {
		return 0.0;
	}
}

/**
 * @fn	double FrameBuffer::getDepth(double x, double y) const
 * @brief	Gets a depth at (x, y)
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	The depth at (x, y).
 */

double FrameBuffer::getDepth(double x, double y) const {
	return getDepth((int)(x), (int)(y));
}

/**
 * @fn	bool FrameBuffer::checkInWindow(int x, int y) const
 * @brief	Returns true iff (x, y) is a valid window coordinate.
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @return	True iff (x, y) is a valid window coordinate.
 */

bool FrameBuffer::checkInWindow(int x, int y) const {
	return 0 <= x && x < window.width &&
			0 <= y && y < window.height;
}

/**
 * @fn	void FrameBuffer::setPixel(int x, int y, const color &C, double depth)
 * @brief	Sets a pixel's color and depth values
 * @param	x	 	Window x coordinate.
 * @param	y	 	Window y coordinate.
 * @param	C	 	The color to set.
 * @param	depth	The depth to set
 */

void FrameBuffer::setPixel(int x, int y, const color &C, double depth) {
	setDepth(x, y, depth);
	setColor(x, y, C);
}

static double computeAq(const QuadricParameters &qParams, const Ray &ray) {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &J = qParams.J;
	const double twoA = 2.0 * A;
	const double twoB = 2.0 * B;
	const double twoC = 2.0 * C;
	dvec3 Ro = ray.origin;
	const dvec3 &Rd = ray.dir;

	return A * glm::pow(Rd.x, 2) +
			B * glm::pow(Rd.y, 2) +
			C * glm::pow(Rd.z, 2);
}

static double computeBq(const QuadricParameters &qParams, const Ray &ray) {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &J = qParams.J;
	const double twoA = 2.0 * A;
	const double twoB = 2.0 * B;
	const double twoC = 2.0 * C;
	dvec3 Ro = ray.origin;
	const dvec3 &Rd = ray.dir;

	return twoA * Ro.x*Rd.x +
		twoB * Ro.y*Rd.y +
		twoC * Ro.z*Rd.z;
}

static double computeCq(const QuadricParameters &qParams, const Ray &ray) {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &J = qParams.J;
	const double twoA = 2.0 * A;
	const double twoB = 2.0 * B;
	const double twoC = 2.0 * C;
	dvec3 Ro = ray.origin;
	const dvec3 &Rd = ray.dir;

	return A * glm::pow(Ro.x, 2.0) +
		B * glm::pow(Ro.y, 2.0) +
		C * glm::pow(Ro.z, 2.0) +
		J;
}

static double solve(double A, double B, double C) {
	double D = B * B - 4 * A*C;
	if (D < 0) return -1.0;
	return (-B + std::sqrt(D)) / (2.0 * A);
}

/**
 * @fn	void FrameBuffer::showAxes(int x, int y, const Ray &ray, double thickness)
 * @brief	Inserts a R, G, or B pixel if the ray hits the X, Y, or Z axis.
 * @param	x   The x coordinate in the framebuffer
 * @param	y   The y coordinate in the framebuffer
 * @param	ray The viewing ray
 * @param	thickness how wide the axes should appear
 */

void FrameBuffer::showAxes(int x, int y, const Ray &ray, double thickness) {
	color currColor = getColor(x, y);
	static const QuadricParameters X = QuadricParameters::cylinderXQParams(thickness);
	static const QuadricParameters Y = QuadricParameters::cylinderYQParams(thickness);
	static const QuadricParameters Z = QuadricParameters::cylinderZQParams(thickness);
	const double AqX = computeAq(X, ray);
	const double BqX = computeBq(X, ray);
	const double CqX = computeCq(X, ray);
	const double AqY = computeAq(Y, ray);
	const double BqY = computeBq(Y, ray);
	const double CqY = computeCq(Y, ray);
	const double AqZ = computeAq(Z, ray);
	const double BqZ = computeBq(Z, ray);
	const double CqZ = computeCq(Z, ray);
	const double tX = solve(AqX, BqX, CqX);
	const double tY = solve(AqY, BqY, CqY);
	const double tZ = solve(AqZ, BqZ, CqZ);
	const dvec3 Xintercept = ray.getPoint(tX);
	const dvec3 Yintercept = ray.getPoint(tY);
	const dvec3 Zintercept = ray.getPoint(tZ);
	const int W = 2;
	if (x % W == 0 && y % W == 0) {		// color every other pixel
		if (tX >= 0 && Xintercept.x >= 0) {
			setColor(x, y, red);
		} else if (tY > 0 && Yintercept.y >= 0) {
			setColor(x, y, green);
		} else if (tZ > 0 && Zintercept.z >= 0) {
			setColor(x, y, blue);
		}
	}
}

void dot(FrameBuffer &fb, int x, int y, int W, const color &C, double Z) {
	for (int col = x - W; col <= x + W; col++) {
		for (int row = y - W; row <= y + W; row++) {
			if (row >= 0 && row < fb.getWindowHeight() &&
				col >= 0 && col < fb.getWindowWidth()) {
					fb.setColor(col, row, C);
			}
		}
	}
}

/**
 * @fn	void FrameBuffer::showAxes(const dmat4 &VM, const dmat4 &PM, const dmat4 &VPM, const BoundingBoxi &viewport, double thickness)
 * @brief	Displays axes.
 * @param	VM	viewing matrix
 * @param	PM	projection matrix
 * @param	VPM			viewport transformation matrix
 * @param	viewport	viewport
 * @param	thickness	how wide the axes should appear
 */

void FrameBuffer::showAxes(const dmat4 &VM, const dmat4 &PM, const dmat4 &VPM,
							const BoundingBoxi &viewport, double thickness) {
	const double LEN = 10;
	const double INC = 0.1;
	const static color C[] = { red, green, blue };
	for (double i = 0.0; i <= LEN; i += INC) {
		vector<dvec4> pts = { dvec4(i, 0.0, 0.0, 1.0), dvec4(0.0, i, 0.0, 1.0), dvec4(0.0, 0.0, i, 1.0) };
		for (size_t j = 0; j < pts.size(); j++) {
			dvec4 eye = VM * pts[j];
			dvec4 proj = PM * eye;
			dvec4 clip;
			if (proj.w >= 0) {
				clip = proj / proj.w;
			} else {
				clip.x /= -proj.w;
				clip.y /= -proj.w;
				clip.z = -std::abs(proj.z/proj.w);
				clip.w = 1.0;
			}
			const int W = 1;
			if (std::abs(clip.x) <= 1.0 && std::abs(clip.y) <= 1.0 && std::abs(clip.z) <= 1.0) {
				dvec4 window = VPM * clip;
				int x = (int)glm::clamp(window.x, (double)viewport.lx, (double)viewport.rx);
				int y = (int)glm::clamp(window.y, (double)viewport.ly, (double)viewport.ry);
				double currZ = getDepth(x, y);
				if (std::abs(window.z - currZ) < 0.01) {
					dot(*this, x, y, 1, C[j], window.z);
				}
			}
		}
	}
}
