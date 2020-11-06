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
#include "Defs.h"
#include "ColorAndMaterials.h"
#include "Image.h"
#include "Utilities.h"

/**
 * @struct	HitRecord
 * @brief	Stores information regarding a ray-object intersection. Used in raytracing.
 */

struct HitRecord {
	double t;					//!< the t value where the intersection took place.
	dvec3 interceptPt;		//!< the (x,y,z) value where the intersection took place.
	dvec3 normal;			//!< the normal vector at the intersection point.
	Material material;			//!< the Material value of the object.
	Image *texture;				//!< the texture associated with this object, if any.
	double u, v;				//!< (u,v) correpsonding to intersection point.

	/**
	 * @fn	HitRecord()
	 * @brief	Constructs a HitRecord that corresponds to "no hit"
	 */

	HitRecord() {
		u = v = 0;
		t = FLT_MAX;
		texture = nullptr; 
	}

	/**
	 * @fn	static HitRecord getClosest(const vector<HitRecord> &hits)
	 * @brief	Gets a closest, give a vector of hits.
	 * @param	hits	The hits to consider.
	 * @return	The closest hit, that is in front of the camera.
	 */

	static HitRecord getClosest(const vector<HitRecord> &hits) {
		HitRecord theHit;
		for (size_t i = 0; i < hits.size(); i++) {
			if (inRangeExclusive(hits[i].t, 0, theHit.t)) {
				theHit = hits[i];
			}
		}
		return theHit;
	}
};