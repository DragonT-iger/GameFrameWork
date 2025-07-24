#pragma once
#include "MonoBehaviour.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Collider.h"

class DinoController : public MonoBehaviour
{
public:
    // Ʃ�׿� �Ķ���� �� �ν����Ϳ��� �ٷ� ���� �� �ְ� public
    float m_runSpeed = 200.f;   // X �� �̵� �ӵ� (px/s)
    float m_jumpVelocity = 550.f;   // �ʱⰡ��
    float m_gravity = 2000.f;  // �߷� ���ӵ�

    // ������������������������������������������������������������������������������������������
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void OnTriggerEnter(Collider* other) override;

private:
    // ĳ�õ� ������Ʈ
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
    Animator* m_animator = nullptr;

    // ����/����-����
    float  m_velocityY = 0.f;
    float  m_groundY = 0.f;
    bool   m_isGrounded = true;

    std::string m_curAnim = "run";
};
