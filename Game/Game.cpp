#include "pch.h"
#include "Game.h"
#include "ExampleScene.h"

bool Game::Initialize()
{

	m_timer = std::make_unique<GameTimer>();

    m_timer->Reset();

	// ������ �ʱ�ȭ

	if (false == __super::Create(L"D2DEngine", L"D2DEngine", 1920, 1080))
	{
		return false;
	}

    // ������ �ʱ�ȭ

	D2DRenderer::Instance().Initialize(static_cast<HWND>(GetHandle()));
    
    //���ҽ� �Ŵ��� ����
    ResourceManager::Instance().SetResourcePath(std::filesystem::current_path() / "Assets");
    ResourceManager::Instance().LoadPath();


    // �� ó�� �� ����� �ε��ϴ¹�
	SceneManager::Instance().Instance().Instance().Instance().Instance().RegisterScene(L"MainScene", std::make_unique<ExampleScene>());

	
    

    // ���� �� �����Ͱ� �����Ǳ� ���̶� Instantiate ����

    SceneManager::Instance().LoadScene(L"MainScene");

	return true;
}

void Game::Run()
{
    MSG msg = { 0 };

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!InputManager::Instance().OnHandleMessage(msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            m_timer->Tick();
            LifeCycle(m_timer->DeltaTime()); 
        }
    }
}

void Game::LifeCycle(float deltaTime)
{

	static float elapsedTime = 0.0f;
    static float fixedDeltaTime = 0.02f;
    
	elapsedTime += deltaTime;

    Scene* scene = SceneManager::Instance().GetActiveScene();

	D2DRenderer::Instance().RenderBegin();

    if (scene && scene->IsActive())
    {
        while(elapsedTime >= fixedDeltaTime)
        {
            scene->FixedUpdate(fixedDeltaTime);
            elapsedTime -= fixedDeltaTime;
		}

        scene->Update(deltaTime);

		scene->LateUpdate(deltaTime);

        scene->Render();
	}

    D2DRenderer::Instance().RenderEnd();
}

void Game::Release()
{
    m_timer = nullptr;
    __super::Destroy();
}

void Game::UpdateTime()
{
    assert(m_timer != nullptr && "Ÿ�̸Ӱ� �������� �ʽ��ϴ�!" );

    m_timer->Tick();
}

void Game::OnResize(int width, int height)
{
    __super::OnResize(width, height);
    /*Scene* scene = SceneManager::Instance().GetActiveScene();
    scene->OnResize(width , height);*/
}

void Game::OnClose()
{
	SceneManager::Instance().UnInitialize();
	ResourceManager::Instance().Uninitialize();
    D2DRenderer::Instance().Uninitialize();
}
