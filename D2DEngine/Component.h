/// 날짜 / 이름 / 수정내용
/// 2025-07-02 권용범 최초버전 작성
/// 2025-07-09 권용범 MonoBehaviour 에서 바로 접근할수 있도록 GetOwner() 함수 추가 this로 접근하게 해보려고도 했는데 헤더 순환 참조 발생했음
/// 2025-07-13 권용범 템플릿 중복 참조 , 모호한 문제 해결 (inline , 네임스페이스 명시로 ODR 문제 해결) 즉 MonoBehaviour에서 GetComponent<T>()를 바로 호출할수 있게 됨

#pragma once

/// <summary>
/// 컴포넌트 클래스
/// </summary>
class Component {
public:
	friend class GameObject;

	Component() = default;
    virtual ~Component() = default;

	GameObject* GetOwner() const { return m_owner; } // 나중에 protected로 바꿀수도 있음 wrapper 함수만 보이게 하기 위해서

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
		assert(false && "Component must have an owner GameObject before adding a component. 아마 생성자에서 초기화 해서 그럴거임 생성자 쓰지말고 awake 초기화");
        return nullptr; 
    }
    return m_owner->GameObject::AddComponent<T>; // 이거 GameObject:: 안해주면 컴파일러가 못찾네 개빡치내
}

template<typename T> inline
T* Component::GetComponent() const {
    if (m_owner == nullptr) {
		assert(false && "Component must have an owner GameObject before getting a component. 아마 생성자에서 초기화 해서 그럴거임 생성자 쓰지말고 awake 초기화");
        return nullptr; 
    }
    return m_owner->GameObject::GetComponent<T>(); 
}
