/// 날짜 / 이름 / 수정내용
/// 2025-07-11 권용범 최초버전 작성
#pragma once

#include "GameObject.h"
#include "RenderInfo.h"

class Camera;

/// <summary>
/// 라이프 사이클을 지원하는 씬
/// </summary>
class Scene
{
public:

    enum class ScenePhase
    {
        None,
        Awake,
        Start,
        Update,
        FixedUpdate,
        LateUpdate,
        Render
    };

    explicit Scene(const std::wstring& name = L"NewScene") : m_name(name) {};
    virtual ~Scene() = default;

    GameObject* CreateGameObject(const std::wstring& name = L"GameObject");
	const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const { return m_gameObjects; }

	void Destroy(GameObject* object);

    // ---------- Lifecycle ----------
	virtual void Awake(); // 일단은 Awake 중간에서 GameObject를 생성하고 초기화할거기 떄문에 Awake만 virtual로 선언 장기적으로 봤을때 virtual이 없는게 맞음
    void Start();
    void Update(float deltaTime);
    void FixedUpdate(float fixedDelta);
    void LateUpdate(float deltaTime);
    void Render();

    void UnInitialize();

	// ---------- Render Queue ----------
    void SetRenderQ();

    // ---------- Misc ----------
    void SetActive(bool active) { m_active = active; }
    bool IsActive() const { return m_active; }


    // ---------- Camera ---------

    Camera* GetCamera() const { return m_Camera; }
    void    RegisterCamera(Camera* cam);
    void    UnregisterCamera(Camera* cam) { if (m_Camera == cam) m_Camera = nullptr; }
    D2D1::Matrix3x2F GetRenderTM(bool isFlip = false, float offsetX = 0.0f, float offsetY = 0.0f);


	// ---------- Event ----------
	virtual void OnEnable() {} 
    virtual	void OnDisable() {}

    virtual void OnResize(int width, int height) {}; // (필요한가?? 왜적었더라)

    const std::wstring& GetName() const { return m_name; }

protected:
    /* 지연 큐 적용 */
    void FlushPending();

private:
    bool                                            m_isIterating = false;
    std::vector<std::unique_ptr<GameObject>>        m_pendingAdd;
    std::vector<GameObject*>                        m_pendingDestroy;


    std::wstring                                                                        m_name;
    bool                                                                         m_active = true; // 아직 작동 안함
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    std::vector<RenderInfo>		                                        m_renderQ;
    Camera* m_Camera = nullptr;
    ScenePhase                                      m_phase = ScenePhase::None;
};