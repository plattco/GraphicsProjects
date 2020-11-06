/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include <vector>
#include "IShape.h"

/**
 * @fn	IShape::IShape()
 * @brief	Constructs a default IShape, centered at the origin.
 */

IShape::IShape() {
}

/**
 * @fn	void IShape::getTexCoords(const dvec3 &pt, double &u, double &v) const
 * @brief	Computes the tex coordinate of a point on the surface. The default
 * 			return value is (0, 0)
 * @param 		  	pt	The coordinate to process
 * @param [in,out]	u 	The u, in (u, v).
 * @param [in,out]	v 	The v, in (u, v).
 */

void IShape::getTexCoords(const dvec3 &pt, double &u, double &v) const {
	u = v = 0;
}

/**
 * @fn	dvec3 IShape::movePointOffSurface(const dvec3 &pt, const dvec3 &n)
 * @brief	Compute point that is slightly off surface.
 * @param	pt	Intersection point.
 * @param	n 	Normal vector at pt.
 * @return	The point that is approximately EPSILON off the surface.
 */

dvec3 IShape::movePointOffSurface(const dvec3 &pt, const dvec3 &n) {
	/* CSE 386 - todo  */
	return pt;
}

/**
 * @fn	VisibleIShape::VisibleIShape(IShapePtr shapePtr, const Material &mat)
 * @brief	Represents an visible, implicit shape.
 * @param	shapePtr	Pointer to the implicit shape.
 * @param	mat			Material
 */

VisibleIShape::VisibleIShape(IShapePtr shapePtr, const Material &mat)
	: material(mat), shape(shapePtr) {
	texture = nullptr;
}

/**
 * @fn	void VisibleIShape::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Identifies the closest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit that repesents the closest "hit".
 */

void VisibleIShape::findClosestIntersection(const Ray &ray, HitRecord &hit) const {
	shape->findClosestIntersection(ray, hit);
	if (hit.t < FLT_MAX) {
		hit.material = material;
		hit.texture = texture;
		if (hit.texture != nullptr) {
			shape->getTexCoords(hit.interceptPt, hit.u, hit.v);
		}
	}
}

/**
 * @fn	void VisibleIShape::setTexture(Image *tex)
 * @brief	Sets a texture for this implicit shape.
 * @param [in,out]	tex	The image to use as the texture, if not null.
 */

void VisibleIShape::setTexture(Image *tex) {
	texture = tex;
}

/**
 * @fn	HitRecord VisibleIShape::findIntersection(const Ray &ray, const vector<VisibleIShapePtr> &surfaces)
 * @brief	Searches for the first intersection
 * @param	ray			The ray.
 * @param	surfaces	The surfaces in the scene.
 * @return	The closest intersection that is in front of the camera.
 */

HitRecord VisibleIShape::findIntersection(const Ray &ray, const vector<VisibleIShapePtr> &surfaces) {
	/* CSE 386 - todo  */
	HitRecord theHit;
	for (int i = 0; i < surfaces.size(); i++) {
		HitRecord thisHit;
		VisibleIShape& thisSurface = *surfaces[i];
		thisSurface.findClosestIntersection(ray, thisHit);
		if (thisHit.t < theHit.t) {
			theHit = thisHit;
		}
	}
	return theHit;
}

/**
 * @fn	IDisk::IDisk()
 * @brief	Implicit representation of an implicit disk. Create a unit circle, centered
 *          on the origin, and lying on the x-y plane.
 */

IDisk::IDisk()
	: IShape(), center(ORIGIN3D), n(Y_AXIS), radius(1.0) {
}

/**
 * @fn	IDisk::IDisk(const dvec3 &pos, const dvec3 &normal, double rad)
 * @brief	Implicit representation of an implicit disk.
 * @param	pos   	Center of disk.
 * @param	normal	Normal vector of disk.
 * @param	rad   	Radius of disk.
 */

IDisk::IDisk(const dvec3 &pos, const dvec3 &normal, double rad)
	: IShape(), center(pos), n(normal), radius(rad) {
}

void IDisk::getTexCoords(const dvec3& pt, double& u, double& v) const {

	// Assume disk lies parallel to xy plane
	map(pt.x, center.x - radius, center.x + radius, 0.0, 1.0, u);
	map(pt.y, center.y - radius, center.y + radius, 0.0, 1.0, v);
	v = 1 - v;

}

