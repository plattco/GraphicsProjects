/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "Defs.h"
#include "VertexOps.h"

// Pipeline transformation matrices
dmat4 VertexOps::modelingTrans;
dmat4 VertexOps::viewingTrans;
dmat4 VertexOps::projectionTrans;
dmat4 VertexOps::viewportTrans;
bool VertexOps::renderBackFaces = true;

const BoundingBox3D VertexOps::ndc(-1, 1, -1, 1, -1, 1);	//l,r,b,t,n,f
BoundingBoxi VertexOps::viewport(0, WINDOW_WIDTH - 1, 0, WINDOW_HEIGHT - 1);

// Planes describing the normalized device coordinates view volume - 2x2x2 cube

vector<IPlane> VertexOps::allButNearNDCPlanes{ IPlane(dvec3(1, 0, 0), dvec3(-1, 0, 0)),
												IPlane(dvec3(0, 1, 0), dvec3(0, -1, 0)),
												IPlane(dvec3(0, 0, 1), dvec3(0, 0, -1)),
												IPlane(dvec3(-1, 0, 0), dvec3(1, 0, 0)),
												IPlane(dvec3(0, -1, 0), dvec3(0, 1, 0)),
//												IPlane(dvec3(0, 0, -1), dvec3(0, 0, 1))
										};

/**
 * @fn	vector<VertexData> triangulate(const vector<VertexData> &poly)
 * @brief	Triangulates the given polygon
 * @param	poly	The polygon to be decomposed into individual triangles.
 * @return	A vector of triangles, which comprise the original polygon.
 */

vector<VertexData> triangulate(const vector<VertexData> &poly) {
	vector<VertexData> triangles;

	for (unsigned int i = 1; i < poly.size() - 1; i++) {
		triangles.push_back(poly[0]);
		triangles.push_back(poly[i]);
		triangles.push_back(poly[i + 1]);
	}

	return triangles;
}

/**
 * @fn	vector<VertexData> VertexOps::clipAgainstPlane(vector<VertexData> &verts, const IPlane &plane)
 * @brief	Clips a polygon against a single plane
 * @param [in,out]	verts	The array of vertices.
 * @param 		  	plane	The plane that will do the clipping.
 * @return	The polygon that exludes the portions outside the given plane.
 */

vector<VertexData> VertexOps::clipAgainstPlane(vector<VertexData> &verts, const IPlane &plane) {
	vector<VertexData> output;

	if (verts.size() > 2) {
		verts.push_back(verts[0]);

		for (unsigned int i = 1; i < verts.size(); i++) {
			bool v0In = plane.onFrontSide(verts[i - 1].pos.xyz());
			bool v1In = plane.onFrontSide(verts[i].pos.xyz());

			if (v0In && v1In) {
				output.push_back(verts[i]);
			} else if (v0In || v1In) {
				double t;
				plane.findIntersection(verts[i - 1].pos.xyz(), verts[i].pos.xyz(), t);
				VertexData I(1.0 - t, verts[i - 1], t, verts[i]);
				output.push_back(I);
				if (!v0In && v1In) {
					output.push_back(verts[i]);
				}
			}
		}
	}
	return output;
}

/**
 * @fn	vector<VertexData> VertexOps::clipPolygon(const vector<VertexData> &clipCoords)
 * @brief	Clip polygon against the normalized view volumn - 2x2x2 cube.
 * @param	clipCoords	The array of triangles.
 * @param	planes		Planes to clip against
 * @return	The array of triangles, after performing clipping.
 */

vector<VertexData> VertexOps::clipPolygon(const vector<VertexData> &clipCoords,
											const vector<IPlane> &planes) {
	vector<VertexData> ndcCoords;

	if (clipCoords.size() > 2) {
		for (unsigned int i = 0; i < clipCoords.size() - 2; i += 3) {
			vector<VertexData> polygon;
			polygon.push_back(clipCoords[i]);
			polygon.push_back(clipCoords[i + 1]);
			polygon.push_back(clipCoords[i + 2]);

			for (IPlane plane : planes) {
				polygon = clipAgainstPlane(polygon, plane);
			}
			if (polygon.size() > 3) {
				polygon = triangulate(polygon);
			}
			for (VertexData v : polygon) {
				ndcCoords.push_back(v);
			}
		}
	}
	return ndcCoords;
}

