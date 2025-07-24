#pragma once
/// 날짜 / 이름 / 수정내용
enum class PivotPreset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

using Matrix3x2 = D2D1::Matrix3x2F;

/// <summary>
/// Transform 계층구조
/// </summary>
class Transform : public Component
{
public:
	friend class SpriteRenderer;

	Transform() = default; // 0 0 1 0 0 초기화
	~Transform(); // 혹시 모를 댕글링을 위해

	// 로컬
	const Vector2& GetPosition()					const { return m_position; }
		  float	   GetRotation()					const { return m_rotation; }
	const Vector2& GetScale()						const { return m_scale; }
	const Vector2& GetPivot()						const { return m_pivot; }

	void SetPosition(const Vector2& position)		{ m_position = position; m_dirty = true; }
	void SetRotation(float rotation)				{ m_rotation = rotation; m_dirty = true; }
	void SetScale(const Vector2& scale)				{ m_scale = scale	   ; m_dirty = true; }
	
	// 편의 메서드들
	void Translate(const Vector2& delta)			{ m_position.x += delta.x; m_position.y += delta.y; SetDirty(); }
	void Translate(const float x, const float y)	{ m_position.x += x; m_position.y += y; SetDirty(); }
	void Rotate(float degree)						{ m_rotation += degree; SetDirty(); }

	Vector2 GetForward() const;

	//계층구조 관련
	Transform* GetParent() const { return m_parent; }
	void SetParent(Transform* parent);
	void DetachChildren();

	const Matrix3x2& GetLocalMatrix();
	const Matrix3x2& GetWorldMatrix();
	Matrix3x2 GetInverseWorldMatrix();

	Vector2 GetPivotPoint() const;
	void SetPivotPreset(PivotPreset preset);

	void AddChild(Transform* child);
	void RemoveChild(Transform* child);

private:
	void SetDirty();
	void UpdateMatrices();
	void SetSpriteSize(const D2D1_SIZE_F& size) { m_spriteSize = size; SetDirty(); }

	bool m_dirty = false;

	Vector2 m_position = { 0.f , 0.f };
	float m_rotation = 0.f;
	Vector2 m_scale = { 1.f, 1.f };

	Transform* m_parent = nullptr;
	std::vector<Transform*> m_children = {};

	Matrix3x2 m_matrixLocal = D2D1::Matrix3x2F::Identity();
	Matrix3x2 m_matrixWorld = D2D1::Matrix3x2F::Identity();

	Vector2 m_pivot = { 0.f , 0.f };
	D2D1_SIZE_F m_spriteSize = { 0.f , 0.f };

	
};

