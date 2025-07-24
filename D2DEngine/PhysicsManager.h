#pragma once
#include <unordered_set>

class Collider;

struct CollisionPair
{
    Collider* a;
    Collider* b;

    bool operator==(const CollisionPair& other) const noexcept
    {
        return a == other.a && b == other.b;
    }
};

struct CollisionPairHash
{
    size_t operator()(const CollisionPair& p) const noexcept
    {
        auto low = std::min(p.a, p.b);
        auto high = std::max(p.a, p.b);
        return std::hash<Collider*>()(low) ^ (std::hash<Collider*>()(high) << 1);
    }
};

class PhysicsManager
{
public:
    static PhysicsManager& Instance()
    {
        static PhysicsManager Instance;
        return Instance;
    }

    void Step(float fixedDelta);

private:
    PhysicsManager() = default;
    ~PhysicsManager() = default;

    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;
    PhysicsManager(PhysicsManager&&) = delete;
    PhysicsManager& operator=(PhysicsManager&&) = delete;

    std::unordered_set<CollisionPair, CollisionPairHash> m_prevCollisions;
};
