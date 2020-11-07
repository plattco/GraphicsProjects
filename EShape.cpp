/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "EShape.h"

/**
 * @fn	EShapeData EShape::createEDisk(const Material &mat, double radius, int slices)
 * @brief	Creates a disk.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	slices	Number of slices.
 * @return	The new disk.
 */

EShapeData EShape::createEDisk(const Material &mat, double radius, int slices) {
	/* CSE 386 - todo  */
	EShapeData result;

	double angleInc = TWO_PI / SLICES;

	for (int i = 0; i < SLICES; i++) {
		double A1 = i * angleInc;
		double A2 = A1 + angleInc;
		dvec4 A(0.0, 0.0, 0.0, 1.0);
		dvec4 B(glm::cos(A1), glm::sin(A1), 0.0, 1.0);
		dvec4 C(glm::cos(A2), glm::sin(A2), 0.0, 1.0);
		VertexData::addTriVertsAndComputeNormal(result, A, B, C, mat);
	}

	return result;
}

/**
 * @fn	EShapeData EShape::createESphere(const Material &mat, double R, int slices)
 * @brief	Creates sphere.
 * @param	mat   	Material.
 * @param	R   	Radius.
 * @param	slices	Slices.
 * @return	The new sphere.
 */

EShapeData EShape::createESphere(const Material &mat, double R, int slices) {
	/* CSE 386 - todo  */
	EShapeData result;
	dvec4 A(0, 0, 0, 1);
	dvec4 B(1, 0, 0, 1);
	dvec4 C(1, 1, 0, 1);
	result = EShape::createETriangle(mat, A, B, C);
	return result;
}

/**
 * @fn	EShapeData EShape::createECylinder(const Material &mat, double R, double height, int slices)
 * @brief	Creates cylinder, which is centered on (0,0,0) and aligned with y axis.
 * @param	mat   	Material.
 * @param	R   	Radius.
 * @param	height	Height.
 * @param	slices	Slices.
 * @return	The new cylinder.
 */

EShapeData EShape::createECylinder(const Material &mat, double R, double height, int slices) {
	/* CSE 386 - todo  */
	// similarly to the cone I need to loop through and build (planes? rectangles) one by one in different spots
	// depending on the paramets until the correct cylinder is built.
	// I need to move it to the right place by using rotation and transposition
	EShapeData result;
	dvec4 A(0, 0, 0, 1);
	dvec4 B(1, 1, 1, 1);
	dvec4 C(1, 0, -1, 1);
	result = EShape::createETriangle(mat, A, B, C);
	return result;
}

/**
 * @fn	EShapeData EShape::createECone(const Material &mat, double R, double height, int slices)
 * @brief	Creates cone, which is aligned with y axis.
 * @param	mat   	Material.
 * @param	R   	Radius.
 * @param	height	Height.
 * @param	slices	Slices.
 * @return	The new cone.
 */

