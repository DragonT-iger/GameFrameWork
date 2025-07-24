#include "pch.h"
#include "Scene.h"



// -----------------------------------------------------------------------------
// GameObject 생성 / 파괴
// -----------------------------------------------------------------------------

GameObject* Scene::CreateGameObject(const std::wstring& name)
{
    auto go = std::make_unique<GameObject>(name);
    GameObject* raw = go.get();

    if (m_isIterating)
        m_pendingAdd.emplace_back(std::move(go));
    else
        m_gameObjects.emplace_back(std::move(go));
    return raw;
}

void Scene::Destroy(GameObject* object)
{
    if (object)
        m_pendingDestroy.push_back(object);
}

// -----------------------------------------------------------------------------
// Lifecycle dispatch
// -----------------------------------------------------------------------------

void Scene::Awake()
{
    //if (!m_active) return;
    m_phase = ScenePhase::Awake;

    GameObject* camera = CreateGameObject(L"Camera");
    camera->AddComponent<Camera>();

    camera->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

	// 카메라는 기본적으로 씬에 등록

    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->Awake();
    m_isIterating = false;
    FlushPending();
}

void Scene::Start()
{
    //if (!m_active) return;
	m_phase = ScenePhase::Start;
    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->Start();
    m_isIterating = false;
    FlushPending();
}

void Scene::Update(float deltaTime)
{
    //if (!m_active) return;
	m_phase = ScenePhase::Update;
    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->Update(deltaTime);
    m_isIterating = false;
    FlushPending();
}

void Scene::FixedUpdate(float fixedDelta)
{
    //if (!m_active) return;

	m_phase = ScenePhase::FixedUpdate;

    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->FixedUpdate(fixedDelta);
    m_isIterating = false;
    FlushPending();

    PhysicsManager::Instance().Step(fixedDelta);

    
}

void Scene::LateUpdate(float deltaTime)
{
    //if (!m_active) return;
	m_phase = ScenePhase::LateUpdate;
    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->LateUpdate(deltaTime);
    m_isIterating = false;
    FlushPending();

    

	/*if (!cam) std::cout << "카메라가 없음" << std::endl;
	else std::cout << "카메라가 있음" << std::endl;*/

    //assert(cam && "카메라 없음"); 카메라는 일단 없어도 되잖아?


    // 렌더링 로직은 여기에


    /* example
    

    const auto& view = cam->GetViewTM();
    for (auto& go : m_gameObjects)
        if (auto* sr = go->GetComponent<SpriteRenderer>())
            sr->Render(r, view);
    
    
    */
}

void Scene::Render()
{

	//if (!m_active) return;
	m_phase = ScenePhase::Render;

    SetRenderQ();

	auto* cam = GetCamera();

	D2D1::Matrix3x2F viewTM = cam->GetViewTM();

    for(auto& info : m_renderQ)
    {
        D2D1::Matrix3x2F renderTM = GetRenderTM(info.isFlip);
        D2D1::Matrix3x2F mWV = renderTM * info.worldTM * viewTM;
        D2DRenderer::Instance().SetTransform(mWV);
        //D2DRenderer::Instance().DrawCircle(0, 0, info.radius, RGB(255, 0, 0));
        D2DRenderer::Instance().DrawBitmap(info.m_bitmap.Get(), info.m_destRect, info.m_srcRect);
	}

	m_renderQ.clear();
}

void Scene::UnInitialize()
{
    m_gameObjects.clear();
}

void Scene::SetRenderQ()
{
    for (auto& obj : m_gameObjects)
    {
        const auto& spRender = obj->GetComponent<SpriteRenderer>();
        if (spRender)
        {
            m_renderQ.push_back(spRender->GetRenderInfo());
        }
    }
}

void Scene::RegisterCamera(Camera* cam)
{
    if (m_Camera) {
        assert(false && "씬에 카메라가 두대일수 없슴");
    }

    m_Camera = cam;
}

D2D1::Matrix3x2F Scene::GetRenderTM(bool isFlip, float offsetX, float offsetY)
{
    float scaleX = isFlip ? -1.0f : 1.0f;

    offsetX = isFlip ? -offsetX : offsetX;
    offsetY = -offsetY;

    return D2D1::Matrix3x2F::Scale(scaleX, -1.0f) * D2D1::Matrix3x2F::Translation(offsetX, offsetY);
}

void Scene::FlushPending()
{
    std::vector<GameObject*> added;
    for (auto& up : m_pendingAdd)
    {
        GameObject* raw = up.get();
        m_gameObjects.emplace_back(std::move(up));
        added.push_back(raw);
    }
    m_pendingAdd.clear();

    if (m_phase == ScenePhase::Awake)
        for (auto* obj : added)
            obj->Awake();
    else if (m_phase == ScenePhase::Start)
        for (auto* obj : added)
            obj->Start();

    for (auto* dead : m_pendingDestroy)
    {
        auto it = std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
            [dead](auto& up) { return up.get() == dead; });
        m_gameObjects.erase(it, m_gameObjects.end());
    }
    m_pendingDestroy.clear();
}
