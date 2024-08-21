#pragma once

#include "ColliderComponent.h"

// Comparator for sorting colliders
inline bool CompareByXY(Collider& a, Collider& b) {
    if (a.GetBoundingBox()->x == b.GetBoundingBox()->x) {
        return a.GetBoundingBox()->y < b.GetBoundingBox()->y;
    }
    return a.GetBoundingBox()->x < b.GetBoundingBox()->x;
}

class CollisionManager
{
public:
    // Singleton access method
    static CollisionManager& getInstance() {
        static CollisionManager instance;
        return instance;
    }

    // Add a collider
    void addCollider(const Collider& collider) {
        colliders.push_back(collider);
    }

    // Remove a collider (assuming we match by pointer for simplicity)
    void removeCollider(const Collider* collider) {
        auto it = std::remove_if(colliders.begin(), colliders.end(),
            [collider](const Collider& c) { return &c == collider; });
        colliders.erase(it, colliders.end());

    }

    std::vector<GameObject*> checkCollision(SDL_Rect* gameObject);

private:
    // Private constructor for singleton pattern
    CollisionManager(){}

    // Private destructor
    ~CollisionManager() {}

    // Prevent copy construction and assignment
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;

    // List of colliders
    std::vector<Collider> colliders;

    // A threshold value to decide when to stop checking further
    const int threshold = 3; // Example threshold value

    // Sort colliders
    void sortColliders() {
        std::sort(colliders.begin(), colliders.end(), CompareByXY);
    }
};


