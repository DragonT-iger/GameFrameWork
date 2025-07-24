#include "pch.h"
#include "DinoController.h"
#include "ResourceManager.h"

// ������������������������������������������������������������������������������������������
void DinoController::Awake()
{
    m_transform = GetComponent<Transform>();
    m_spriteRenderer = GetComponent<SpriteRenderer>();
    m_animator = GetComponent<Animator>();
	AddComponent<BoxCollider>();

    assert(m_transform && m_spriteRenderer && m_animator &&
        "DinoController::Awake - �ʼ� ������Ʈ�� ����!");
}

void DinoController::Start()
{
    // �ִϸ��̼� Ŭ�� �ε� & ���
    auto pandaEat = ResourceManager::Instance().LoadAnimationClip("PandaSpriteSheet.json", "TagEat");
    auto pandaWave = ResourceManager::Instance().LoadAnimationClip("PandaSpriteSheet.json", "TagWave");

    m_animator->AddClip("eat", pandaEat);
    m_animator->AddClip("wave", pandaWave);
    m_animator->SetEntryState("eat");

    // ���� ��ġ�� ���� �������� ����
    m_groundY = m_transform->GetPosition().y;
}

void DinoController::Update(float deltaTime)
{
    // �� ���� �̵� (�޸���)
    //m_transform->Translate(m_runSpeed * deltaTime, 0);

    // �� ���� �Է�
    if (m_isGrounded && Input.GetKeyDown(Keycode::SPACE))
    {
        m_velocityY = m_jumpVelocity;
        m_isGrounded = false;

        if (m_curAnim != "eat") {
            m_curAnim = "eat";
            m_animator->ChangeState("eat");
        }
    }

    // �� �߷� ���� & ���� ó��
    if (!m_isGrounded)
    {
        m_velocityY -= m_gravity * deltaTime;
        m_transform->Translate(0, m_velocityY * deltaTime);

        if (m_transform->GetPosition().y <= m_groundY) // ����
        {
            Vector2 pos = m_transform->GetPosition();
            pos.y = m_groundY;
            m_transform->SetPosition(pos);

            m_velocityY = 0.f;
            m_isGrounded = true;

            if (m_curAnim != "wave") {
                m_curAnim = "wave";
                m_animator->ChangeState("wave");
            }
        }
    }
}

void DinoController::OnTriggerEnter(Collider* other)
{
#ifdef _DEBUG
    cwout << L"[�浹] Dino hit �� " << other->GetOwner()->GetName() << std::endl;
#endif
    // TODO: ���ӿ��� ó�� (�� ��ȯ, UI ǥ�� ��)
}