/**
 * @fn	vector<VertexData> VertexOps::clipLineSegments(const vector<VertexData> &clipCoords)
 * @brief	Clip line segments against normalized view volume.
 * @param	clipCoords	The vector of line segments that are to be clipped.
 * @param	planes	planes to clip against
 * @return	A vector&lt;VertexData&gt;
 */

vector<VertexData> VertexOps::clipLineSegments(const vector<VertexData> &clipCoords,
											const vector<IPlane> &planes) {
	vector<VertexData> ndcCoords;

	if (clipCoords.size() > 1) {
		for (unsigned int i = 0; i < clipCoords.size() - 1; i += 2) {
			VertexData v0 = clipCoords[i];
			VertexData v1 = clipCoords[i + 1];

			bool outsideViewVolume = false;

			for (const IPlane &plane : planes) {
				bool v0In = plane.onFrontSide(v0.pos.xyz());
				bool v1In = plane.onFrontSide(v1.pos.xyz());

				if (!v0In && !v1In) { // Line segment is entirely clipped
					outsideViewVolume = true;
					break; 
				} else if (v0In && !v1In) {
					double t;
					plane.findIntersection(v0.pos.xyz(), v1.pos.xyz(), t);
					v1 = VertexData(1.0-t, v0, t, v1);
				} else if (!v0In && v1In) {
					double t;
					plane.findIntersection(v0.pos.xyz(), v1.pos.xyz(), t);
					v0 = VertexData(1.0-t, v0, t, v1);
				} else {  // both inside
					;
				}
			}
			if (!outsideViewVolume) {
				ndcCoords.push_back(v0);
				ndcCoords.push_back(v1);
			}
		}
	}
	return ndcCoords;
}

 /**
 * @fn	vector<VertexData> VertexOps::processBackwardFacingTriangles(const vector<VertexData> &triangleVerts)
 * @brief	Removes the backward facing triangles
 * @param	triangleVerts	The vector of triangle vertices.
 * @return	Vector of triangle vertices, without those facing backward.
 */

vector<VertexData> VertexOps::processBackwardFacingTriangles(const vector<VertexData> &triangleVerts) {
	/* CSE 386 - todo  */
	vector<VertexData> triangles;
	triangles = triangleVerts;
	return triangles;
}

/**
 * @fn	vector<VertexData> VertexOps::transformVerticesToWorldCoordinates(const dmat4 &modelMatrix, const vector<VertexData> &vertices)
 * @brief	Apply modeling transformation to vector of vertices.
 * @param	modelMatrix	Modeling matrix.
 * @param	vertices   	The vector of vertices.
 * @return	The transformed vertices.
 */

vector<VertexData> VertexOps::transformVerticesToWorldCoordinates(const dmat4 &modelMatrix, const vector<VertexData> &vertices) {
	// Create 3 x 3 matrix for transforming normal vectors to world coordinates
	dmat3 TM3x3(modelMatrix);
	dmat3 modelingTransfomationForNormals = glm::transpose(glm::inverse(TM3x3));

	vector<VertexData> transformedVertices;
	for (unsigned int i=0; i<vertices.size(); i++) {
		const VertexData &v = vertices[i];
		dvec3 n = modelingTransfomationForNormals * v.normal;
		dvec4 worldPos = modelMatrix * v.pos;
		VertexData vt(worldPos, n, v.material, worldPos.xyz());
		transformedVertices.push_back(vt);
	}
	return transformedVertices;
}

/**
 * @fn	vector<VertexData> VertexOps::transformVertices(const dmat4 &TM, const vector<VertexData> & vertices)
 * @brief	Applies a transformation matrix to a vector of vertices. Does not change the worldPosition; copies it over.
 * @param	TM			The transformation matrix.
 * @param	vertices   	The vertices.
 * @return	The transformed vector of vertices.
 */

