#pragma once

class CircleInfo;

class CircleCollider : public Collider
{
public:
	void SetRadius(float newRadius) { m_radius = newRadius; }
	float GetRadius() const { return m_radius; }

	bool IsCollide(const Collider* other) const override;

private:
	float m_radius = 1.0f;
};

