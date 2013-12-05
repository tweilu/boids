#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m){
          this->a = a;
          this->b = b;
          this->c = c;
          this->material = m;
          hasTex = false;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){
		
		Matrix3f t_mat = Matrix3f(	this->a.x() - this->b.x(), this->a.x() - this->c.x(), this->a.x() - ray.getOrigin().x(),
									this->a.y() - this->b.y(), this->a.y() - this->c.y(), this->a.y() - ray.getOrigin().y(),
									this->a.z() - this->b.z(), this->a.z() - this->c.z(), this->a.z() - ray.getOrigin().z());
		Matrix3f a_mat = Matrix3f(	this->a.x() - this->b.x(), this->a.x() - this->c.x(), ray.getDirection().x(),
									this->a.y() - this->b.y(), this->a.y() - this->c.y(), ray.getDirection().y(),
									this->a.z() - this->b.z(), this->a.z() - this->c.z(), ray.getDirection().z());
		Matrix3f b_mat = Matrix3f(	this->a.x() - ray.getOrigin().x(), this->a.x() - this->c.x(), ray.getDirection().x(),
									this->a.y() - ray.getOrigin().y(), this->a.y() - this->c.y(), ray.getDirection().y(),
									this->a.z() - ray.getOrigin().z(), this->a.z() - this->c.z(), ray.getDirection().z());
		Matrix3f c_mat = Matrix3f(	this->a.x() - this->b.x(), this->a.x() - ray.getOrigin().x(), ray.getDirection().x(),
									this->a.y() - this->b.y(), this->a.y() - ray.getOrigin().y(), ray.getDirection().y(),
									this->a.z() - this->b.z(), this->a.z() - ray.getOrigin().z(), ray.getDirection().z());
		float t = t_mat.determinant() / a_mat.determinant();
		float beta = b_mat.determinant() / a_mat.determinant();
		float gamma = c_mat.determinant() / a_mat.determinant();
		float alpha = 1 - beta - gamma;

		if (beta + gamma > 1 or beta < 0 or gamma < 0) {
			return false;
		}

		if (t >= tmin and t < hit.getT()) {
			Material* new_m = this->material;
			Vector2f new_uv = alpha * texCoords[0] + beta * texCoords[1] + gamma * texCoords[2];
			new_m->setUV(new_uv);
			Vector3f n = (alpha * normals[0] + beta * normals[1] + gamma * normals[2]).normalized();
			hit.set(t, new_m, n);
			return true;
		}

		return false;		
	}
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
	Vector3f a;
	Vector3f b;
	Vector3f c;
	Material* material;
};

#endif //TRIANGLE_H