vector<VertexData> VertexOps::transformVertices(const dmat4 &TM, const vector<VertexData> & vertices) {
	vector<VertexData> transformedVertices;

	for (VertexData v : vertices) {
		VertexData vt(TM * v.pos, v.normal, v.material);
		// Save the world position separately for use in per pixel lighting calculations
		vt.worldPos = v.worldPos;

		transformedVertices.push_back(vt);
	}
	return transformedVertices;
}

double computeNearPlane(const dmat4 &PM) {
	double alpha = PM[2][2];
	double beta = PM[3][2];
	double gamma = PM[2][3];
	double omega = PM[3][3];
	double nearf = -(omega + beta) / (alpha + gamma);
	return nearf;
}

/**
 * @fn	void VertexOps::processTriangleVertices(FrameBuffer &frameBuffer, const dvec3 &eyePos, const vector<LightSourcePtr> &lights, const vector<VertexData> &objectCoords)
 * @brief	Transforms the triangle vertices through pipeline: object -> world -> eye -> clip/ndc -> window.
 * @param [in,out]	frameBuffer 	Buffer for frame data.
 * @param 		  	eyePos			The eye position.
 * @param 		  	lights			The lights.
 * @param 		  	objectCoords	The object coordinates.
 */

void VertexOps::processTriangleVertices(FrameBuffer &frameBuffer, const dvec3 &eyePos,
										const vector<LightSourcePtr> &lights,
										const vector<VertexData> &objectCoords) {
	vector<VertexData> worldCoords = transformVerticesToWorldCoordinates(modelingTrans, objectCoords);
	vector<VertexData> eyeCoords = transformVertices(viewingTrans, worldCoords);

	double nearZ = computeNearPlane(VertexOps::projectionTrans);
	vector <IPlane> nearPlane = { IPlane(dvec4(0.0, 0.0, nearZ, 1.0), -Z_AXIS) };
	vector<VertexData> eyeCoordsClippedOnNearPlane = clipPolygon(eyeCoords, nearPlane);

	vector<VertexData> projCoords = transformVertices(projectionTrans, eyeCoordsClippedOnNearPlane);
	vector<VertexData> clipCoords;

	for (VertexData v : projCoords) {		// Perspective division
		if (v.pos.w >= 0) {
			v.pos /= v.pos.w;
		} else {							// should not happen
			v.pos.x /= -v.pos.w;
			v.pos.y /= -v.pos.w;
			v.pos.z = -std::abs(v.pos.z/-v.pos.w);
			v.pos.w = 1.0;
		}
		clipCoords.push_back(v);
	}

	clipCoords = processBackwardFacingTriangles(clipCoords);	

	vector<VertexData> ndcCoords = clipPolygon(clipCoords, allButNearNDCPlanes);
	vector<VertexData> windowCoords = transformVertices(viewportTrans, ndcCoords);

	for (VertexData &vd : windowCoords) {
		vd.pos.x = glm::clamp(vd.pos.x, (double)viewport.lx, (double)viewport.rx);
		vd.pos.y = glm::clamp(vd.pos.y, (double)viewport.ly, (double)viewport.ry);
	}

	drawManyFilledTriangles(frameBuffer, eyePos, lights, windowCoords, viewingTrans);
}

/**
 * @fn	void VertexOps::processTriangleVertices(FrameBuffer &frameBuffer, const vector<LightSourcePtr> &lights, const dmat4 &TM, const vector<VertexData> &objectCoords)
 * @brief	Process the triangle vertices
 * @param [in,out]	frameBuffer 	Framebuffer.
 * @param 		  	lights			The lights in the scene.
 * @param 		  	TM				The modeling transformation matrix.
 * @param 		  	objectCoords	The vector of triangles in object coordinates.
 */

void VertexOps::processTriangleVertices(FrameBuffer &frameBuffer,
										const vector<LightSourcePtr> &lights,
										const dmat4 &TM,
										const vector<VertexData> &objectCoords) {
	dvec3 eyePos = glm::inverse(VertexOps::viewingTrans)[3].xyz();
	VertexOps::modelingTrans = TM;
	processTriangleVertices(frameBuffer, eyePos, lights, objectCoords);
}

