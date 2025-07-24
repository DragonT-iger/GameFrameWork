#include "pch.h"
#include "CircleCollider.h"

bool CircleCollider::IsCollide(const Collider* other) const
{
		// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
		//circle->GetCenter() + circle->GetRadius();

		constexpr float PPM = 50.0f;
		//std::cout << circle->GetCenter().x << " " << circle->GetCenter().y << " " << circle->m_radius * PPM << " " << GetCenter().x << " " << GetCenter().y << " " << m_radius * PPM << std::endl;


		
		
		
		float length = abs(sqrt((pow(GetCenter().x - circle->GetCenter().x, 2) + pow(GetCenter().y - circle->GetCenter().y, 2))));



		//std::cout << circle->GetRadius() + m_radius << " " << length << std::endl;
		if((circle->GetRadius() + m_radius) * PPM >= length) // ���� ������ �� �ϴ�
		{
			return true;
		}



		//GetOwner()->

		return false;
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();

	}


	//���ǵ��� ���� �������� �浹���� ����
	return false;
}
