/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#pragma once
#include <vector>
#include "HitRecord.h"

struct IShape;
typedef IShape *IShapePtr;
struct VisibleIShape;
typedef VisibleIShape *VisibleIShapePtr;

/**
 * @struct	Ray
 * @brief	Represents a ray.
 */

struct Ray {
	dvec3 origin;		//!< starting point for this ray
	dvec3 dir;			//!< direction for this ray, given it's origin
	Ray(const dvec3 &rayOrigin, const dvec3 &rayDirection) :
		origin(rayOrigin), dir(glm::normalize(rayDirection)) {
	}
	dvec3 getPoint(double t) const {
		return origin + t * dir;
	}
};

/**
 * @struct	IShape
 * @brief	Base class for all implicit shapes.
 */

struct IShape {
	IShape();
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const = 0;
	virtual void getTexCoords(const dvec3 &pt, double &u, double &v) const;
	static dvec3 movePointOffSurface(const dvec3 &pt, const dvec3 &n);
};

/**
 * @struct	VisibleIShape
 * @brief	A visible implicit shape.
 */

struct VisibleIShape {
	Material material;	//!< Material for this shape.
	IShapePtr shape;	//!< Pointer to underlying implicit shape.
	Image *texture;		//!< Texture associated with this shape, if any.
	VisibleIShape(IShapePtr shapePtr, const Material &mat);
	void findClosestIntersection(const Ray &ray, HitRecord &hit) const;
	void setTexture(Image *tex);
	static HitRecord findIntersection(const Ray &ray, const vector<VisibleIShapePtr> &surfaces);
};

/**
 * @struct	IPlane
 * @brief	An implicit representation of a plane.
 */

struct IPlane : public IShape {
	dvec3 a;	//!< point on the plane
	dvec3 n;	//!< plane's normal vector
	IPlane(const dvec3 &point, const dvec3 &normal);
	IPlane(const vector<dvec3> &vertices);
	IPlane(const dvec3 &p1, const dvec3 &p2, const dvec3 &p3);
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const;
	bool onFrontSide(const dvec3 &point) const;
	void findIntersection(const dvec3 &p1, const dvec3 &p2, double &t) const;
};

/**
 * @struct	IDisk
 * @brief	Implicit representation of a disk (i.e., 2D circle) with a particular
 * 			center and normal vector.
 */

struct IDisk : public IShape {
	IDisk();
	IDisk(const dvec3 &position, const dvec3 &n, double rad);
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const;
	virtual void getTexCoords(const dvec3& pt, double& u, double& v) const;
	dvec3 center;	//!< center point of disk
	dvec3 n;		//!< normal vector of disk
	double radius;
};

/**
 * @struct	QuadricParameters
 * @brief	Represents the 9 parameters that describe a quadric.
 */

struct QuadricParameters {
	double A, B, C, D, E, F, G, H, I, J;
	QuadricParameters();
	QuadricParameters(const vector<double> &items);
	QuadricParameters(double a, double b, double c, double d, double e, double f,
						double g, double h, double i, double j);
	static QuadricParameters cylinderXQParams(double R);
	static QuadricParameters cylinderYQParams(double R);
	static QuadricParameters cylinderZQParams(double R);
	static QuadricParameters sphereQParams(double R);
	static QuadricParameters ellipsoidQParams(const dvec3 &sz);

};

/**
 * @struct	ITriangle
 * @brief	Implicit representation of triangle.
 */

struct ITriangle : public IShape {
	dvec3 a;	//!< first vertex.
	dvec3 b;	//!< second vertex.
	dvec3 c;	//!< third vertex.
	IPlane plane;	//!< the plane this triangle lies on.
	ITriangle(const dvec3 &A, const dvec3 &B, const dvec3 &C);
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const;
	bool inside(const dvec3 &pt) const;
};

/**
 * @struct	IQuadricSurface
 * @brief	Implicit representation of quadric surface. These shapes can be
 * 			described by the general quadric surface equation
 */

struct IQuadricSurface : public IShape {
	dvec3 center;	//!< center of quadric
	IQuadricSurface(const QuadricParameters &params,
					const dvec3 &position);
	IQuadricSurface(const vector<double> &params,
					const dvec3 & position);
	IQuadricSurface(const dvec3 & position);
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const;
	int findIntersections(const Ray &ray, HitRecord hits[2]) const;
	dvec3 normal(const dvec3 &pt) const;
	virtual void computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const;
protected:
	QuadricParameters qParams;		//!< The parameters that make up the quadric
	double twoA;					//!< 2*A
	double twoB;					//!< 2*B
	double twoC;					//!< 2*C
};

/**
 * @struct	ISphere
 * @brief	Implicit representation of sphere.
 */

struct ISphere : IQuadricSurface {
	ISphere(const dvec3 &position, double radius);
	virtual void getTexCoords(const dvec3 &pt, double &u, double &v) const;
	virtual void computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const;
};

/**
 * @struct	ICylinder
 * @brief	Base class for implicit representation of a cylinder.
 */

struct ICylinder : public IQuadricSurface {
	double radius, length;
	ICylinder(const dvec3 &position, double R, double len, const QuadricParameters &qParams);
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const = 0;
	virtual void computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const;
};

/**
 * @struct	ICylinderY
 * @brief	Implicit representation of open cylinder oriented along y-axis coordinate.
 */

struct ICylinderY : public ICylinder {
	ICylinderY(const dvec3 &position, double R, double len);
	virtual void findClosestIntersection(const Ray &ray, HitRecord &hit) const;
	void getTexCoords(const dvec3 &pt, double &u, double &v) const;
};

/*
 * @struct ICylinderZ
 * @brief implicit representation of open cylinder oriented along z-axis coordinate.
 */

struct IClosedCylinderY : public ICylinder {
	IClosedCylinderY(const dvec3& position, double R, double len);
	virtual void findClosestIntersection(const Ray& ray, HitRecord& hit) const;
	void getTexCoords(const dvec3& pt, double& u, double& v) const;
};

/*
 * @struct ICylinderZ
 * @brief implicit representation of open cylinder oriented along z-axis coordinate.
 */

struct ICylinderZ : public ICylinder {
	ICylinderZ(const dvec3& position, double R, double len);
	virtual void findClosestIntersection(const Ray& ray, HitRecord& hit) const;
	void getTexCoords(const dvec3& pt, double& u, double& v) const;
};

/**
 * @struct	IEllipsoid
 * @brief	Implicit representation of an ellipsoid.
 */

struct IEllipsoid : public IQuadricSurface {
	IEllipsoid(const dvec3 &position, const dvec3 &sz);
	virtual void computeAqBqCq(const Ray &ray, double &Aq, double &Bq, double &Cq) const;
};