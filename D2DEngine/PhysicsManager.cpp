#include "pch.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "GameObject.h"

void PhysicsManager::Step(float fixedDelta)
{
    Scene* scene = SceneManager::Instance().GetActiveScene();
    if (!scene) return;

    std::unordered_set<CollisionPair, CollisionPairHash> currCollisions;

    std::vector<Collider*> colliders;
    colliders.reserve(scene->GetGameObjects().size());
    for (const auto& goPtr : scene->GetGameObjects())
    {
        GameObject* go = goPtr.get();
        if (!go->IsActive()) continue;

        if (auto* col = go->GetComponent<Collider>())
            colliders.push_back(col);
    }

    const size_t n = colliders.size();
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            Collider* a = colliders[i];
            Collider* b = colliders[j];

            if (!a->IsCollide(b)) continue;

            CollisionPair pair{ a, b };
            if (reinterpret_cast<uintptr_t>(a) > reinterpret_cast<uintptr_t>(b))
                std::swap(pair.a, pair.b);

            currCollisions.insert(pair);

            if (m_prevCollisions.find(pair) == m_prevCollisions.end())
            {
                a->GetOwner()->BroadcastTriggerEnter(b);
                b->GetOwner()->BroadcastTriggerEnter(a);
            }
            else
            {
                a->GetOwner()->BroadcastTriggerStay(b);
                b->GetOwner()->BroadcastTriggerStay(a);
            }
        }
    }

    for (const auto& pair : m_prevCollisions)
    {
        if (currCollisions.find(pair) != currCollisions.end())
            continue; 

        pair.a->GetOwner()->BroadcastTriggerExit(pair.b);
        pair.b->GetOwner()->BroadcastTriggerExit(pair.a);
    }

    m_prevCollisions.swap(currCollisions);
}
