#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
#include "Noise.h"
class Material
{
public:
	
	Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0, float r =0 );

    virtual ~Material();

    virtual Vector3f getDiffuseColor() const ;

    Vector3f Shade( const Ray& ray, const Hit& hit, const Vector3f& dirToLight, const Vector3f& lightColor ) ;

	static  Vector3f pointwiseDot( const Vector3f& v1 , const Vector3f& v2 );

	float clampedDot( const Vector3f& L , const Vector3f& N )const;
	void loadTexture(const char * filename);
	float getRefractionIndex();
	void setRefractionIndex(float r);
	Vector3f getDiffuseColor();
	Vector3f getSpecularColor();

	void setNoise(const Noise & n);

	// Used to set the final UV for Shading
	void setUV(Vector2f& uv) { this->uv = uv; }

	Vector3f getK() {
		// Handles textures if texture is valid
		if (t.valid()) {
			return t(uv[0], uv[1]);
		}
		return getDiffuseColor();
	}

protected:
  Vector3f diffuseColor;
  float refractionIndex;
  float shininess;
  Vector3f specularColor;
  Texture t;
  Noise noise;
  Vector2f uv;
};

#endif // MATERIAL_H
