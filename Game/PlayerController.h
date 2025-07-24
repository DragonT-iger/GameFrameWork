// 예시코드
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake(); // 필요한 것만 오버라이드
    void Start() override;
    void Update(float deltaTime) override;
	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other) override;
	void OnTriggerExit(Collider* other) override;



    float m_xSpeed = 15.f; // x축 이동 속도
    float m_ySpeed = 15.f; // y축 이동 속도

private:
    std::string                 curAnim;
    Animator*       m_animator = nullptr;
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
