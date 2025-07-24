#pragma once
class Collider : public MonoBehaviour
{
public:
	virtual ~Collider() = default;

	void Awake() override { m_transform = GetComponent<Transform>(); }

	virtual bool IsCollide(const Collider* other) const = 0; // �̰ɷ� ������ LateUpdate���� �浹 ������ Ȯ���ϸ� ��

	Vector2	 GetOffset() const { return m_offset; }
	void	 SetOffset(const Vector2& newOffset) { m_offset = newOffset; }
	Vector2  GetCenter() const { return m_transform->GetPosition() + m_offset; }

protected:
	Transform* m_transform = nullptr;
	Vector2    m_offset = { 0,0 };
	bool       m_isTrigger = true; // �⺻������ true�� �ֳ��ϸ� Rigidbody ������ ���� ��.. �׷�.. �ϴ��� Overlap
};

