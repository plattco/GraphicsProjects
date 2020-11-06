/****************************************************
 * 2016-2020 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted..
 ****************************************************/

#include "Light.h"
#include <math.h>
#include <cmath>


void changeLightPos(dvec3 cameraPos, dvec3 pos, bool isTiedToWorld) {
	if (isTiedToWorld) {
		pos = cameraPos;
	}
	else if (!isTiedToWorld) {
		pos = pos;
	}
}

/**
 * @fn	color ambientColor(const color &mat, const color &light)
 * @brief	Computes the ambient color produced by a single light at a single point.
 * @param	mat  	Ambient material property.
 * @param	light	Light's ambient color.
 * @return	Ambient color.
  */

color ambientColor(const color &mat, const color &light) {
	dvec3 answer;
	answer.x = mat.x * light.x;
	answer.y = mat.y * light.y;
	answer.z = mat.z * light.z;
	return answer;
}

/**
 * @fn	color diffuseColor(const color &mat, const color &light, const dvec3 &l, const dvec3 &n)
 * @brief	Computes diffuse color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	light	 	The light.
 * @param	l		 	Light vector.
 * @param	n		 	Normal vector.
 * @return	Diffuse color.
 */

// not working
color diffuseColor(const color &mat, const color &light,
					const dvec3 &l, const dvec3 &n) {
	/* CSE 386 - todo  */

	// Assuming that the light.diffuse, mat.diffuse is given as the color vectors
	dvec3 answer; // should be light.diffuse * mat.diffuse * (l*n)
	dvec3 num1; // = cross(light, mat);
	double num2; // = dot(l, n);
	num1.x = mat.x * light.x;
	num1.y = mat.y * light.y;
	num1.z = mat.z * light.z;
	num2 = glm::dot(l, n);
	answer.x = num1.x * num2;
	answer.y = num1.y * num2;
	answer.z = num1.z * num2;
	return answer;
}

/**
 * @fn	color specularColor(const color &mat, const color &light, double shininess, const dvec3 &r, const dvec3 &v)
 * @brief	Computes specular color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	light	 	The light's color.
 * @param	shininess	Material shininess.
 * @param	r		 	Reflection vector.
 * @param	v		 	Viewing vector.
 * @return	Specular color.
 */


color specularColor(const color &mat, const color &light,
					double shininess,
					const dvec3 &r, const dvec3 &v) {
	dvec3 answer; // Assuming that the light.specular, mat.specular is given as the color vectors
	double dotProd = abs((r.x * v.x) + (r.y * v.y) + (r.z * v.z));
	dvec3 num1; // = cross(light, mat);
	num1.x = mat.x * light.x;
	num1.y = mat.y * light.y;
	num1.z = mat.z * light.z;
	double num2 = abs(pow(dotProd, shininess));
	answer = num1 * num2;
	// answer = abs(answer);
	return answer;
	
}

/**
 * @fn	color totalColor(const Material &mat, const LightColor &lightColor, const dvec3 &viewingDir, const dvec3 &normal, const dvec3 &lightPos, const dvec3 &intersectionPt, bool attenuationOn, const LightAttenuationParameters &ATparams)
 * @brief	Color produced by a single light at a single point.
 * @param	mat			  	Material.
 * @param	lightColor	  	The light's color.
 * @param	v	  			The v vector.
 * @param	n   		  	Normal vector.
 * @param	lightPos	  	Light position.
 * @param	intersectionPt	(x,y,z) of intersection point.
 * @param	attenuationOn 	true if attenuation is on.
 * @param	ATparams	  	Attenuation parameters.
 * @return	Color produced by a single light at a single point.
 */
 

color totalColor(const Material &mat, const LightColor &lightColor,
				const dvec3 &v, const dvec3 &n,
				const dvec3 &lightPos, const dvec3 &intersectionPt,
				bool attenuationOn, 
				const LightATParams &ATparams) {
	if (DEBUG_PIXEL) {
		cout << endl;
	}
	// need to compute r
	// cal ambientColor(), diffuseColor()	
	dvec3 l = glm::normalize(lightPos - intersectionPt);
	// double dotProd = (l.x * n.x) + (l.y * n.y) + (l.z * n.z);
	// double num1 = 2 * dotProd;
	dvec3 r = glm::normalize(2.0 * glm::dot(l, n) * n - l);
	// dvec3 r = num1 * (n - l); // struggled with order of operations / correct operations. I could not find a clean example / way to get through this
	dvec3 speccy = specularColor(mat.specular, lightColor.specular, mat.shininess, r, v);
	dvec3 diffy = diffuseColor(mat.diffuse, lightColor.diffuse, l, n);
	dvec3 ambby = ambientColor(mat.ambient, lightColor.ambient);
	color answer = speccy + diffy + ambby;
	return answer;
}