/**
 * @fn	void VertexOps::processLineSegments(FrameBuffer &frameBuffer, const dvec3 &eyePos, const vector<LightSourcePtr> &lights, const vector<VertexData> &objectCoords)
 * @brief	Process the line segments through the pipeline.
 * @param [in,out]	frameBuffer 	Frame buffer
 * @param 		  	eyePos			Eye position.
 * @param 		  	lights			The lights in the scene.
 * @param 		  	objectCoords	The vector of object coordinates.
 */

void VertexOps::processLineSegments(FrameBuffer &frameBuffer, const dvec3 &eyePos,
									const vector<LightSourcePtr> &lights,
									const vector<VertexData> &objectCoords) {
	vector<VertexData> worldCoords = transformVerticesToWorldCoordinates(modelingTrans, objectCoords);

	vector<VertexData> eyeCoords = transformVertices(viewingTrans, worldCoords);
	vector<VertexData> projCoords = transformVertices(projectionTrans, eyeCoords);
	vector<VertexData> clipCoords;

	for (VertexData v : projCoords) {	// Perspective division
		if (v.pos.w >= 0)
			v.pos /= v.pos.w;
		else {							// this should not happen
			v.pos /= -v.pos.w;
			v.pos.z = -std::abs(v.pos.z);
		}
		clipCoords.push_back(v);
	}

	vector<VertexData> ndcCoords = clipLineSegments(clipCoords, allButNearNDCPlanes);
	vector<VertexData> windowCoords = transformVertices(viewportTrans, ndcCoords);
	drawManyLines(frameBuffer, eyePos, lights, windowCoords, viewingTrans);
}

/**
 * @fn	void VertexOps::render(FrameBuffer &frameBuffer, const vector<VertexData> &verts, const vector<LightSourcePtr> &lights, const dmat4 &TM)
 * @brief	Renders this object
 * @param [in,out]	frameBuffer	Buffer for frame data.
 * @param 		  	verts	   	The vertices.
 * @param 		  	lights	   	The lights.
 * @param 		  	TM		   	The time.
 */

void VertexOps::render(FrameBuffer &frameBuffer, const vector<VertexData> &verts,
							const vector<LightSourcePtr> &lights,
							const dmat4 &TM) {
	dvec3 eyePos = glm::inverse(VertexOps::viewingTrans)[3].xyz();
	VertexOps::modelingTrans = TM;
	VertexOps::processTriangleVertices(frameBuffer, eyePos, lights, verts);
}

/**
 * @fn	void VertexOps::setViewport(int left, int right, int bottom, int top)
 * @brief	Sets a viewport to a particular setting.
 * @param	left  	left edge
 * @param	right 	right edge
 * @param	bottom	bottom edge
 * @param	top     top edge
 */

void VertexOps::setViewport(int left, int right, int bottom, int top) {
	setViewport(BoundingBoxi(left, right, bottom, top));
}

/**
 * @fn	void VertexOps::setViewport(const BoundingBoxi &vp)
 * @brief	Sets a viewport to a particlar setting
 * @param	vp	The new viewport settings
 */

void VertexOps::setViewport(const BoundingBoxi &vp) {
	viewport = vp;
	setViewportTransformation();
}

/**
 * @fn	void VertexOps::setViewportTransformation()
 * @brief	Sets viewport transformation based on the current viewport settings.
 */

void VertexOps::setViewportTransformation() {
	/* CSE386 - todo */
	VertexOps::viewportTrans = T((double)VertexOps::viewport.lx,
											(double)VertexOps::viewport.ly, 0.0) *
		S((double)VertexOps::viewport.width() / VertexOps::ndc.width(),
			(double)VertexOps::viewport.height() / VertexOps::ndc.height(), 1.0) *
		T(-VertexOps::ndc.lx, -VertexOps::ndc.ly, 0.0);
}
