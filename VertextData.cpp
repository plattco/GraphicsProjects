/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "VertexData.h"
#include "Utilities.h"

/**
 * @fn	VertexData::VertexData(const dvec4 &pos, const dvec3 &norm, const Material &mat, const dvec3 &worldPos) : position(pos), normal(glm::normalize(norm)), material(mat), worldPosition(worldPos)
 * @brief	Constructor
 * @param	pos			Current coordinate.
 * @param	norm		Normal vector
 * @param	mat			Material
 * @param	worldPos	World position.
 */

VertexData::VertexData(const dvec4 &pos,
				const dvec3 &norm,
				const Material &mat,
				const dvec3 &worldPos) :
	pos(pos), normal(glm::normalize(norm)), material(mat), worldPos(worldPos) {
}

/**
 * @fn	VertexData::VertexData(double w1, const VertexData &vd1, double w2, const VertexData &vd2)
 * @brief	Constructs object using weighted average of two VertexData objects.
 * @param	w1 	Weight #1.
 * @param	vd1	VertexData #1.
 * @param	w2 	Weight #2.
 * @param	vd2	VertexData #2.
 */

VertexData::VertexData(double w1, const VertexData &vd1,
					double w2, const VertexData &vd2)
					: pos(weightedAverage(w1, vd1.pos, w2, vd2.pos)),
						normal(weightedAverage(w1, vd1.normal, w2, vd2.normal)),
						material(weightedAverage(w1, vd1.material, w2, vd2.material)),
						worldPos(weightedAverage(w1, vd1.worldPos, w2, vd2.worldPos)) {
}

/**
 * @fn	void VertexData::addTriVertsAndComputeNormal(vector<VertexData> &verts, const dvec4 &V1, const dvec4 &V2, const dvec4 &V3, const dvec3 &n, const Material &mat)
 * @brief	Adds a triangle vertices, adding vertices to end of verts. Vertices are specified
 * 			in counterclockwise order.
 * @param [in,out]	verts	The vector of vertices.
 * @param 		  	V1   	The first vertice
 * @param 		  	V2   	The second vertice.
 * @param 		  	V3   	The third vertice.
 * @param 		  	n	 	Normal vector.
 * @param 		  	mat  	The matrix.
 */

void VertexData::addTriVertsAndNormal(vector<VertexData> &verts,
											const dvec4 &V1,
											const dvec4 &V2,
											const dvec4 &V3,
											const dvec3 &n,
											const Material &mat) {
	verts.push_back(VertexData(V1, n, mat));
	verts.push_back(VertexData(V2, n, mat));
	verts.push_back(VertexData(V3, n, mat));
}

/**
 * @fn	void VertexData::addTriVertsAndComputeNormal(vector<VertexData> &verts, const dvec4 &V1, const dvec4 &V2, const dvec4 &V3, const Material &mat)
 * @brief	Adds a triangle vertices and computes normal, adding vertices to end of verts. Vertices are specified in counterclockwise order.
 * @param [in,out]	verts	The vector of vertices.
 * @param 		  	V1   	The first vertice
 * @param 		  	V2   	The second vertice.
 * @param 		  	V3   	The third vertice.
 * @param 		  	mat  	Material.
 */

void VertexData::addTriVertsAndComputeNormal(vector<VertexData> &verts,
											const dvec4 &V1,
											const dvec4 &V2,
											const dvec4 &V3,
											const Material &mat) {
	dvec3 n = normalFrom3Points(V1.xyz(), V2.xyz(), V3.xyz());
	verts.push_back(VertexData(V1, n, mat));
	verts.push_back(VertexData(V2, n, mat));
	verts.push_back(VertexData(V3, n, mat));
}

/**
 * @fn	void VertexData::addTriVertsAndComputeNormals(vector<VertexData> &verts, const vector<dvec4> &pts, const Material &mat)
 * @brief	Adds multiple triangles to triangle vertices
 * @param [in,out]	verts	The vector of vertices.
 * @param 		  	pts  	The new triangle vertices to be added.
 * @param 		  	mat  	Material.
 */

void VertexData::addTriVertsAndComputeNormals(vector<VertexData> &verts,
								const vector<dvec4> &pts,
								const Material &mat) {
	size_t numTris = pts.size() / 3;
	for (size_t i = 0; i < numTris; i++) {
		const dvec4 &V1 = pts[3 * i];
		const dvec4 &V2 = pts[3 * i + 1];
		const dvec4 &V3 = pts[3 * i + 2];
		addTriVertsAndComputeNormal(verts, V1, V2, V3, mat);
	}
}

/**
 * @fn	void VertexData::addConvexPolyVertsAndComputeNormals(vector<VertexData> &verts, const vector<dvec4> &polyCorners, const Material &mat)
 * @brief	Converts polygon into triangles vertices and adds them to vert.
 * @param [in,out]	verts	The vector of vertices.
 * @param 		  	polyCorners  	The polygon to be added.
 * @param 		  	mat  	Material.

 */

void VertexData::addConvexPolyVertsAndComputeNormals(vector<VertexData> &verts,
										const vector<dvec4> &polyCorners,
										const Material &mat) {
	size_t numTris = polyCorners.size() - 2;
	for (size_t i = 0; i < numTris; i++) {
		const dvec4 &V1 = polyCorners[0];
		const dvec4 &V2 = polyCorners[i + 1];
		const dvec4 &V3 = polyCorners[i + 2];
		addTriVertsAndComputeNormal(verts, V1, V2, V3, mat);
	}
}

/**
 * @fn	void VertexData::addConvexPolyVertsAndComputeNormals(vector<VertexData> &verts, const dvec4 &p1, const dvec4 &p2, const dvec4 &p3, const dvec4 &p4, const Material &mat)
 * @brief	Adds a convex quadrilateral.
 * @param [in,out]	verts	The vertices.
 * @param 		  	p1   	The first vertex.
 * @param 		  	p2   	The second vertex.
 * @param 		  	p3   	The third vertex.
 * @param 		  	p4   	The fourth vertex.
 * @param 		  	mat  	The matrix.
 */

void VertexData::addConvexPolyVertsAndComputeNormals(vector<VertexData> &verts,
										const dvec4 &p1,
										const dvec4 &p2,
										const dvec4 &p3,
										const dvec4 &p4,
										const Material &mat) {
	addConvexPolyVertsAndComputeNormals(verts, vector<dvec4>({ p1, p2, p3, p4 }), mat);
}

/**
 * @fn	VertexData operator* (double w, const VertexData &data)
 * @brief	Multiplication operator for VertexData objects
 * @param	w   	The scalar multiplier.
 * @param	data	Vertex data to scale.
 * @return	The scaled Vertex data.
 */

VertexData operator * (double w, const VertexData &data) {
	VertexData result(w*data.pos, w*data.normal, w*data.material, w*data.worldPos);
	return result;
}

/**
 * @fn	VertexData VertexData::operator+ (const VertexData &other) const
 * @brief	Addition operator for VertexData objects
 * @param	other	The 2nd VertexData object.
 * @return	The raw summation of the two VertexData objects
 */

VertexData VertexData::operator + (const VertexData &other) const {
	VertexData result(*this);
	result.material += other.material;
	result.normal += other.normal;
	result.pos += other.pos;
	result.worldPos += other.worldPos;
	return result;
}
