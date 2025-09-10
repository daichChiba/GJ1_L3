#include "ColliderManager.h"

void ColliderManager::CheckAllCollisions() {
	for (Collider* collider : colliders_) {

		if (collider->GetObjID() == ObjID::player) {
			for (Collider* collider2 : colliders_) {
				if (collider2->GetObjID() == ObjID::ExitPortal) {
					if (CollisionDetection(collider->GetSphere(), collider2->GetSphere())) {
						collider->GetFOnCollision()(collider2->GetWarp());
					}
				}
			}
		}
	}
}
