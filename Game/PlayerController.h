// �����ڵ�
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake(); // �ʿ��� �͸� �������̵�
    void Start() override;
    void Update(float deltaTime) override;
	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other) override;
	void OnTriggerExit(Collider* other) override;



    float m_xSpeed = 15.f; // x�� �̵� �ӵ�
    float m_ySpeed = 15.f; // y�� �̵� �ӵ�

private:
    std::string                 curAnim;
    Animator*       m_animator = nullptr;
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