/**
 * @fn	color PositionalLight::illuminate(const dvec3 &interceptWorldCoords, const dvec3 &normal, const Material &material, const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	interceptWorldCoords				The surface properties of the intercept point.
 * @param	normal					The normal vector.
 * @param	material			The object's material properties.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color PositionalLight::illuminate(const dvec3 &interceptWorldCoords,
									const dvec3 &normal,
									const Material &material,
									const Frame &eyeFrame, bool inShadow) const {


	if (!inShadow && isOn) {
		dvec3 color;
		dvec3 tempy;
		tempy.x = eyeFrame.origin.x - interceptWorldCoords.x;
		tempy.y = eyeFrame.origin.y - interceptWorldCoords.y;
		tempy.z = eyeFrame.origin.z - interceptWorldCoords.z;
		 color = totalColor(material, lightColor, normalize(tempy), normalize(normal), pos, interceptWorldCoords, attenuationIsTurnedOn, atParams); // I tried finding v as e-point (eyeframe-vec)
		return color;
	}
	else if (isOn && inShadow) {
		dvec3 ambby = ambientColor(material.ambient, lightColor.ambient);
		return ambby;
	}
	else if (!isOn) {
		return black;
	}
	return material.ambient;
}

color PositionalLight::illuminate(const dvec3& interceptWorldCoords, const dvec3& normal, const Material& material, const Frame& eyeFrame, bool inShadow)
{
	if (!inShadow && isOn) {
		dvec3 color;
		dvec3 tempy;
		tempy.x = eyeFrame.origin.x - interceptWorldCoords.x;
		tempy.y = eyeFrame.origin.y - interceptWorldCoords.y;
		tempy.z = eyeFrame.origin.z - interceptWorldCoords.z;
		color = totalColor(material, lightColor, normalize(tempy), normalize(normal), pos, interceptWorldCoords, attenuationIsTurnedOn, atParams); // I tried finding v as e-point (eyeframe-vec)
		return color;
	}
	else if (isOn && inShadow) {
		dvec3 ambby = ambientColor(material.ambient, lightColor.ambient);
		return ambby;
	}
	else if (!isOn) {
		return black;
	}
	return material.ambient;
}



/**
 * @fn	color SpotLight::illuminate(const dvec3 &interceptWorldCoords, const dvec3 &normal, const Material &material, const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	interceptWorldCoords				The surface properties of the intercept point.
 * @param	normal					The normal vector.
 * @param	material			The object's material properties.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color SpotLight::illuminate(const dvec3 &interceptWorldCoords,
							const dvec3 &normal,
							const Material &material,
							const Frame &eyeFrame, bool inShadow) const {
	if (!inShadow && isOn) {
		dvec3 color;
		dvec3 tempy;
		tempy.x = eyeFrame.origin.x - interceptWorldCoords.x;
		tempy.y = eyeFrame.origin.y - interceptWorldCoords.y;
		tempy.z = eyeFrame.origin.z - interceptWorldCoords.z;
		color = totalColor(material, lightColor, normalize(tempy), normalize(normal), pos, interceptWorldCoords, attenuationIsTurnedOn, atParams); // I tried finding v as e-point (eyeframe-vec)
		return color;
	}
	else if (isOn && inShadow) {
		dvec3 ambby = ambientColor(material.ambient, lightColor.ambient);
		return ambby;
	}
	else if (!isOn) {
		return black;
	}
	return material.ambient;
}

/**
* @fn	ostream &operator << (ostream &os, const LightAttenuationParameters &at)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	at		Attenuation parameters.
* @return	The output stream.
*/

ostream &operator << (ostream &os, const LightATParams &at) {
	os << dvec3(at.constant, at.linear, at.quadratic) << endl;
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const PositionalLight &pl)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	pl		Positional light.
* @return	The output stream.
*/

ostream &operator << (ostream &os, const PositionalLight &pl) {
	os << (pl.isOn ? "ON" : "OFF") << endl;
	os << (pl.isTiedToWorld? "WORLD" : "CAMERA") << endl;
	os << " position " << pl.pos << endl;
	os << " ambient " << pl.lightColor.ambient << endl;
	os << " diffuse " << pl.lightColor.diffuse << endl;
	os << " specular " << pl.lightColor.specular << endl;
	os << "Attenuation: " << (pl.attenuationIsTurnedOn ? "ON" : "OFF")
		<< " " << pl.atParams << endl;
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const SpotLight &sl)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	sl		Spotlight.
* @return	The output stream.
*/

ostream &operator << (ostream &os, const SpotLight &sl) {
	PositionalLight pl = (sl);
	os << pl;
	os << " FOV " << sl.fov << endl;
	return os;
}


ostream &operator << (ostream &os, const LightColor &light) {
	os << "Light Color: " << light.ambient << ' ' << light.diffuse <<
				' ' << light.specular;
	return os;
}
