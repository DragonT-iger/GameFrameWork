#pragma once
#include "MonoBehaviour.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Collider.h"

class DinoController : public MonoBehaviour
{
public:
    // 튜닝용 파라미터 ― 인스펙터에서 바로 만질 수 있게 public
    float m_runSpeed = 200.f;   // X 축 이동 속도 (px/s)
    float m_jumpVelocity = 550.f;   // 초기가속
    float m_gravity = 2000.f;  // 중력 가속도

    // ─────────────────────────────────────────────
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void OnTriggerEnter(Collider* other) override;

private:
    // 캐시된 컴포넌트
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
    Animator* m_animator = nullptr;

    // 점프/착지-상태
    float  m_velocityY = 0.f;
    float  m_groundY = 0.f;
    bool   m_isGrounded = true;

    std::string m_curAnim = "run";
};
