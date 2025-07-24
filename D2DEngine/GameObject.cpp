#include "pch.h"

#include "GameObject.h"
#include "MonoBehaviour.h"
#include "Transform.h"

GameObject::GameObject(const std::wstring& name)
    : m_name{ name }, m_active{ true } {
    this->AddComponent<Transform>();
}

void GameObject::RemoveComponent(Component* component)
{
    if (!component) return;

    if (m_isIterating)
        m_pendingRemove.push_back(component);
    else {
        auto it = std::remove_if(m_components.begin(), m_components.end(),
            [component](auto& up) { return up.get() == component; });
        m_components.erase(it, m_components.end());
    }
}

/* Activation -------------------------------------------------- */
void GameObject::SetActive(bool active) { m_active = active; }
bool GameObject::IsActive() const { return m_active; }



/* Lifecycle Methods -------------------------------------------- */

void GameObject::Awake() {
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            mb->Awake();
    m_isIterating = false;
    FlushPending();
}

void GameObject::Start() {
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            mb->Start();
    m_isIterating = false;
    FlushPending();
}

void GameObject::Update(float deltaTime) {
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            mb->Update(deltaTime);
    m_isIterating = false;
    FlushPending();
}

void GameObject::FixedUpdate(float fixedDeltaTime) {
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            mb->FixedUpdate(fixedDeltaTime);
    m_isIterating = false;
    FlushPending();
}

void GameObject::LateUpdate(float deltaTime) {
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            mb->LateUpdate(deltaTime);
    m_isIterating = false;
    FlushPending();
}

void GameObject::BroadcastTriggerEnter(Collider* other)
{
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->OnTriggerEnter(other);
        }
	}
}

void GameObject::BroadcastTriggerStay(Collider* other)
{
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->OnTriggerStay(other);
        }
	}
}

void GameObject::BroadcastTriggerExit(Collider* other)
{
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->OnTriggerExit(other);
        }
	}
}
void GameObject::FlushPending()
{
    /* 1) Add */
    for (auto& up : m_pendingAdd)
        m_components.emplace_back(std::move(up));
    m_pendingAdd.clear();

    /* 2) Remove */
    for (auto* dead : m_pendingRemove)
    {
        auto it = std::remove_if(m_components.begin(), m_components.end(),
            [dead](auto& up) { return up.get() == dead; });
        m_components.erase(it, m_components.end());
    }
    m_pendingRemove.clear();
}
