/// ��¥ / �̸� / ��������
/// 2025-07-13 �ǿ�� ���ʹ��� �ۼ�

#pragma once
#include "Scene.h"
class SceneManager {
public:
    static SceneManager& Instance() {
        static SceneManager instance;
        return instance;
    };

    // �� ���/Ȱ��ȭ
    void    RegisterScene(const std::wstring& name, std::unique_ptr<Scene> scene);
	Scene*  GetScene(const std::wstring& name) { return m_scenes[name].get(); } // ������ nullptr ��ȯ
    void    SetActiveScene(Scene* scene) { m_active = scene; }
    Scene*  GetActiveScene() const { return m_active; }
	void    LoadScene(const std::wstring& name);
    void    UnInitialize();

private:
    SceneManager() = default;
    ~SceneManager() = default;
    
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

    Scene* m_active = nullptr;
    std::unordered_map<std::wstring, std::unique_ptr<Scene>> m_scenes;
};


//   �ϴ� SceneManager�� ���� ���߿� ��ġ ����
inline GameObject* Instantiate(const std::wstring& name = L"GameObject")
{
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Instantiate: active scene is null!");
    return s->CreateGameObject(name);
}