/**
 * @fn	void IDisk::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Identifies the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IDisk::findClosestIntersection(const Ray &ray, HitRecord &hit) const {
	/* CSE 386 - todo  */
	IPlane plane(center, n);
	plane.findClosestIntersection(ray, hit);
	if (hit.t != FLT_MAX && glm::distance(center, hit.interceptPt) > radius) {
		hit.t = FLT_MAX;
	}
}

/**
 * @fn	ISphere::ISphere(const dvec3 & position, double radius)
 * @brief	Implicit representation of a 3D sphere.
 * @param	position	The center of the sphere.
 * @param	radius  	The radius of the sphere.
 */

ISphere::ISphere(const dvec3 &position, double radius)
	: IQuadricSurface(QuadricParameters::sphereQParams(radius), position) {
}

/**
 * @fn	void ISphere::getTexCoords(const dvec3 &pt, double &u, double &v) const
 * @brief	Gets texture coordinates for a point on the surface.
 * @param 		  	pt	The point on the surface.
 * @param [in,out]	u 	The u in the (u, v) texture coordinates.
 * @param [in,out]	v 	The v in the (u, v) texture coordinates.
 */

void ISphere::getTexCoords(const dvec3 &pt, double &u, double &v) const {
	/* CSE 386 - todo  */
	u = v = 0;
}

/**
 * @fn	void ISphere::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const
 * @see textbook.
 * @brief	Calculates aq, bq, and cq that are used in the quadric equations. The 
 * 			values that are know to be zero are eliminated from the code.
 * @param 		  	ray	The ray.
 * @param [in,out]	Aq 	aq.
 * @param [in,out]	Bq 	bq.
 * @param [in,out]	Cq 	cq.
 */

void ISphere::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &D = qParams.D;
	const double &E = qParams.E;
	const double &F = qParams.F;
	const double &G = qParams.G;
	const double &H = qParams.H;
	const double &I = qParams.I;
	const double &J = qParams.J;

	dvec3 Ro = ray.origin - center;
	const dvec3 &Rd = ray.dir;

	Aq = /*A * */ (Rd.x*Rd.x) +
		/*B * */ (Rd.y*Rd.y) +
		/*C * */ (Rd.z*Rd.z);
		//D * (Rd.x * Rd.y) +
		//E * (Rd.x * Rd.z) +
		//F * (Rd.y * Rd.z);

	Bq = 2 * /* A * */ Ro.x*Rd.x +
		2 * /* B * */ Ro.y*Rd.y +
		2 * /* C * */ Ro.z*Rd.z;
		//D * (Ro.x * Rd.y + Ro.y * Rd.x) +
		//E * (Ro.x * Rd.z + Ro.z * Rd.x) +
		//F * (Ro.y * Rd.z + Ro.z * Rd.y) +
		//G * Rd.x + H * Rd.y + I * Rd.z;

	Cq = /* A * */ (Ro.x * Ro.x) +
		/* B * */ (Ro.y * Ro.y) +
		/* C * */ (Ro.z * Ro.z) +
		//D * (Ro.x * Ro.y) +
		//E * (Ro.x * Ro.z) +
		//F * (Ro.y * Ro.z) +
		//G * Ro.x +
		//H * Ro.y +
		I * Ro.z + J;
}

/**
 * @fn	QuadricParameters::QuadricParameters() : QuadricParameters(vector<double> {1, 1, 1, 0, 0, 0, 0, 0, 0, -1})
 * @brief	Default constructor
 */

QuadricParameters::QuadricParameters()
	: QuadricParameters(vector<double> {1, 1, 1, 0, 0, 0, 0, 0, 0, -1}) {
}

/**
 * @fn	QuadricParameters::QuadricParameters(const vector<double> &items)
 * @brief	Constructor using 10 values.
 * @param	items	The items.
 */

QuadricParameters::QuadricParameters(const vector<double> &items)
			: A(items[0]), B(items[1]), C(items[2]), D(items[3]),
				E(items[4]), F(items[5]), G(items[6]), H(items[7]),
				I(items[8]), J(items[9]) {
}

