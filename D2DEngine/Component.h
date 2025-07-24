/// ��¥ / �̸� / ��������
/// 2025-07-02 �ǿ�� ���ʹ��� �ۼ�
/// 2025-07-09 �ǿ�� MonoBehaviour ���� �ٷ� �����Ҽ� �ֵ��� GetOwner() �Լ� �߰� this�� �����ϰ� �غ����� �ߴµ� ��� ��ȯ ���� �߻�����
/// 2025-07-13 �ǿ�� ���ø� �ߺ� ���� , ��ȣ�� ���� �ذ� (inline , ���ӽ����̽� ��÷� ODR ���� �ذ�) �� MonoBehaviour���� GetComponent<T>()�� �ٷ� ȣ���Ҽ� �ְ� ��

#pragma once

/// <summary>
/// ������Ʈ Ŭ����
/// </summary>
class Component {
public:
	friend class GameObject;

	Component() = default;
    virtual ~Component() = default;

	GameObject* GetOwner() const { return m_owner; } // ���߿� protected�� �ٲܼ��� ���� wrapper �Լ��� ���̰� �ϱ� ���ؼ�

	template<typename T, typename... Args> inline
    T* AddComponent(Args&&... args);

    template<typename T> inline
    T* GetComponent() const;


protected:
    void SetOwner(GameObject* owner) { m_owner = owner; }

private:
    GameObject* m_owner = nullptr;
};

template<typename T, typename... Args> inline
T* Component::AddComponent(Args&&... args) {
    if (m_owner == nullptr) {
		assert(false && "Component must have an owner GameObject before adding a component. �Ƹ� �����ڿ��� �ʱ�ȭ �ؼ� �׷����� ������ �������� awake �ʱ�ȭ");
        return nullptr; 
    }
    return m_owner->GameObject::AddComponent<T>; // �̰� GameObject:: �����ָ� �����Ϸ��� ��ã�� ����ġ��
}

template<typename T> inline
T* Component::GetComponent() const {
    if (m_owner == nullptr) {
		assert(false && "Component must have an owner GameObject before getting a component. �Ƹ� �����ڿ��� �ʱ�ȭ �ؼ� �׷����� ������ �������� awake �ʱ�ȭ");
        return nullptr; 
    }
    return m_owner->GameObject::GetComponent<T>(); 
}
