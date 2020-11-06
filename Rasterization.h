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
#include "FragmentOps.h"
#include "VertexData.h"

void drawAxisOnWindow(FrameBuffer &frameBuffer);
void drawWirePolygon(FrameBuffer &frameBuffer, const vector<dvec3> &pts, const color &rgb);
void drawLine(FrameBuffer &frameBuffer, int x1, int y1, int x2, int y2, const color &C);
void drawLine(FrameBuffer &frameBuffer, const dvec2 &pt1, const dvec2 &pt2, const color &C);
void drawLine(FrameBuffer &frameBuffer, const dvec3 &eyePos,
					vector<LightSourcePtr> &lights, 
					const VertexData &v0, const VertexData &v1,
					const dmat4 &viewingMatrix);
void drawManyLines(FrameBuffer &frameBuffer, const dvec3 &eyePos,
					const vector<LightSourcePtr> &lights, const vector<VertexData> &vertices,
					const dmat4 &viewingMatrix);
void drawWireFrameTriangle(FrameBuffer &frameBuffer, const dvec3 &eyePos,
							const vector<LightSourcePtr> &lights, const VertexData &v0, const VertexData &v1, const VertexData &v2,
							const dmat4 &viewingMatrix);
void drawFilledTriangle(FrameBuffer &frameBuffer, const dvec3 &eyePos, vector<LightSourcePtr> &lights, const VertexData &v0,
						const VertexData &v1, const VertexData &v2,
						const dmat4 &viewingMatrix);
void drawManyWireFrameTriangles(FrameBuffer &frameBuffer, const dvec3 &eyePos, 
								const vector<LightSourcePtr> &lights, const vector<VertexData> &vertices,
								const dmat4 &viewingMatrix);
void drawManyFilledTriangles(FrameBuffer &frameBuffer, const dvec3 &eyePos,
							const vector<LightSourcePtr> &lights, const vector<VertexData> &vertices,
							const dmat4 &viewingMatrix);
void drawArc(FrameBuffer &fb, const dvec2 &center, double R,
				double startRads, double lengthInRads, const color &rgb);