#pragma once
#include "Sphere.h"
#include "ObjID.h"
#include <functional>
class Collider {
public:

	void Initialize(ObjID objId, Sphere sphere, bool isWarp);

	ObjID GetObjID() const { return objID_; }
	Sphere GetSphere() const { return sphere_; }
	bool GetIsWarp() const { return isWarp_; }
	std::function<void(int)> GetFOnCollision() { return fOnCollision; }
	bool GetWarp() const { return true; }

	void SetObjID(ObjID objId) { objID_ = objId; }
	void SetSphere(Sphere sphere) { sphere_ = sphere; }
	void SetIsWarp(bool isWarp) { isWarp_ = isWarp; }
	void SetFOnCollision(std::function<void(int)> a) { fOnCollision = a; }

private:
	ObjID objID_;
	Sphere sphere_;
	std::function<void(int)> fOnCollision;
	bool isWarp_;
};
