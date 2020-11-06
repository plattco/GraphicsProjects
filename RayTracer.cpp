/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/


#include "RayTracer.h"
#include "IShape.h"
#include "Light.h"


/**
 * @fn	RayTracer::RayTracer(const color &defa)
 * @brief	Constructs a raytracers.
 * @param	defa	The clear color.
 */

RayTracer::RayTracer(const color &defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth,
								const IScene &theScene) const {
	const RaytracingCamera &camera = *theScene.camera;
	const vector<VisibleIShapePtr> &objs = theScene.opaqueObjs;
	const vector<PositionalLightPtr> &lights = theScene.lights;
	//PositionalLight posLight(dvec3(-10, 10, 10), pureWhiteLight);

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
			DEBUG_PIXEL = (x == xDebug && y == yDebug);
			if (DEBUG_PIXEL) {
				cout << "";
			}
			Ray ray = camera.getRay(x, y);
			HitRecord hit = VisibleIShape::findIntersection(ray, theScene.opaqueObjs);
			HitRecord hit2 = VisibleIShape::findIntersection(ray, theScene.transparentObjs);
			color totalColor;
			color transColor;
			bool inShadow = false;
			bool inShadowTrans = false;
			

			for (PositionalLightPtr light : theScene.lights) { // can I include both transparent and not transparent in one loop or separate into two?
				// determine distance to light from intersection
				dvec3 distance = light->pos - hit.interceptPt;
				double d = glm::distance(light->pos, hit.interceptPt);
				// determine direction to light source from intersection. How?
				dvec3 direction(light->pos.x - hit.interceptPt.x, light->pos.y - hit.interceptPt.y, light->pos.z - hit.interceptPt.z);
				normalize(direction);

				// make a shadow feeler using intersection as origin and direction as light vector
				//ShadowFeeler shadow = ShadowFeeler(hit.interceptPt, direction);
				Ray shadowFeeler = Ray(hit.interceptPt + 0.001 * hit.normal, direction);
				Ray shadowFeeler2 = Ray((hit2.interceptPt + 0.001 * hit2.normal), direction);
				// check the shadow feeler for intersection with object in scene to find the first object it hits (using hitrecotd?)
				HitRecord shadowHit = VisibleIShape::findIntersection(shadowFeeler, theScene.opaqueObjs);
				HitRecord shadowHitTrans = VisibleIShape::findIntersection(shadowFeeler2, theScene.opaqueObjs);
				dvec3 newDistance = light->pos - shadowHit.interceptPt;
				dvec3 newDistance2 = light->pos - shadowHitTrans.interceptPt;
				if (newDistance.z < distance.z) {
					inShadow = true;
				}
				else {
					inShadow = false;
				}

				if (newDistance2.z < distance.z) {
					inShadowTrans = true;
				}
				else {
					inShadowTrans = false;
				}
				// if there is no hit or if distance to the intersection > distance to the light then do below
				if (hit.texture != nullptr) {
					color C = hit.texture->getPixelUV(hit.u, hit.v);
					totalColor = totalColor + C;
				}
				color c = light->illuminate(hit.interceptPt, hit.normal, hit.material, camera.cameraFrame, inShadow);
				color transLight = light->illuminate(hit2.interceptPt, hit2.normal, hit2.material, camera.cameraFrame, inShadow);
				// color trans = hit2.material.ambient * hit2.material.alpha; // hit2.interceptPt, hit2.normal, hit2.material, camera.cameraFrame, false);
				totalColor = totalColor + c /*+ trans*/;
				transColor = totalColor + c + transLight;
				dvec3 n = hit.normal;
				if (glm::dot(n, ray.dir) > 0) {
					n = -n;
				}
				hit.normal = n;
			}


			color transAndBackground = ((hit2.material.ambient * hit2.material.alpha) * defaultColor);
			//color transAndBackground = (transColor * defaultColor);
			color trans = hit2.material.ambient;
			color C = (1 - hit.material.alpha) * totalColor + (hit2.material.alpha * trans);
			// frameBuffer.setColor(x, y, totalColor);
			if (hit.interceptPt == dvec3(0,0,0)) {
				frameBuffer.setColor(x, y, defaultColor);
			}
			else if (hit.material.alpha > 0.95) {
				frameBuffer.setColor(x, y, totalColor);
			}
			else if (hit2.interceptPt != dvec3(0,0,0) && hit.interceptPt == dvec3(0,0,0)) {
				frameBuffer.setColor(x, y, transAndBackground);
			}
			else if (hit2.interceptPt != dvec3(0, 0, 0) && hit.interceptPt != dvec3(0, 0, 0)) {
				frameBuffer.setColor(x, y, C);
			}
			//if no hit default color
			//if solid hit only totalColor
			//if both below
			//if transparent hit only mix trans and background color
			/*if (both are hit && hit1 > hit2) {
				frameBuffer.setColor(x, y, C);
			}*/

			/* Reflection pseudocode (I think it goes in here, not in traceIndividualRay)
			Check the ray against every object to find closest intersection
			If the ray hits an object

				Initialize total illumination to emissive color of the object
				For each light source do

					Use a shadow feeler to check if the light source is blocked
					If the light source is not blocked

						Add illumination for the light source to total illumination

				If the recursive base case has not been reached

					Create a reflection ray
					Recursively trace the reflection ray
					Add the result of tracing the reflection ray to total illumination
					Attenuate total illumination based on distance to closest intersection
					Return total illumination

			Else

				return default color
			*/
			//frameBuffer.setColor(x, y, totalColor);
			//frameBuffer.setColor(x, y, hit.material.diffuse);
			// color c = illuminate(hit.interceptPt, hit.normal, hit.material, camera.cameraFrame, false);
			// color c = lights[0]->illuminate(hit.interceptPt, hit.normal, hit.material, camera.cameraFrame, false);
			// frameBuffer.showAxes(x, y, ray, 0.25);			// Displays R/x, G/y, B/z axes
			// HitRecord hit = VisibleIShape::findIntersection(ray, theScene.opaqueObjs);
		}
	}
	frameBuffer.showColorBuffer();
}


/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray, const IScene &theScene, int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray &ray, const IScene &theScene, int recursionLevel) const {
	/* CSE 386 - todo  */
	HitRecord theHit = VisibleIShape::findIntersection(ray, theScene.opaqueObjs);
	color result = defaultColor;

	if (theHit.t < FLT_MAX) {
		color totalColor = theHit.material.ambient;
		result = defaultColor;
	}

	return result;
}

