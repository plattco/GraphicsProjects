/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "IScene.h"

/**
 * @fn	IScene::IScene(RaytracingCamera *theCamera)
 * @brief	Construct scene using a particular camera.
 * @param [in,out]	theCamera	The camera to use.
 */

IScene::IScene(RaytracingCamera *theCamera) {
	camera = theCamera;
}

/**
 * @fn	void IScene::addOpaqueObject(const VisibleIShapePtr obj)
 * @brief	Adds an visible object to the scene
 * @param	obj	The object to be added.
 */

void IScene::addOpaqueObject(const VisibleIShapePtr obj) {
	opaqueObjs.push_back(obj);
}

/**
 * @fn	void IScene::addTransparentObject(const VisibleIShapePtr obj, double alpha)
 * @brief	Adds a transparent object to the scene
 * @param	obj  	The transparent object to be added.
 * @param	alpha	The alpha value of the object.
 */

void IScene::addTransparentObject(const VisibleIShapePtr obj, double alpha) {
	obj->material.alpha = alpha;
	transparentObjs.push_back(obj);
}

/**
 * @fn	void IScene::addLight(const PositionalLightPtr light)
 * @brief	Adds a positional light to the scene.
 * @param	light	The light to be added.
 */

void IScene::addLight(const PositionalLightPtr light) {
	lights.push_back(light);
}
