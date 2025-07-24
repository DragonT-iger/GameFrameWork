#pragma once

/// 날짜 / 이름 / 수정내용
/// 2025-07-04 권용범 최초버전 작성
/// 2025-07-07 권용범 Transform 특수화
/// 2025-07-10 권용범 라이프사이클 + args + 중복 컴포넌트 추가 방지 및 MonoBehaviour 형식 저장에서 
///                  Component 저장으로 변경해서 Behaviour 도 저장 가능하게 (BoxCollider Behaviour로 저장가능하게) 

/// <summary>
/// Unity Like GameObject Class
/// </summary>
class GameObject
{
public:
    GameObject(const std::wstring& name = L"GameObject");

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template<typename T>
    T* GetComponent() const;

    void RemoveComponent(Component* component);

    void SetActive(bool active);
    bool IsActive() const;

    // 씬에 마지막에 넣고 돌릴꺼임 그냥 호출하지 말기 일단 나중에 씬이랑 friend 걸거나 해야지 Mono에서는 못쓰게

    void Awake();
    void Start();
    void Update(float deltaTime);
    void FixedUpdate(float fixedDeltaTime);
    void LateUpdate(float deltaTime);


	void BroadcastTriggerEnter(Collider* other);
	void BroadcastTriggerStay(Collider* other);
	void BroadcastTriggerExit(Collider* other);

    //getname

	const std::wstring& GetName() const { return m_name; }
    void SetName(const std::wstring& name) { m_name = name; }

	const std::wstring& GetTag() const { return m_tag; }
    void SetTag(const std::wstring& tag) { m_tag = tag; }

private:
    void FlushPending();

    std::wstring                                  m_name;
	std::wstring                                  m_tag = L"Untagged";
    bool                                          m_active = true;
    std::vector<std::unique_ptr<Component>>       m_components;
    std::unique_ptr<Transform>                    m_transform;

    bool                                          m_isIterating = false;
    std::vector<std::unique_ptr<Component>>       m_pendingAdd;
    std::vector<Component*>                       m_pendingRemove;
};

//템플릿은 cpp로 못옮겨

// 리턴 raw로 주니까 delete 절대하지마셈 나중에 shared_ptr 로 해도 되겠네 이거
template<typename T, typename... Args> inline // inline은 ODR 방지용
T* GameObject::AddComponent(Args&&... args)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    // 컴파일 타임 타입 체크

    if (T* existing = this->GetComponent<T>()) 
    {
        // 유니티에서는 이게 되긴 하는데 실수할 여지가 너무 많아서 처리했음
        cwout << L"[경고] " << typeid(T).name()
            << L" 컴포넌트가 이미 존재합니다. 중복 추가를 건너뛰고 기존거 리턴함.\n";
        // 디버그용으로 완전 차단하려면 assert 삽입
        // assert(false && "Duplicate component!");
        return existing; 
    }

    auto comp = std::make_unique<T>(std::forward<Args>(args)...);
    T* raw = comp.get();

    raw->SetOwner(this);

    if (m_isIterating)
        m_pendingAdd.emplace_back(std::move(comp));
    else
        m_components.emplace_back(std::move(comp));
    return raw;
}
template<> inline
Transform* GameObject::AddComponent<Transform>() {
    if (m_transform)
    {
        cwout << L"[GameObject] Transform already exists\n";
        assert(false && "Duplicate Transform on GameObject");
        return m_transform.get();
    }
    m_transform = std::make_unique<Transform>();
	Transform* raw = m_transform.get();

	raw->SetOwner(this);

    return m_transform.get();
}

template<typename T> inline
T* GameObject::GetComponent() const
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    // 컴파일 타임 타입 체크

    for (auto& c : m_components)
        if (auto casted = dynamic_cast<T*>(c.get()))            return casted;
    return nullptr;
}
template<> inline
Transform* GameObject::GetComponent<Transform>() const
{
    return m_transform.get();
}