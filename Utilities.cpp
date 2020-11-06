/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Defs.h"
#include "FrameBuffer.h"
#include "Utilities.h"
#include <math.h>
#include <algorithm>

/**
* @fn	ostream &operator << (ostream &os, const dvec2 &V)
* @brief	Output stream for vec2.
* @param	os		Output stream.
* @param	V		The vector.
*/

ostream &operator << (ostream &os, const dvec2 &V) {
	os << "[ " << V.x << " " << V.y << " ]";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dvec3 &V)
* @brief	Output stream for vec3.
* @param	os		Output stream.
* @param	V		The vector.
*/

ostream &operator << (ostream &os, const dvec3 &V) {
	os << "[ " << V.x << " " << V.y << " " << V.z << " ]";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dvec4 &V)
* @brief	Output stream for vec4.
* @param	os		Output stream.
* @param	V		The vector.
*/

ostream &operator << (ostream &os, const dvec4 &V) {
	os << "[ " << V.x << " " << V.y << " " << V.z << " " << V.w << " ]";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat432 &M)
* @brief	Output stream for mat2.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream &operator << (ostream &os, const dmat2 &M) {
	os << "\n";
	for (int row = 0; row < 2; row++) {
		os << "|\t";
		for (int col = 0; col < 2; col++) {
			os << std::setw(8) << std::setprecision(4) << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat3 &M)
* @brief	Output stream for mat3.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream &operator << (ostream &os, const dmat3 &M) {
	os << "\n";
	for (int row = 0; row < 3; row++) {
		os << "|\t";
		for (int col = 0; col < 3; col++) {
			os << std::setw(8) << std::setprecision(4) << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat4 &M)
* @brief	Output stream for mat4.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream &operator << (ostream &os, const dmat4 &M) {
	os << "\n";
	for (int row = 0; row < 4; row++) {
		os << "|\t";
		for (int col = 0; col < 4; col++) {
			os << std::setw(8) << std::setprecision(4) << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat4x2 &M)
* @brief	Output stream for mat4x2.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream &operator << (ostream &os, const dmat4x2 &M) {
	os << "\n";
	for (int row = 0; row < 2; row++) {
		os << "|\t";
		for (int col = 0; col < 4; col++) {
			os << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}
/**
 * @fn	void swap(double &a, double &b)
 * @brief	Swaps that values of two doubleing point numbers, without
 * 			using std.
 * @param [in,out]	a	First double.
 * @param [in,out]	b	Second double.
 */

void swap(double& a, double& b) {
	/* CSE 386 - todo  */
	double temp;
	temp = a;
	a = b;
	b = temp;
}


/**
 * @fn	bool approximatelyEqual(double a, double b)
 * @brief	Determines if two values are approximately equal.
 * 			That is, their values within EPSILON of each other.
 * @param	a	The first value.
 * @param	b	The second value.
 * @return	true iff (a-b) is in [-EPSILON, EPSILON].
 */

bool approximatelyEqual(double a, double b) {
	/* CSE 386 - todo  */
	double diff = glm::abs(a - b);
	if (diff < EPSILON) {
		return true;
	}
	else {
		return false;
	}
}

/**
 * @fn	bool approximatelyZero(double a)
 * @brief	Determines if a value is approximately zero.
 * 			That is, the value is within EPSILON of zero.
 * @param	a	The value.
 * @return	true iff a is in [-EPSILON, EPSILON].
 */

bool approximatelyZero(double a) {
	/* CSE 386 - todo  */
	if (a > -EPSILON && a < EPSILON) {
		return true;
	}
	else {
		return false;
	}
	}

/**
 * @fn	double normalizeDegrees(double degrees)
 * @brief	Converts an arbitrary number of degrees to an equivalent
 * 			number of degrees in the range [0, 360). Loops should NOT
 *          be used in this function.
 * @param	degrees	The degrees.
 * @return	Normalized degrees in the range [0, 360).
 * @test	normalizeDegrees(0) --> 0
 * @test	normalizeDegrees(1) --> 1
 * @test	normalizeDegrees(-1) --> 359
 * @test	normalizeDegrees(-721) --> 359
 */

double normalizeDegrees(double degrees) {
	/* CSE 386 - todo  */
	if (degrees < 0 && degrees > -361) {
		degrees = degrees + 360;
	}
	else if (degrees > 360 && degrees < 721) {
		degrees = degrees - 360;
	}
	else if (degrees > 720 && degrees < 901) {
		degrees = degrees - 720;
	}
	else if (degrees < -360 && degrees > -721) {
		degrees = degrees + 720;
	}
	return degrees;
}

/**
 * @fn	double normalizeRadians(double rads)
 * @brief	Converts an arbitrary number of radians to an equivalent
 * 			number of radians in the range [0, 2*M_PI). Loops should NOT
 *          be used in this function.
 * @param	rads	The radians.
 * @return	Normalized radians in the range [0, 2*M_PI).
 * @test	normalizeRadians(0) --> 0
 * @test	normalizeRadians(1) --> 1
 * @test	normalizeRadians(3*M_PI) --> M_PI
 * @test	normalizeRadians(-31*M_PI) --> M_PI
 */

double normalizeRadians(double rads) {
	/* CSE 386 - todo  */
	if (rads >= 0) {
		rads = (fmod(rads, TWO_PI));
		return rads;
	}
	rads = (TWO_PI + (fmod(rads, TWO_PI)));
	return rads;
	// old below
	/*if (rads <= TWO_PI && rads > 0) {
		return rads;
	}
	else if (rads >= (-1 * TWO_PI) && rads < 0) {
		return TWO_PI - abs(rads);
	}
	else if (rads < 0) {
		return TWO_PI - abs((fmod(rads, TWO_PI)));
	}
	rads = fmod(rads, TWO_PI);
	return rads;*/
}

/**
 * @fn	double rad2deg(double rads)
 * @brief	Converts radians to degrees.  This function behaves like glm::degrees,
 * without using glm::degrees.
 * @param	rads	The radians.
 * @return	Degrees.
 */

double rad2deg(double rads) {
	rads = (rads * (180 / 3.14159));
	return rads;
}

/**
 * @fn	double deg2rad(double degs)
 * @brief	Converts degrees to radians. This function behaves like glm::radians,
 * without using glm::radians.
 * @param	degs	The degrees.
 * @return	Radians.
 */

double deg2rad(double degs) {
	degs = (degs * (3.14159 / 180));
	return degs;
}

/**
* @fn	double min(double A, double B, double C)
* @brief	Determines the minimum of three values, using std::min.
* @param	A	First value.
* @param	B	Second value
* @param	C	Third value.
* @return	The minimum value.
*/

double min(double A, double B, double C) {
	/* CSE 386 - todo  */
	double min1 = std::min(A, B);
	double min = std::min(min1,C);
	return min;
}

/**
* @fn	double max(double A, double B, double C)
* @brief	Determines the maximum of three values, using std::max.
* @param	A	First value.
* @param	B	Second value
* @param	C	Third value.
* @return	The maximum value.
*/

double max(double A, double B, double C) {
	/* CSE 386 - todo  */
	double max1 = std::max(A,B);
	double max = std::max(max1,C);
	return max;
}

/**
 * @fn	void pointOnUnitCircle(double angleRads, double &x, double &y)
 * @brief	Determines the (x,y) position of a point on the standard
 * 			unit circle.
 * @param 		  	angleRads	The angle in radians.
 * @param [in,out]	x		 	A double to process.
 * @param [in,out]	y		 	A double to process.
 */
void pointOnUnitCircle(double angleRads, double &x, double &y) {
	x = cos(angleRads);
	y = sin(angleRads);
}

/**
	   * @fn 	double areaOfTriangle(float a, float b, float c)
	   * @brief	Computes the area of triangle using Heron's formula
	   * @param	a length of first side.
	   * @param	b length of second side.
	   * @param	c length of third side.
	   * @return	Area of triangle. Returns -1.0 if any of the sides
	   *         are <= 0.
	   */
double areaOfTriangle(double  a, double b, double c) {
	double result = 0;
	double s = ((a + b + c) / 2);
	if (a <= 0 || b <= 0 || c <= 0) {
		return -1.0;
	}
	result = sqrt(s * (s - a) * (s - b) * (s - c));
	return result;
}

/**
* @fn	dvec2 pointOnCircle(const dvec2 &center, double R, double angleRads)
* @brief	Computes the (x,y) value of a point on the circle centered on 'center',
* 			having radius R. The point is determined by sweeping an arc 'angleRads'.
* @param	center   	The center of the circle
* @param	R		 	Radius of circle.
* @param	angleRads	The angle in radians.
* @return	The point on the circle.
*/

dvec2 pointOnCircle(const dvec2 &center, double R, double angleRads) {
	/* CSE 386 - todo  */
	return dvec2(0, 0);
}

/**
* @fn	double directionInDegrees(double x1, double y1, double x2, double y2)
* @brief	Compute the direction/heading of (x2,y2), relative
* 			to (x1,y1). Result is in range [0, 360).
* @param	x1  x value of first (x,y) pair
* @param	y1  y value of first (x,y) pair
* @param	x2  x value of second (x,y) pair
* @param	y2  y value of second (x,y) pair
* @return	The angle of (x2,y2) relative to (x1,y1).
* @test	directionInDegrees(2, 10, 3, 11) --> 45
* @test	directionInDegrees(3, 11, 2, 10) --> 225
* @test	directionInDegrees(0, 0, 10, 10) --> 45
* @test	directionInDegrees(2, 2, 2, 0) --> 270
*/

double directionInDegrees(double x1, double y1, double x2, double y2) {
	/* CSE 386 - todo  */
	return 0;
}

/**
* @fn	double directionInDegrees(const dvec2 &referencePt, const dvec2 &targetPt)
* @brief	Compute the direction/heading of 'targetPt', relative
* 			to referencePt.
* @param	referencePt	Reference point.
* @param	targetPt	Target point point.
* @return	A double.
* @test	directionInDegrees((2,10), (3,11)) --> 45
*/

double directionInDegrees(const dvec2 &referencePt, const dvec2 &targetPt) {
	/* CSE 386 - todo  */
	return 0;
}

/**
* @fn	double directionInDegrees(const dvec2 &targetPt)
* @brief	Compute the direction/heading of 'targetPt', relative
* 			to the origin.
* @param	targetPt	Target point.
* @return	The direction in degrees.
* @test	directionInDegrees((1,0)) --> 0
* @test	directionInDegrees((1,1)) --> 45
*/

double directionInDegrees(const dvec2 &targetPt) {
	/* CSE 386 - todo  */
	return 0;
}

/**
* @fn	dvec2 doubleIt(const dvec2 &V)
* @brief	Computes 2*V
* @param	V	The vector.
* @return	2*V.
*/

dvec2 doubleIt(const dvec2 &V) {
	/* CSE 386 - todo  */
	return V + V;
}

/**
* @fn	dvec3 myNormalize(const dvec3 &V)
* @brief	Computes the normalization of V, without calling glm::normalize.
* @param	V	The vector.
* @return	Normalized vector V.
*/

dvec3 myNormalize(const dvec3 &V) {
	/* CSE 386 - todo  */
	double len = glm::length(V);
	return V / len;
}

/**
* @fn	bool isOrthogonal(const dvec3 &a, const dvec3 &b)
* @brief	Determines if two vectors are orthogonal, or nearly orthogonal.
* @param	a	The first vector.
* @param	b	The second vector.
* @return	True iff the two vector are orthogonal.
*/

bool isOrthogonal(const dvec3 &a, const dvec3 &b) {
	double dotProd = (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
	if (dotProd == 0) {
		return true;
	}
	else if (approximatelyZero(dotProd)) {
		return true;
	}
	return false;
}

/**
 * @fn	double cosBetween(const dvec2 &v1, const dvec2 &v2)
 * @brief	Cosine between v1 and v2. 
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	The cosine between v1 and v2.
 */

double cosBetween(const dvec2 &v1, const dvec2 &v2) {
	/* CSE 386 - todo  */
	double cos = glm::dot(v1, v2)/(glm::length(v1)*glm::length(v2));
	return cos;
}

/**
 * @fn	double cosBetween(const dvec3 &v1, const dvec3 &v2)
 * @brief	Computes the cosine between v1 and v2.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	A double.
 */

double cosBetween(const dvec3 &v1, const dvec3 &v2) {
	/* CSE 386 - todo  */
	double cos = glm::dot(v1, v2) / (glm::length(v1)*glm::length(v2));
	return cos;
}

/**
 * @fn	double radsBetween(const dvec2 &v1, const dvec2 &v2)
 * @brief	Computes the radians between two vectors. Uses trig functions.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	The number of radians between the two vectors.
 */

double radsBetween(const dvec2 &v1, const dvec2 &v2) {
	/* CSE 386 - todo  */
	return 0;
}

/**
 * @fn	double radsBetween(const dvec3 &v1, const dvec3 &v2)
 * @brief	Computes the radians between two vectors. Uses trig functions.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	The number of radians between the two vectors.
 */

double radsBetween(const dvec3 &v1, const dvec3 &v2) {
	/* CSE 386 - todo  */
	return 0;
}

/**
* @fn	dvec3 project(const dvec3 &from, const dvec3 &onto)
* @brief	Project the vector 'from' onto the vector 'onto'
* @param	from	Source for the.
* @param	onto	The onto.
* @return	'from' projected onto 'onto'
*/

dvec3 project(const dvec3 &from, const dvec3 &onto) { // not sure if correct
	/* CSE 386 - todo  */
	// dot product of from and onto divided by (magnitude of b)^2
	double dotProd = (from.x * onto.x) + (from.y * onto.y) + (from.z * onto.z);
	double magFirst = ((onto.x * onto.x) + (onto.y * onto.y) + (onto.z * onto.z));
	double magnitude = magFirst * magFirst;
	dotProd = dotProd / magnitude;
	// return dotProd;
	return from;
}

/**
* @fn	dvec2 rotate90CCW(const dvec2 &pt)
* @brief	Rotate a 2D point about the origin, 90 degrees counterclockwise.
* @param	pt	A dvec2 to process.
* @return	The point rotated 90 degrees counterclockwise.
* @test	rotate90CCW((-4,-10)) -> (10,-4)
* @test	rotate90CCW((10,-4)) -> (4,10)
*/

dvec2 rotate90CCW(const dvec2 &pt) {
	/* CSE 386 - todo  */
	return pt;
}

/**
 * @fn	double map(double x, double xLow, double xHigh, double yLow, double yHigh)
 * @brief	Linearlly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	xLow 	The low value of the x range.
 * @param 		  	xHigh	The high value of the x range.
 * @param 		  	yLow 	The low value of the y range.
 * @param 		  	yHigh	The high value of the y range.
 * @test	map(2, 0, 5, 10, 11) --> 10.4
 */

double map(double x, double xLow, double xHigh, double yLow, double yHigh) {
	/* CSE 386 - todo  */
	double temp1 = x - xLow; // first section
	double temp2 = yHigh - yLow; // top of second section
	double temp3 = xHigh - xLow; // bot of second section
	double temp4 = temp2 / temp3; // result of second section
	temp4 = temp4 + yLow; // 
	x = temp1 * temp4;
	return x;
}

/**
 * @fn	void map(double x, double xLow, double xHigh, double yLow, double yHigh, double &y)
 * @brief	Linearlly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	xLow 	The low value of the x range.
 * @param 		  	xHigh	The high value of the x range.
 * @param 		  	yLow 	The low value of the y range.
 * @param 		  	yHigh	The high value of the y range.
 * @param [in,out]	y	 	The mapped value in the y range.
 * @test	map(2, 0, 5, 10, 11, y) --> y = 10.4
 */

void map(double x, double xLow, double xHigh, double yLow, double yHigh, double &y) {
	double temp1 = x - xLow; // first section
	double temp2 = yHigh - yLow; // top of second section
	double temp3 = xHigh - xLow; // bot of second section
	double temp4 = temp2 / temp3; // result of second section
	temp4 = temp4 + yLow; // 
	y = temp1 * temp4;
}

/**
 * @fn	vector<double> quadratic(double A, double B, double C)
 * @brief	Solves the quadratic equation, given A, B, and C.
 * 			0, 1, or 2 roots are inserted into the vector and returned.
 * 			The roots are placed into the vector in sorted in ascending order.
 * @param	A	A.
 * @param	B	B.
 * @param	C	C.
 * @return	Vector containing the real roots.
 * @test	quadratic(1,4,3) --> [-3,-1]
 * @test	quadratic(1,0,0) --> [0]
 * @test	quadratic(-4, -2, -1) --> []
 */

vector<double> quadratic(double A, double B, double C) {
	/* CSE 386 - todo  */
	double disc = B * B - 4 * A * C;
	vector<double> vecOfRoots(2);
	double discRoot = sqrt(disc);
	double denom = 2 * A;
	double root1 = (-B + discRoot) / denom;
	double root2 = (-B - discRoot) / denom;
	vecOfRoots[0] = -1;
	vecOfRoots[1] = +1;

	if (disc > 0) {
		vecOfRoots[0] = std::min(root1, root2);
		vecOfRoots[1] = std::max(root1, root2);
		return vecOfRoots;
	}
	else if (disc == 0) {
		vecOfRoots[0] = root1;
		return vecOfRoots;
	}
	else if (disc < 0) {
		return vecOfRoots;
	}
}

/**
 * @fn	int quadratic(double A, double B, double C, double roots[2])
 * @brief	Solves the quadratic equation, given A, B, and C.
 * 			0, 1, or 2 roots are inserted into the array 'roots'.
 * 			The roots are sorted in ascending order.
 * @param	A	 	A.
 * @param	B	 	B.
 * @param	C	 	C.
 * @param	roots	The real roots.
 * @test	quadratic(1, 4, 3, ary) --> returns 2 and fills in ary with: [-3,-1]
 * @test	quadratic(1 ,0, 0, ary) --> returns 1 and fills in ary with: [0]
 * @test	quadratic(-4, -2, -1, ary) --> returns 0 and does not modify ary.
 * @return	The number of real roots put into the array 'roots'
*/

int quadratic(double A, double B, double C, double roots[2]) {
	/* CSE 386 - todo  */
	roots[0] = -1;
	roots[1] = +1;
	double disc = B * B - 4 * A * C;
	double discRoot = sqrt(disc);
	double denom = 2 * A;
	double root1 = (-B + discRoot) / denom;
	double root2 = (-B - discRoot) / denom;

	if (disc > 0) {
		roots[0] = std::min(root1, root2);
		roots[1] = std::max(root1, root2);
		return 2;
	}
	else if (disc == 0) {
		roots[0] = root1;
		return 1;
	}
	else{
		return 0;
	}
}


/**
 * @fn	double areaOfParallelogram(const dvec3 &v1, const dvec3 &v2)
 * @brief	Computes the area of parallelogram, given two vectors eminating
 * 			from the same corner of the parallelogram.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	Area of parallelogram.
 */

double areaOfParallelogram(const dvec3 &v1, const dvec3 &v2) {
	// find magnitude of the cross product of v1 and v2 and return it
	double area = sqrt(pow((v1.y * v2.z - v2.y * v1.z), 2) + pow((v1.x * v2.z - v2.x * v1.z), 2) + pow((v1.x * v2.y - v2.x * v1.y), 2));

	return area;
}


/**
 * @fn	double areaOfTriangle(const dvec3 &pt1, const dvec3 &pt2, const dvec3 &pt3)
 * @brief	Computes the area of triangle.
 * @param	pt1	The first point.
 * @param	pt2	The second point.
 * @param	pt3	The third point.
 * @return	Area of triangle.
 */

double areaOfTriangle(const dvec3 &pt1, const dvec3 &pt2, const dvec3 &pt3) {
	// I need to find the dot product of (pt3 - pt1) and (pt2 - pt1) and half that. 
	dvec3 part1 = pt3 - pt1;
	dvec3 part2 = pt2 - pt1;
	// this might be dot prod double cross = sqrt(pow((part1.y * part2.z - part2.y * part1.z), 2) + pow((part1.x * part2.z - part2.x * part1.z), 2) + pow((part1.x * part2.y - part2.x * part1.y), 2));
	dvec3 crossProd = cross(part1, part2);
	double result = 0.0;
	// dvec3 result = crossProd * 0.5f; // not sure how to get this to a double.

	return result;
}

/**
* @fn	bool isOrthoNormalBasis(const dvec3 &u, const dvec3 &v, const dvec3 &w)
* @brief	Determines if three vectors form an orthonormal basis.
* @param	u	The u vector.
* @param	v	The v vector.
* @param	w	The w vector.
* @return	True if ortho normal basis, false if not.
*/

bool isOrthoNormalBasis(const dvec3 &u, const dvec3 &v, const dvec3 &w) {
	/* CSE 386 - todo  */
	return false;
}

/**
 * @fn	bool isRightHandedOrthoNormalBasis(const dvec3 &u, const dvec3 &v, const dvec3 &w)
 * @brief	Determines if three vectors form a right-handed orthonormal basis.
 * @param	u	The u vector.
 * @param	v	The v vector.
 * @param	w	The w vector.
 * @return	true iff right handed ortho normal basis.
 */

bool isRightHandedOrthoNormalBasis(const dvec3 &u, const dvec3 &v, const dvec3 &w) {
	/* CSE 386 - todo  */
	return false;
}

/**
* @fn	dvec3 pointingVector(const dvec3 &pt1, const dvec3 &pt2)
* @brief	Computes unit-length pointing vector.
* @param	pt1	The first point.
* @param	pt2	The second point.
* @return	Unit length vector that points from pt1 to pt2.
*/

dvec3 pointingVector(const dvec3 &pt1, const dvec3 &pt2) {
	// I do not know how I can find the length of a vector that points to another vector as I did not find anything this specific in the slides but I know how to find
	// the unit length of a vector so I will try that.
	// I found that "vector subtraction can be used to find a vector that points from one to another so I suppose that means pt2 - pt1.
	double unitLength = sqrt((pt1.x * pt1.x) + (pt1.y * pt1.y) + (pt1.z * pt1.z));
	dvec3 result = pt2 - pt1;
	return result;
}

/**
* @fn	dvec3 normalFrom3Points(const dvec3 &pt0, const dvec3 &pt1, const dvec3 &pt2)
* @brief	Computes a unit-length normal vector from 3 points, specified in counterclockwise order.
* @param	pt0	The first point.
* @param	pt1	The second point.
* @param	pt2	The third point.
* @return	Normal vector.
*/

dvec3 normalFrom3Points(const dvec3 &pt0, const dvec3 &pt1, const dvec3 &pt2) {
	dvec3 crossy = cross(pt1 - pt0, pt2 - pt0);
	dvec3 norm = crossy / glm::length(crossy);
	return norm;
}

/**
* @fn	dvec3 normalFrom3Points(const vector<dvec3> pts)
* @brief	Computes a unit-length normal vector from 3 points, specified in counterclockwise order.
* @param	pts	The points.
* @return	The normal vector.
*/

dvec3 normalFrom3Points(const vector<dvec3> &pts) { // I don't really understand how I am able to get the three points out of pts and how to return it after finding 
													//the normal vector
	//dvec3 crossy = cross(pts.y - pts.x, pts.z - pts.x);
	dvec3 pt0 = pts[0];
	dvec3 pt1 = pts[1];
	dvec3 pt2 = pts[2];
	dvec3 crossy = cross(pt1 - pt0, pt2 - pt0);
	dvec3 norm = crossy / glm::length(crossy);
	return norm;
}

/**
* @fn	dvec3 getRow(const dmat3 &mat, int row)
* @brief	Retrieves a particular row out of a matrix.
* @param	mat	The matrix.
* @param	row	The row.
* @return	The extracted row.
*/

dvec3 getRow(const dmat3 &mat, int row) {

	return 	dvec3(mat[0][row], mat[1][row], mat[2][row]);

}

/**
 * @fn	dvec3 getCol(const dmat3 &mat, int col)
 * @brief	Retrieves a particular column out of a matrix.
 * @param	mat	The matrix.
 * @param	col	The column.
 * @return	The extracted column.
 */

dvec3 getCol(const dmat3 &mat, int col) {
	dvec3 result = mat[col];
	return result;
}

/**
* @fn	bool isInvertible(const dmat432 &mat)
* @brief	Determines if mat is invertible
* @param	mat	The matrix.
* @return	true if invertible, false if not.
*/

bool isInvertible(const dmat2 &mat) {
	double determinant = glm::determinant(mat);
	if (determinant == 0) {
		return false;
	}
	else if (determinant != 0) {
		return true;
	}
}

/**
 * @fn	bool isInvertible(const dmat3 &mat)
 * @brief	Determines if mat is invertible
 * @param	mat	The matrix.
 * @return	true if invertible, false if not.
 */

bool isInvertible(const dmat3& mat) {
	double determinant = glm::determinant(mat);
	if (determinant == 0) {
		return false;
	}
	else if (determinant != 0) {
		return true;
	}
}

/**
 * @fn	dvec3 solveLinearSystem(const dmat3 &M, const dvec3 &y)
 * @brief	Solves a linear system
 * @param	M	The matrix.
 * @param	y	The vector.
 * @return	x, such that M*x = y. Returns (0,0,0) if no solution exists (i.e., M is singular).
 */

dvec3 solveLinearSystem(const dmat3 &M, const dvec3 &y) {
	if (isInvertible(M)) {
		return (glm::inverse(M) * y);
	}
	return dvec3(0,0,0);
}

/**
 * @fn	dmat3 addMatrices(const vector<dmat3> &M)
 * @brief	Adds the several matrices together.
 * @param	M	Vector of matrices.
 * @return	M[0]+M[1]+...+M[n-1]
 */

dmat3 addMatrices(const vector<dmat3>& M) {
	/* CSE 386 - todo  */
	// add matrixes in loops, may be able to add them directly
	dmat3 result;
	for (int i = 0; i < M.size(); i++) {
		// for (int j = 0; j < M[i].length(); i++) {
			result = result + M[i];
		// }
	}
	return result;
}

/**
 * @fn	dmat3 multiplyMatrices(const vector<dmat3> &M)
 * @brief	Multiply many matrices together.
 * @param	M	The vector of matrices.
 * @return	Returns M[0]*M[1]*...M[n-1].
 */

dmat3 multiplyMatrices(const vector<dmat3> &M) {
	dmat3 result;
	for (int i = 0; i < M.size(); i++) {
		// for (int j = 0; j < M[i].length(); i++) {
		result = result * M[i];
		// }
	}
	return result;
}

/**
 * @fn	dvec3 multiplyMatrixAndVertex(const dmat3 &M, const dvec3 &x)
 * @brief	Multiply matrix and vertex
 * @param	M	A matrix.
 * @param	x	A vector.
 * @return	Returns M*x.
 */

dvec3 multiplyMatrixAndVertex(const dmat3 &M, const dvec3 &x) {
	dvec3 answer = M * x;
	return answer;
}

/**
 * @fn	dvec3 multiplyMatricesAndVertex(const vector<dmat3> &M, const dvec3 &x)
 * @brief	Multiply matrices and vertex
 * @param	M	A vector of matrices to process.
 * @param	x	The vertex to process.
 * @return	Returns the result of M[0]*M[1]*...M[n-1]*x
 */

dvec3 multiplyMatricesAndVertex(const vector<dmat3> &M, const dvec3 &x) {
	//todo
	dvec3 answer = (M[0] * x);
	dmat3 temp = M[0];
	for (int i = 1; i < M.size(); i++) {
		temp = temp * M[i];
	}
	answer = temp * x;
	return answer;
}

/**
 * @fn	vector<dvec3> multiplyMatrixAndVertices(const dmat3 &M, const vector<dvec3> &verts)
 * @brief	Returns the vector containing: <M*x[0], M*x[1], ... M*x[n-1]>
 * @param	M	 	A dmat3 to process.
 * @param	verts	The vertices.
 * @return	Returns the vector: <M*x[0], M*x[1], ... M*x[n-1]>
 */

vector<dvec3> multiplyMatrixAndVertices(const dmat3 &M, const vector<dvec3> &verts) {
	/* CSE 386 - todo  */
	vector<dvec3> result;

	for (int i = 0; i < verts.size(); i++) {
		result.push_back(M * verts[i]);
	}
	return result;
}

/**
 * @fn	vector<dvec3> multiplyMatricesAndVertices(const vector<dmat3> &M, const vector<dvec3> &verts)
 * @brief	Multiply matrices and vertices
 * @param	M	 	Vector of matrices.
 * @param	verts	Vector of vertices.
 * @return	Returns: <BIGMAT*x[0], BIGMAT*x[1], ... BIGMAT*x[n-1]>, where BIGMAT = M[0]*M[1]*...M[n-1]
 */

vector<dvec3> multiplyMatricesAndVertices(const vector<dmat3> &M, const vector<dvec3> &verts) {
	/* CSE 386 - todo  */
	vector<dvec3> result;
	dmat3 temp = M[0];
	for (int j = 1; j < M.size(); j++) {
		temp = temp * M[j];
	}
	for (int i = 0; i < verts.size(); i ++) {
		result.push_back(temp * verts[i]);
	}
	return result;
}

/**
* @fn	dmat3 T(double dx, double dy)
* @brief	Creates the 3x3 translation matrix for 2D systems.
* @param	dx	x translation factor.
* @param	dy	y translation factor.
* @return	The scaling matrix.
*/

dmat3 T(double dx, double dy) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 S(double sx, double sy)
 * @brief	Creates the 3x3 scaling matrix for 2D systems.
 * @param	sx	x scale factor.
 * @param	sy	y scale factor.
 * @return	The scaling matrix.
 */

dmat3 S(double sx, double sy) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 R(double deg)
 * @brief	Returns 3x3 rotation matrix for 2D rotations.
 * @param	deg	Degrees to rotate.
 * @return	The rotation matrix.
 */

dmat3 R(double deg) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 horzShear(double a)
 * @brief	Horizontal shear.
 * @param	a	Shearing parameter.
 * @return	The 3x3 shearing matrix.
 */

dmat3 horzShear(double a) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 vertShear(double a)
 * @brief	Vertical shear.
 * @param	a	Shearing parameter.
 * @return	The 3x3 shearing matrix.
 */

dmat3 vertShear(double a) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 reflectAcrossYaxis()
 * @brief	Reflect across the Y axis.
 * @return	The 3x3 matrix.
 */

dmat3 reflectAcrossYaxis() {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 reflectAcrossOrigin()
 * @brief	Reflect across the origin.
 * @return	The 3x3 matrix.
 */

dmat3 reflectAcrossOrigin() {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 scale2XAboutPoint(double x, double y)
 * @brief	Scale objects 2X about a particular point.
 * @param	x	The x value about which scaling should occur.
 * @param	y	The y value about which scaling should occur.
 * @return	The 3x3 scale matrix.
 */

dmat3 scale2XAboutPoint(float x, float y) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 reflectAcrossLineYeqXplus50()
 * @brief	Reflect objects across the line y = x + 50
 * @return	The reflection matrix.
 */

dmat3 reflectAcrossLineYeqXplus50() {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
 * @fn	dmat3 rotateAroundOwnAxisAndAroundSun(double distFromOrigin, double angleAboutOwnAxis, double angleAboutOrigin)
 * @brief	Perform a earth-like rotation about the sun/origin.
 * @param	distFromOrigin		How far object is away from origin.
 * @param	angleAboutOwnAxis	How many radians the object is rotated about its own axis
 * @param	angleAboutOrigin	How many radians the object is rotated about the origin
 * @return	The 3x3 scale matrix.
 */

dmat3 rotateAroundOwnAxisAndAroundSun(double distFromOrigin,
												double angleAboutOwnAxis,
												double angleAboutOrigin) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
* @fn	dmat4 T(double dx, double dy, double dz)
* @brief	Creates the 4x4 translation matrix for 3D systems.
* @param	dx	The x translation factor.
* @param	dy	The y translation factor.
* @param	dz	The z translation factor.
* @return	The 4x4 translation matrix for 3D systems.
*/

dmat4 T(double dx, double dy, double dz) {
	/* CSE 386 - todo  */
	return dmat4();
}

/**
* @fn	dmat4 S(double sx, double sy, double sz)
* @brief	Creates the 4x4 scaling matrix for 3D systems.
* @param	sx	The x scaling factor.
* @param	sy	The y scaling factor.
* @param	sz	The z scaling factor.
* @return	The 4x4 scaling matrix for 3D systems.
*/

dmat4 S(double sx, double sy, double sz) {
	/* CSE 386 - todo  */
	return dmat4();
}

/**
* @fn	dmat4 S(double scale)
* @brief	Creates the 4x4 scaling matrix for 3D systems.
* @param	scale	The scale.
* @return	The 4x4 [uniform] scaling matrix for 3D systems.
*/

dmat4 S(double scale) {
	/* CSE 386 - todo  */
	return dmat4();
}

/**
* @fn	dmat3 Rx(double rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +x axis.
*/

dmat4 Rx(double rads) {
	/* CSE 386 - todo  */
	return dmat4();
}

/**
* @fn	dmat3 Ry(double rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +y axis.
*/

dmat4 Ry(double rads) {
	/* CSE 386 - todo  */
	return dmat4();
}

/**
* @fn	dmat3 Rz(double rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +z axis.
*/

dmat4 Rz(double rads) {
	/* CSE 386 - todo  */
	return dmat4();
}

/**
* @fn	mat3 mystery(float a, float b)
* @brief	Returns W*W*W, where W = [[a b a][b b a][b b a]].
* @param	a	The value of a.
* @param	b	The value of b.
* @return	Returns W*W*W, where W = [[a b a][b b a][b b a]]
*/

glm::mat3 mystery(float a, float b) {
	/* CSE 386 - todo  */
	return dmat3();
}

/**
* @fn	void computeXYZFromAzimuthAndElevation(double R, double az, double el, double &x, double &y, double &z)
* @brief	Computes (x,y,z), given a specific azimuth/elevation angles.
* @param 		  	R 	The radius of the sphere.
* @param 		  	az	Azimuth
* @param 		  	el	Elevation.
* @param [in,out]	x 	A double to process.
* @param [in,out]	y 	A double to process.
* @param [in,out]	z 	A double to process.
*/

void computeXYZFromAzimuthAndElevation(double R,
										double az, double el,
										double &x, double &y, double &z) {
	z = R*std::cos(el)*std::cos(az);
	x = R*std::cos(el)*std::sin(az);
	y = R*std::sin(el);
}

/**
* @fn	void computeAzimuthAndElevationFromXYZ(double x, double y, double z, double &R, double &az, double &el)
* @brief	Calculates the azimuth and elevation from xyz
* @param 		  	x 	The x coordinate.
* @param 		  	y 	The y coordinate.
* @param 		  	z 	The z coordinate.
* @param [in,out]	R 	The radius of the sphere.
* @param [in,out]	az	Azimuth.
* @param [in,out]	el	Elevation.
*/

void computeAzimuthAndElevationFromXYZ(double x, double y, double z,
										double &R, double &az, double &el) {
	R = glm::length(dvec3(x, y, z));
	az = std::atan2(x, z);
	el = std::atan2(y, glm::length(dvec2(x, z)));
}

/**
* @fn	void computeAzimuthAndElevationFromXYZ(const dvec3 &pt, double &R, double &az, double &el)
* @brief	Compute the azimuth/elevation (relative to the origin) of the point (x,y,z)
* @param 		  	pt	The point - (x,y,z).
* @param [in,out]	R 	The radius of the sphere.
* @param [in,out]	az	Azimuth.
* @param [in,out]	el	Elevation.
*/

void computeAzimuthAndElevationFromXYZ(const dvec3 &pt,
										double &R, double &az, double &el) {
	computeAzimuthAndElevationFromXYZ(pt.x, pt.y, pt.z, R, az, el);
}

/**
* @fn	bool inRangeInclusive(double val, double lo, double hi)
* @brief	Determines if value is in a range inclusive
* @param	val	The value.
* @param	lo 	The low end of the range.
* @param	hi 	The high end of the range.
* @return	True iff val in [lo, hi].
*/

bool inRangeInclusive(double val, double lo, double hi) {
	return val >= lo && val <= hi;
}

/**
* @fn	bool inRangeExclusive(double val, double lo, double hi)
* @brief	Determines if value is in a range exclusive
* @param	val	The value.
* @param	lo 	The low end of the range.
* @param	hi 	The high end of the range.
* @return	true iff val in (lo, hi).
*/

bool inRangeExclusive(double val, double lo, double hi) {
	return val > lo && val < hi;
}

/**
* @fn	bool inRectangle(double x, double y, double left, double bottom, double right, double top)
* @brief	Determines if (x,y) is inside (or on) a rectangle.
* @param	x	  	The x coordinate.
* @param	y	  	The y coordinate.
* @param	left  	The left edge of rectangle.
* @param	bottom	The bottom edge of rectangle.
* @param	right 	The right edge of rectangle.
* @param	top   	The top edge of rectangle.
* @return	true iff (x,y) is in/on the rectangle.
*/

bool inRectangle(double x, double y, double left, double bottom, double right, double top) {
	return inRangeInclusive(x, left, right) &&
		inRangeInclusive(y, bottom, top);
}

/**
* @fn	bool inRectangle(const dvec2 &pt, const dvec2 &lowerLeft, const dvec2 &upperRight)
* @brief	Determines if (x,y) is inside (or on) a rectangle.
* @param	pt		  	The point - (x,y)
* @param	lowerLeft 	The lower left corner of the rectangle - (left, bottom).
* @param	upperRight	The upper right corner of the rectangle - (right, top).
* @return	true iff (x,y) is in/on the rectangle.
*/

bool inRectangle(const dvec2 &pt, const dvec2 &lowerLeft, const dvec2 &upperRight) {
	return inRangeInclusive(pt.x, lowerLeft.x, upperRight.x) &&
		inRangeInclusive(pt.y, lowerLeft.y, upperRight.y);
}

/**
* @fn	bool approximateVectorEquality(const dvec3 &v1, const dvec3 &v2)
* @brief	Determines if two vectors are equal, or nearly equal. Near equality
* 			is when the radians between the two vectors is less than EPSILON and
* 			the difference between the lengths is less than EPSILON.
* @param	v1	The first vector.
* @param	v2	The second vector.
* @return	true iff v1 == v2.
*/

bool approximateVectorEquality(const dvec3 &v1, const dvec3 &v2) {
	return radsBetween(v1, v2) < EPSILON && approximatelyEqual(glm::length(v1), glm::length(v2));
}


/**
* @fn	string extractBaseFilename(const string &str)
* @brief	Extracts the base filename described by str
* @param	str	The string.
* @return	The extracted base filename.
* @test	extractBaseFileName("/usr/etc/hosts.txt") --> "hosts.txt"
*/

string extractBaseFilename(const string &str) {
#ifdef WINDOWS
	size_t pos = str.rfind('\\');
#else
	size_t pos = str.rfind('/');
#endif
	return str.substr(pos + 1);
}

bool DEBUG_PIXEL = false;
int xDebug = -1, yDebug = -1;

void mouseUtility(int b, int s, int x, int y) {
	if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN) {
		xDebug = x;
		yDebug = glutGet(GLUT_WINDOW_HEIGHT) - y - 1;
		cout << "(" << xDebug << "," << yDebug << ") = " << endl;
	}
}

void graphicsInit(int argc, char *argv [], const std::string &windowName) {
#ifndef WINDOWS
	setenv("DISPLAY", ":0.0", 1);
#endif
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	std::string title = username + std::string(" -- ") + extractBaseFilename(windowName);
    glutCreateWindow(title.c_str());
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
}
