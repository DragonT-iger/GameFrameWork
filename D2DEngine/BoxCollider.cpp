#include "pch.h"
#include "BoxCollider.h"

bool BoxCollider::IsCollide(const Collider* other) const
{
	// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();
	}
	return true;
	return false;
}