/**
 * @fn	QuadricParameters::QuadricParameters(double a, double b, double c, double d, double e, double , double g, double h, double i, double j)
 * @brief	Constructor
 * @param	a	Quadric parameter A.
 * @param	b	Quadric parameter B.
 * @param	c	Quadric parameter C.
 * @param	d	Quadric parameter D.
 * @param	e	Quadric parameter E.
 * @param	f	Quadric parameter F.
 * @param	g	Quadric parameter G.
 * @param	h	Quadric parameter H.
 * @param	i	Quadric parameter I.
 * @param	j	Quadric parameter J.
 */

QuadricParameters::QuadricParameters(double a, double b, double c, double d, double e, double f,
									double g, double h, double i, double j)
				: QuadricParameters(vector<double> {a, b, c, d, e, f, g, h, i, j}) {
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderXQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the x axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::cylinderXQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(0.0, 1.0 / R2, 1.0 / R2, 0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderYQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the y axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::cylinderYQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(1.0 / R2, 0, 1.0 / R2, 0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::cylinderZQParams(double R)
 * @brief	Constructs the parameters for a cylinder oriented along the z axis.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::cylinderZQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(1.0 / R2, 1.0 / R2, 0, 0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	QuadricParameters QuadricParameters::sphereQParams(double R)
 * @brief	Constructs the parameters for a sphere centered on the origin.
 * @param	R	Radius of cylinder.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::sphereQParams(double R) {
	double R2 = R * R;
	return QuadricParameters(1, 1, 1, 0, 0, 0, 0, 0, 0, -R2);
}

/**
 * @fn	QuadricParameters QuadricParameters::ellipsoidQParams(dvec3 sz)
 * @brief	Ellipoid parameters
 * @param	sz	Size of ellipsoid.
 * @return	The QuadricParameters.
 */

QuadricParameters QuadricParameters::ellipsoidQParams(const dvec3 &sz) {
	dvec3 size = sz * sz;
	return QuadricParameters(1.0 / size.x, 1.0 / size.y, 1.0 / size.z,
							0, 0, 0, 0, 0, 0, -1);
}

/**
 * @fn	IPlane::IPlane(const dvec3 &point, const dvec3 &normal)
 * @brief	Constructor
 * @param	point 	The point.
 * @param	normal	The normal.
 */

IPlane::IPlane(const dvec3 &point, const dvec3 &normal)
	: IShape(), a(point), n(normalize(normal)) {
}

/**
 * @fn	IPlane::IPlane(const vector<dvec3> &vertices)
 * @brief	Constructor
 * @param	vertices	The three vertices.
 */

IPlane::IPlane(const vector<dvec3> &vertices)
				: IShape() {
	a = vertices[0];
	n = glm::normalize(glm::cross(vertices[2] - vertices[1], vertices[0] - vertices[1]));
}

/**
 * @fn	IPlane::IPlane(const dvec3 &p0, const dvec3 &p1, const dvec3 &p2) : IShape(), a(p1), n(glm::normalize(glm::cross(p2 - p1, p0 - p1)))
 * @brief	Constructor
 * @param	p0	The p 0.
 * @param	p1	The first dvec3.
 * @param	p2	The second dvec3.
 */

IPlane::IPlane(const dvec3 &p0, const dvec3 &p1, const dvec3 &p2)
				: IShape(), a(p1), n(glm::normalize(glm::cross(p2 - p1, p0 - p1))) {
}

/**
 * @fn	bool IPlane::onFrontSide(const dvec3 &point) const
 * @brief	Determines if point is on the "front side of plane"
 * @param	point	The point.
 * @return	True if it succeeds, false if it fails.
 */

bool IPlane::onFrontSide(const dvec3 &point) const {
	// If dot product is positive the point is on the "positive" side of the plane
	bool onFront = glm::dot(point.xyz() - a, n) >= 0.0;
	return onFront;
}

/**
 * @fn	void IPlane::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Implicit representation of a plane
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IPlane::findClosestIntersection(const Ray &ray, HitRecord &hit) const {
	/* CSE 386 - todo  */
	double denom = glm::dot(ray.dir, n); // d dot n
	if (approximatelyZero(denom)) {
		hit.t = FLT_MAX;
	}
	else {
		double num = glm::dot(a - ray.origin, n); // (a-e) dot n
		double t = num / denom;
		if (t > 0) { // can see it
			hit.t = t;
			hit.normal = n;
			hit.interceptPt = ray.getPoint(t);
		}
		else {   // can't see it
			hit.t = FLT_MAX;
		}
	}
}

/**
 * @fn	void IPlane::findIntersection(const dvec3 &p1, const dvec3 &p2, double &t) const
 * @brief	Searches for the first intersection between a line segment. Used in the pipeline.
 * @param 	p1	The first point
 * @param 	p2	The second piont.
 * @param [in,out]	t 	The value of t where the intersection takes place.
 */

void IPlane::findIntersection(const dvec3 &p1, const dvec3 &p2, double &t) const {
	double d1 = glm::dot(p1.xyz() - a, n);
	double d2 = glm::dot(p2.xyz() - a, n);

	// Find the paramter of the intercept with the plane
	t = d1 / (d1 - d2);
}

/**
 * @fn	IQuadricSurface::IQuadricSurface(const QuadricParameters &params, const dvec3 &position)
 * @brief	Constructs an implicit representation of a QuadricSurface.
 * @param	params  	Options for controlling the operation.
 * @param	position	The position.
 */

IQuadricSurface::IQuadricSurface(const QuadricParameters &params, const dvec3 &position)
								: IShape(), qParams(params), center(position) {
	twoA = 2.0 * qParams.A;
	twoB = 2.0 * qParams.B;
	twoC = 2.0 * qParams.C;
}

/**
 * @fn	IQuadricSurface::IQuadricSurface(const vector<double> &params, const dvec3 &position)
 * @brief	Constructs an implicit representation of a QuadricSurface.
 * @param	params  	Quadric parameters.
 * @param	position	The position of the quadric.
 */

IQuadricSurface::IQuadricSurface(const vector<double> &params,
								const dvec3 &position) 
					: IQuadricSurface(QuadricParameters(params), position) {
}

/**
 * @fn	IQuadricSurface::IQuadricSurface(const dvec3 &position)
 * @brief	Constructs an implicit representation of a QuadricSurface.
 * @param	position	The position of the quadric.
 */

IQuadricSurface::IQuadricSurface(const dvec3 &position)
					: IQuadricSurface(QuadricParameters(), position) {
}

/**
 * @fn	void IQuadricSurface::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const
 * @brief	Calculates the aq bq cq
 * @param 		  	ray	The ray.
 * @param [in,out]	Aq 	The aq.
 * @param [in,out]	Bq 	The bq.
 * @param [in,out]	Cq 	The cq.
 */

void IQuadricSurface::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const {
	dvec3 Ro = ray.origin - center;
	const dvec3 &Rd = ray.dir;
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &D = qParams.D;
	const double &E = qParams.E;
	const double &F = qParams.F;
	const double &G = qParams.G;
	const double &H = qParams.H;
	const double &I = qParams.I;
	const double &J = qParams.J;
	Aq = A * (Rd.x*Rd.x) +
		B * (Rd.y*Rd.y) +
		C * (Rd.z*Rd.z) +
		D * (Rd.x * Rd.y) +
		E * (Rd.x * Rd.z) +
		F * (Rd.y * Rd.z);

	Bq = twoA * Ro.x*Rd.x +
		twoB * Ro.y*Rd.y +
		twoC * Ro.z*Rd.z +
		D * (Ro.x * Rd.y + Ro.y * Rd.x) +
		E * (Ro.x * Rd.z + Ro.z * Rd.x) +
		F * (Ro.y * Rd.z + Ro.z * Rd.y) +
		G * Rd.x + H * Rd.y + I * Rd.z;

	Cq = A * (Ro.x * Ro.x) +
		B * (Ro.y * Ro.y) +
		C * (Ro.z * Ro.z) +
		D * (Ro.x * Ro.y) +
		E * (Ro.x * Ro.z) +
		F * (Ro.y * Ro.z) +
		G * Ro.x +
		H * Ro.y +
		I * Ro.z + J;
}

/**
 * @fn	int IQuadricSurface::findIntersections(const Ray &ray, HitRecord hits[2]) const
 * @brief	Searches for the first intersections
 * @param	ray 	The ray.
 * @param	hits	The hits.
 * @return	The found intersections.
 */

int IQuadricSurface::findIntersections(const Ray &ray, HitRecord hits[2]) const {
	double Aq, Bq, Cq;
	computeAqBqCq(ray, Aq, Bq, Cq);
	double roots[2];

	int numRoots = quadratic(Aq, Bq, Cq, roots);
	int numIntersections = 0;

	for (int i = 0; i < numRoots; i++) {
		if (roots[i] > 0) {
			const double &t = roots[i];
			hits[numIntersections].t = t;
			hits[numIntersections].interceptPt = ray.origin + t * ray.dir;
			const dvec3 &intercept = hits[numIntersections].interceptPt;
			hits[numIntersections].normal = normal(intercept);
			numIntersections++;
		}
	}

	return numIntersections;
}

/**
 * @fn	void IQuadricSurface::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IQuadricSurface::findClosestIntersection(const Ray &ray, HitRecord &hit) const {
	static HitRecord hits[2];
	hit.t = FLT_MAX;

	int numIntercepts = findIntersections(ray, hits);
	if (numIntercepts == 1 && hits[0].t > 0) {
		hit.t = hits[0].t;
		hit.interceptPt = hits[0].interceptPt;
		hit.normal = normal(hit.interceptPt);
	} else if (numIntercepts == 2) {
		if (hits[0].t > 0) {
			hit.t = hits[0].t;
			hit.interceptPt = hits[0].interceptPt;
			hit.normal = normal(hit.interceptPt);
		} else if (hits[1].t > 0) {
			hit.t = hits[1].t;
			hit.interceptPt = hits[1].interceptPt;
			hit.normal = normal(hit.interceptPt);
		}
	}
}

/**
 * @fn	dvec3 IQuadricSurface::normal(const dvec3 &P) const
 * @brief	Normals the given p
 * @param	P	A dvec3 to process.
 * @return	A dvec3.
 */

dvec3 IQuadricSurface::normal(const dvec3 &P) const {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &D = qParams.D;
	const double &E = qParams.E;
	const double &F = qParams.F;
	const double &G = qParams.G;
	const double &H = qParams.H;
	const double &I = qParams.I;
	const double &J = qParams.J;
	dvec3 pt = P - center;
	dvec3 normal(twoA * pt.x + D * pt.y + E * pt.z + G,
					twoB * pt.y + D * pt.x + F * pt.z + H,
					twoC * pt.z + E * pt.x + F * pt.y + I);
	return glm::normalize(normal);
}

/**
 * @fn	ICylinder::ICylinder(const dvec3 &pos, double R, double L, const QuadricParameters &qParams)
 * @brief	Constructs an implicit representation of a cylinder.
 * @param	pos	   	The position.
 * @param	R	   	Radius.
 * @param	L	   	Length of cylinder.
 * @param	qParams	Quadric parameters.
 */

ICylinder::ICylinder(const dvec3 &pos, double R, double L,
					const QuadricParameters &qParams)
	: IQuadricSurface(qParams, pos), radius(R), length(L) {
}

/**
 * @fn	void ICylinder::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const
 * @brief	Calculates the aq bq cq
 * @param 		  	ray	The ray.
 * @param [in,out]	Aq 	The aq.
 * @param [in,out]	Bq 	The bq.
 * @param [in,out]	Cq 	The cq.
 */

void ICylinder::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &D = qParams.D;
	const double &E = qParams.E;
	const double &F = qParams.F;
	const double &G = qParams.G;
	const double &H = qParams.H;
	const double &I = qParams.I;
	const double &J = qParams.J;
	dvec3 Ro = ray.origin - center;
	const dvec3 &Rd = ray.dir;

	Aq = A * (Rd.x*Rd.x) +
		B * (Rd.y*Rd.y) +
		C * (Rd.z*Rd.z);
	//D * (Rd.x * Rd.y) +
	//E * (Rd.x * Rd.z) +
	//F * (Rd.y * Rd.z);

	Bq = twoA * Ro.x*Rd.x +
		twoB * Ro.y*Rd.y +
		twoC * Ro.z*Rd.z;
	//D * (Ro.x * Rd.y + Ro.y * Rd.x) +
	//E * (Ro.x * Rd.z + Ro.z * Rd.x) +
	//F * (Ro.y * Rd.z + Ro.z * Rd.y) +
	//G * Rd.x + H * Rd.y + I * Rd.z;

	Cq = A * (Ro.x * Ro.x) +
		B * (Ro.y * Ro.y) +
		C * (Ro.z * Ro.z) +
		//D * (Ro.x * Ro.y) +
		//E * (Ro.x * Ro.z) +
		//F * (Ro.y * Ro.z) +
		//G * Ro.x +
		//H * Ro.y +
		//I * Ro.z +
		J;
}

/**
 * @fn	ICylinderY::ICylinderY(const dvec3 &pos, double rad, double len) : ICylinder(pos, rad, len, QuadricParameters::cylinderYQParams(rad))
 * @brief	Constructor
 * @param	pos	The position.
 * @param	rad	The radians.
 * @param	len	The length.
 */

ICylinderY::ICylinderY(const dvec3 &pos, double rad, double len)
	: ICylinder(pos, rad, len, QuadricParameters::cylinderYQParams(rad)) {
}

/**
 * @fn	void ICylinderY::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void ICylinderY::findClosestIntersection(const Ray &ray, HitRecord &hit) const {
	const dvec3 &rayOrigin = ray.origin;
	const dvec3 &rayDirection = ray.dir;
	static HitRecord hits[2];
	int numHits = ICylinder::findIntersections(ray, hits);
	for (int i = 0; i < numHits; i++) {
		if (hits[i].interceptPt.y < center.y + length / 2 &&
			hits[i].interceptPt.y > center.y - length / 2) {
				hit = hits[i];
				return;
		}
	}
	hit.t = FLT_MAX;
}

/**
* @fn	void ICylinderY::getTexCoords(const dvec3 &pt, double &u, double &v) const
* @brief	Gets tex coordinates
* @param 		  	pt	The point.
* @param [in,out]	u 	Tex coordinate u.
* @param [in,out]	v 	Tex coordinate v.
*/

void ICylinderY::getTexCoords(const dvec3 &pt, double &u, double &v) const {
	/* CSE 386 - todo  */
	u = v = 0;
}

/**
 * @fn	ICylinderY::ICylinderY(const dvec3 &pos, double rad, double len) : ICylinder(pos, rad, len, QuadricParameters::cylinderYQParams(rad))
 * @brief	Constructor
 * @param	pos	The position.
 * @param	rad	The radians.
 * @param	len	The length.
 */

IClosedCylinderY::IClosedCylinderY(const dvec3& pos, double rad, double len)
	: ICylinder(pos, rad, len, QuadricParameters::cylinderYQParams(rad)) {
}

/**
 * @fn	void ICylinderY::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void IClosedCylinderY::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	const dvec3& rayOrigin = ray.origin;
	const dvec3& rayDirection = ray.dir;
	static HitRecord hits[2];
	int numHits = ICylinder::findIntersections(ray, hits);
	for (int i = 0; i < numHits; i++) {
		if (hits[i].interceptPt.y < center.y + length / 2 &&
			hits[i].interceptPt.y > center.y - length / 2) {
			hit = hits[i];
			return;
		}
	}
	hit.t = FLT_MAX;
}

/**
* @fn	void ICylinderY::getTexCoords(const dvec3 &pt, double &u, double &v) const
* @brief	Gets tex coordinates
* @param 		  	pt	The point.
* @param [in,out]	u 	Tex coordinate u.
* @param [in,out]	v 	Tex coordinate v.
*/

void IClosedCylinderY::getTexCoords(const dvec3& pt, double& u, double& v) const {
	/* CSE 386 - todo  */
	u = v = 0;
}


ICylinderZ::ICylinderZ(const dvec3& pos, double rad, double len)
	: ICylinder(pos, rad, len, QuadricParameters::cylinderZQParams(rad)) {
}

/**
 * @fn	void ICylinderY::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	The hit.
 */

void ICylinderZ::findClosestIntersection(const Ray& ray, HitRecord& hit) const {
	const dvec3& rayOrigin = ray.origin;
	const dvec3& rayDirection = ray.dir;
	static HitRecord hits[2];
	int numHits = ICylinder::findIntersections(ray, hits);
	for (int i = 0; i < numHits; i++) {
		if (hits[i].interceptPt.z < center.z + length / 2 &&
			hits[i].interceptPt.z > center.z - length / 2) {
			hit = hits[i];
			return;
		}
	}
	hit.t = FLT_MAX;
}

/**
* @fn	void ICylinderY::getTexCoords(const dvec3 &pt, double &u, double &v) const
* @brief	Gets tex coordinates
* @param 		  	pt	The point.
* @param [in,out]	u 	Tex coordinate u.
* @param [in,out]	v 	Tex coordinate v.
*/

void ICylinderZ::getTexCoords(const dvec3& pt, double& u, double& v) const {
	/* CSE 386 - todo  */
	u = v = 0;
}

ITriangle::ITriangle(const dvec3 &A, const dvec3 &B, const dvec3 &C)
	: IShape(), a(A), b(B), c(C), plane(IPlane(A, B, C)) {
}

/**
 * @fn	bool ITriangle::inside(const dvec3 &pt) const
 * @brief	Insides the given point
 * @param	pt	The point.
 * @return	true iff the point is inside the triangle.
 */

bool ITriangle::inside(const dvec3 &pt) const { // equation 2.35
	dvec3 n = glm::cross(b - a, c - a);
	double n2 = std::pow(glm::length(n), 2.0);
	dvec3 na = glm::cross(c - b, pt - b);
	dvec3 nb = glm::cross(a - c, pt - c);
	dvec3 nc = glm::cross(b - a, pt - a);
	double alpha = glm::dot(n, na) / n2;
	double beta = glm::dot(n, nb) / n2;
	double gamma = glm::dot(n, nc) / n2;
	return inRangeExclusive(beta, 0, 1) && inRangeExclusive(gamma, 0, 1) && inRangeExclusive(alpha, 0, 1);
}

/**
 * @fn	void ITriangle::findClosestIntersection(const Ray &ray, HitRecord &hit) const
 * @brief	Searches for the nearest intersection
 * @param 		  	ray	The ray.
 * @param [in,out]	hit	Hit record.
 */

void ITriangle::findClosestIntersection(const Ray &ray, HitRecord &hit) const {
	plane.findClosestIntersection(ray, hit);
	hit.normal = plane.n;
	if (!inside(hit.interceptPt)) {
		hit.t = FLT_MAX;
	}
}

/**
 * @fn	IEllipsoid::IEllipsoid(const dvec3 &position, const dvec3 &sz) : IQuadricSurface(QuadricParameters::ellipoidParameters(sz), position)
 * @brief	Constructs an implicit representation of an ellipsoid.
 * @param	position	The center of ellipsoid.
 * @param	sz			The size of ellipsoid.
 */

IEllipsoid::IEllipsoid(const dvec3 &position, const dvec3 &sz)
	: IQuadricSurface(QuadricParameters::ellipsoidQParams(sz), position) {
}

/**
 * @fn	void IEllipsoid::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const
 * @brief	Calculates the aq bq cq, given a particular ray.
 * @param 		  	ray	The ray.
 * @param [in,out]	Aq 	Aq.
 * @param [in,out]	Bq 	Bq.
 * @param [in,out]	Cq 	Cq.
 */

void IEllipsoid::computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const {
	const double &A = qParams.A;
	const double &B = qParams.B;
	const double &C = qParams.C;
	const double &D = qParams.D;
	const double &E = qParams.E;
	const double &F = qParams.F;
	const double &G = qParams.G;
	const double &H = qParams.H;
	const double &I = qParams.I;
	const double &J = qParams.J;
	dvec3 Ro = ray.origin - center;
	const dvec3 &Rd = ray.dir;

	Aq = A * (Rd.x*Rd.x) +
		B * (Rd.y*Rd.y) +
		C * (Rd.z*Rd.z);
	//D * (Rd.x * Rd.y) +
	//E * (Rd.x * Rd.z) +
	//F * (Rd.y * Rd.z);

	Bq = 2 * A * Ro.x*Rd.x +
		2 * B * Ro.y*Rd.y +
		2 * C * Ro.z*Rd.z;
	//D * (Ro.x * Rd.y + Ro.y * Rd.x) +
	//E * (Ro.x * Rd.z + Ro.z * Rd.x) +
	//F * (Ro.y * Rd.z + Ro.z * Rd.y) +
	//G * Rd.x + H * Rd.y + I * Rd.z;

	Cq = A * (Ro.x * Ro.x) +
		B * (Ro.y * Ro.y) +
		C * (Ro.z * Ro.z) +
		//D * (Ro.x * Ro.y) +
		//E * (Ro.x * Ro.z) +
		//F * (Ro.y * Ro.z) +
		//G * Ro.x +
		//H * Ro.y +
		I * Ro.z + J;
}
