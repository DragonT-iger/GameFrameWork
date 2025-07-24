#pragma once
class Collider : public MonoBehaviour
{
public:
	virtual ~Collider() = default;

	void Awake() override { m_transform = GetComponent<Transform>(); }

	virtual bool IsCollide(const Collider* other) const = 0; // 이걸로 씬에서 LateUpdate에서 충돌 났는지 확인하면 됨

	Vector2	 GetOffset() const { return m_offset; }
	void	 SetOffset(const Vector2& newOffset) { m_offset = newOffset; }
	Vector2  GetCenter() const { return m_transform->GetPosition() + m_offset; }

protected:
	Transform* m_transform = nullptr;
	Vector2    m_offset = { 0,0 };
	bool       m_isTrigger = true; // 기본적으로 true로 왜냐하면 Rigidbody 구현이 아직 좀.. 그럼.. 일단은 Overlap
};

