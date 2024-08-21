#include "CollisionManager.h"

std::vector<GameObject*> CollisionManager::checkCollision(SDL_Rect* gameObject)
{
    sortColliders();
    std::vector<GameObject*> nearbyObjects;
    int searchX = gameObject->x;
    int searchY = gameObject->y;

    // Loop through sorted colliders and check for proximity
    for (auto& obj : colliders) {
        int objX = obj.GetBoundingBox()->x;
        int objY = obj.GetBoundingBox()->y;

        if (std::abs(objX - searchX) <= threshold && std::abs(objY - searchY) <= threshold) {
            if (SDL_HasIntersection(obj.GetBoundingBox(), gameObject)) {
                nearbyObjects.push_back(obj.owner);
            }   
        }

        // As the list is sorted by x, we can break early if we've moved beyond the search radius
        if (objX > searchX + threshold) {
            break;
        }
    }

    return nearbyObjects;
}
