#pragma once
class BoxCollider : public Collider
{
public:
	Vector2 GetSize() const { return size; }
	void SetSize(const Vector2& newSize) { size = newSize; }

	bool IsCollide(const Collider* other) const override;

private:
	Vector2 size = { 1, 1 };
};

