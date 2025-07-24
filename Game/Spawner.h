#pragma once

#include <random>

class Spawner : public MonoBehaviour
{
public:
    void Awake() override { ScheduleNext(); }

    void Update(float deltaTime) override
    {
        m_elapsed += deltaTime;
        if (m_elapsed >= m_next)
        {
            Spawn();
            ScheduleNext();
        }
    }

private:
    void Spawn()
    {
        GameObject* obs = Instantiate(L"Cactus");
        //obs->AddComponent<SpriteRenderer>();      // 비어 있어도 OK
        //obs->AddComponent<BoxCollider>();
        //obs->AddComponent<ObstacleController>();
        //obs->GetComponent<Transform>()->SetPosition({ 1000.f, 300.f });
    }

    void ScheduleNext()
    {
        m_elapsed = 0.f;
        m_next = std::uniform_real_distribution<float>(1.0f, 2.2f)(m_rng);
    }

    float                       m_elapsed = 0.f;
    float                       m_next = 1.f;
    std::mt19937                m_rng{ std::random_device{}() };
};