EShapeData EShape::createECone(const Material &mat, double R, double height, int slices) {
	/* CSE 386 - todo  */
	// I need to somehow cycle through this in a way that builds a cone piece by piece. I think that I need to loop through and 
	// create a triangle to tack onto the correct place for each iteration until it is built.
	// I need to find out how and where to place the trangles, probably by using R and height.
	// It seems that mat is taken care of since it is applied to the triangle. 
	// Do I need to incorporate R and height into the dvecs below or into the actual building of the cone? probably the triangle.

	EShapeData result;
	dvec4 A(0, 0, 0, 1);
	dvec4 B(1, 0, 0, 1);
	dvec4 C(1, 1, 0, 1);
	result = EShape::createETriangle(mat, A, B, C);
	for(int i = 0; i < slices; i++){
		// find the correct place to place a triangle
		// make sure base of cone is centered on origin and axis is aligned with y
		// I need to move it to the right place by using rotation and transposition
		result = EShape::createETriangle(mat, A, B, C); // create triangle while changing the appropriate attributes.
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createECube(const Material &mat, double width, double height, double depth)
 * @brief	Creates cube
 * @param	mat   	Material.
 * @param	width 	Width.
 * @param	height	Height.
 * @param	depth 	Depth.
 * @return	The new cube.
 */

EShapeData EShape::createECube(const Material &mat, double width, double height, double depth) {
	EShapeData result;
	return result;
}

/**
 * @fn	EShapeData EShape::createETriangles(const Material &mat, const vector<dvec4> &V)
 * @brief	Creates triangles from 3i vertices
 * @param	mat	Material.
 * @param	V  	Vector of objects to process.
 * @return	The new triangles.
 */

EShapeData EShape::createETriangles(const Material &mat, const vector<dvec4> &V) {
	EShapeData result;
	size_t numTris = V.size() / 3;
	for (size_t i = 0; i < numTris; i++) {
		size_t start = 3 * i;
		const dvec4 &A = V[start];
		const dvec4 &B = V[start + 1];
		const dvec4 &C = V[start + 2];
		VertexData::addTriVertsAndComputeNormal(result, A, B, C, mat);
	}
	return result;
}


/**
 * @fn	EShapeData EShape::createETriangle(const Material &mat, const dvec4& A, const dvec4& B, const dvec4& C)
 * @brief	Creates one triangles from 3 vertices
 * @param	mat	Material.
 * @param	A  	First vertex.
 * @param	B  	Second vertex.
 * @param	C  	Third vertex.
 * @return	The new triangles.
 */

EShapeData EShape::createETriangle(const Material& mat,
	const dvec4& A, const dvec4& B, const dvec4& C) {
	EShapeData result;
	VertexData::addTriVertsAndComputeNormal(result, A, B, C, mat);
	return result;
}


/**
 * @fn	EShapeData EShape::createEPlanes(const Material &mat, const vector<dvec4> &V)
 * @brief	Creates planes, which are defined by 4 corners.
 * @param	mat	Material.
 * @param	V  	Vector of points to process.
 * @return	The new planes.
 */

EShapeData EShape::createEPlanes(const Material &mat, const vector<dvec4> &V) {
	EShapeData result;
	size_t numPlanes = V.size() / 4;
	for (size_t i = 0; i < numPlanes; i++) {
		size_t start = 4 * i;
		const dvec4 &A = V[start];
		const dvec4 &B = V[start + 1];
		const dvec4 &C = V[start + 2];
		const dvec4 &D = V[start + 3];
		VertexData::addConvexPolyVertsAndComputeNormals(result, A, B, C, D, mat);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createELines(const Material &mat, const vector<dvec4> &V)
 * @brief	Creates lines
 * @param	mat	Material.
 * @param	V  	A vector of point-pairs.
 * @return	The new lines.
 */

EShapeData EShape::createELines(const Material &mat, const vector<dvec4> &V) {
	EShapeData result;
	for (size_t i = 0; i < V.size(); i++) {
		result.push_back(VertexData(V[i], ZEROVEC, mat));
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createECheckerBoard(const Material &mat1, const Material &mat2, double WIDTH, double HEIGHT, int DIV)
 * @brief	Creates checker board pattern.
 * @param	mat1  	Material #1.
 * @param	mat2  	Material #2.
 * @param	WIDTH 	Width of overall plane.
 * @param	HEIGHT	Height of overall plane.
 * @param	DIV   	Number of divisions.
 * @return	The vertices in the checker board.
 */

EShapeData EShape::createECheckerBoard(const Material &mat1, const Material &mat2, double WIDTH, double HEIGHT, int DIV) {
	EShapeData result;

	const double INC = WIDTH / DIV;
	for (int X = 0; X < DIV; X++) {
		bool isMat1 = X % 2 == 0;
		for (double Z = 0; Z < DIV; Z++) {
			dvec4 V0(-WIDTH / 2.0 + X*INC, 0.0, -WIDTH / 2 + Z*INC, 1.0);
			dvec4 V1 = V0 + dvec4(0.0, 0.0, INC, 0.0);
			dvec4 V2 = V0 + dvec4(INC, 0.0, INC, 0.0);
			dvec4 V3 = V0 + dvec4(INC, 0.0, 0.0, 0.0);
			const Material &mat = isMat1 ? mat1 : mat2;

			result.push_back(VertexData(V0, Y_AXIS, mat));
			result.push_back(VertexData(V1, Y_AXIS, mat));
			result.push_back(VertexData(V2, Y_AXIS, mat));

			result.push_back(VertexData(V2, Y_AXIS, mat));
			result.push_back(VertexData(V3, Y_AXIS, mat));
			result.push_back(VertexData(V0, Y_AXIS, mat));
			isMat1 = !isMat1;
		}
	}
	return result;
}
