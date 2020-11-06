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
#include "FrameBuffer.h"
#include "Light.h"
#include "VertexData.h"
#include "IScene.h"
#include "Rasterization.h"

/**
 * @class	VertexOps
 * @brief	Class to encapsulate the methods related to vertex processing for Pipeline graphics.
 */

class VertexOps {
public:
	static bool renderBackFaces;	//!< Typically false for closed body objects (e.g., sphere).
	static dmat4 modelingTrans;		//!< Used to orient/scale/position objects. Changed often.
	static dmat4 viewingTrans;		//!< Orient/position camera.
	static dmat4 projectionTrans;	//!< Define projection. Typically set just once.
	static dmat4 viewportTrans;		//!< Controls where NDCs map onto window.

	static const BoundingBox3D ndc;		//!< normalized device coordinate; the limits

	static vector<IPlane> allButNearNDCPlanes;		//!< 5 of the 6 planes of the 2x2x2 cube.

	static void processTriangleVertices(FrameBuffer &frameBuffer, const dvec3 &eyePos,
										const vector<LightSourcePtr> &lights,
										const vector<VertexData> &objectCoords);
	static void processTriangleVertices(FrameBuffer &frameBuffer,
										const vector<LightSourcePtr> &lights,
										const dmat4 &TM,
										const vector<VertexData> &objectCoords);
	static void processLineSegments(FrameBuffer &frameBuffer, const dvec3 &eyePos,
									const vector<LightSourcePtr> &lights,
									const vector<VertexData> &objectCoords);
	static void render(FrameBuffer &frameBuffer, const vector<VertexData> &verts,
								const vector<LightSourcePtr> &lights,
								const dmat4 &TM);
	static void setViewport(int left, int right, int bottom, int top);
	static void setViewport(const BoundingBoxi &vp);
	static BoundingBoxi viewport;			//!< the currently active viewport
protected:
	static void setViewportTransformation();
	static vector<VertexData> clipAgainstPlane(vector<VertexData> &verts, const IPlane &plane);
	static vector<VertexData> clipPolygon(const vector<VertexData> &clipCoords,
											const vector<IPlane> &planes);
	static vector<VertexData> clipLineSegments(const vector<VertexData> &clipCoords,
												const vector<IPlane> &planes);
	static vector<VertexData> processBackwardFacingTriangles(const vector<VertexData> &triangleVerts);
	static vector<VertexData> transformVerticesToWorldCoordinates(const dmat4 &modelMatrix, const vector<VertexData> &vertices);
	static vector<VertexData> transformVertices(const dmat4 &TM, const vector<VertexData> &vertices);
};