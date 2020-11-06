/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#pragma once

#include <utility>
#include "VertexData.h"
#include "FrameBuffer.h"
#include "Light.h"

typedef vector<VertexData> EShapeData;

/**
 * @struct	EShape
 * @brief	This class contains functions that create explicitly represented shapes.
 * 			This class is used within pipeline applications. The objects returned by
 * 			these routines are vectors of VertexData, where each successive triplet
 * 			is a triangle.
 */

struct EShape {
	static EShapeData createEPlanes(const Material& mat, const vector<dvec4>& corners);
	static EShapeData createETriangles(const Material& mat, const vector<dvec4>& pts);
	static EShapeData createETriangle(const Material& mat,
									const dvec4& A, const dvec4& B, const dvec4& C);
	static EShapeData createEDisk(const Material& mat, double radius = 1.0, int slices = SLICES);
	static EShapeData createECylinder(const Material& mat, double R = 1.0, double height = 1.0, int slices = SLICES);
	static EShapeData createESphere(const Material& mat, double radius = 1.0, int slices = SLICES);
	static EShapeData createECone(const Material& mat, double radius = 1.0, double height = 1.0, int slices = SLICES);
	static EShapeData createECheckerBoard(const Material& mat1, const Material& mat2, double WIDTH, double HEIGHT, int DIV);
	static EShapeData createELines(const Material& mat, const vector<dvec4>& corners);

	/* CSE 386 - To create */
	static EShapeData createECube(const Material &mat, double width = 1.0, double height = 1.0, double depth = 1.0);
};
