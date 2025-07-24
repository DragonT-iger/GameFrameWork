#include "pch.h"
#include "PlayerController.h"


void PlayerController::Awake()
{
    m_transform = GetComponent<Transform>();
    m_spriteRenderer = GetComponent<SpriteRenderer>();
    m_animator = GetComponent<Animator>();

    WRL::ComPtr<ID2D1Bitmap1> bitmap;
    //D2DRenderer::Instance().CreateBitmapFromFile(L"Assets/Player.png", *bitmap.GetAddressOf());

	GameObject* a = Instantiate(L"aa");
	SpriteRenderer* spriteRenderer = a->AddComponent<SpriteRenderer>();

	spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("Player.png"));


    //m_spriteRenderer->SetBitmap(bitmap);
    //m_spriteRenderer->SetSize(64.f, 64.f);
}

void  PlayerController::Start()
{
	auto pandaEat = ResourceManager::Instance().LoadAnimationClip("PandaSpriteSheet.json", "TagEat");
	auto pandaWave = ResourceManager::Instance().LoadAnimationClip("PandaSpriteSheet.json", "TagWave");


    m_animator->AddClip("eat", pandaEat);
    m_animator->AddClip("wave", pandaWave);
    m_animator->SetEntryState("eat");
}


void PlayerController::Update(float deltatime)
{
	/*m_transform->Translate(m_xSpeed * deltatime, m_ySpeed * deltatime);
	m_transform->Rotate(0.10f * deltatime);*/
	if (Input.GetKeyDown(Keycode::UP))
	{
		m_transform->Translate(0, m_ySpeed * deltatime);
		if (curAnim != "wave")
		{
			curAnim = "wave";
			m_animator->ChangeState("wave");
		}
	}
	else if (Input.GetKeyDown(Keycode::DOWN))
	{
		m_transform->Translate(0, -m_ySpeed * deltatime);
	}
	else if (Input.GetKeyDown(Keycode::RIGHT))
	{
		if (m_spriteRenderer->IsFlip())
			m_spriteRenderer->SetFlip(false);
		m_transform->Translate(m_xSpeed * deltatime, 0);
	}
	else if (Input.GetKeyDown(Keycode::LEFT))
	{
		if(!m_spriteRenderer->IsFlip())
			m_spriteRenderer->SetFlip(true);
		m_transform->Translate(-m_xSpeed * deltatime, 0);
	}
	else
	{
		if (curAnim != "eat")
		{
			curAnim = "eat";
			m_animator->ChangeState("eat");
		}
	}

}

void PlayerController::OnTriggerEnter(Collider* other)
{
    //std::cout << "PlayerController::OnTriggerEnter: " << std::endl;


#ifdef _DEBUG
     cwout << "PlayerController::OnTriggerEnter: " << other->GetOwner()->GetName() << std::endl;
#endif // !__DEBUG

}

void PlayerController::OnTriggerStay(Collider* other)
{
	#ifdef _DEBUG
	cwout << "PlayerController::OnTriggerStay: " << other->GetOwner()->GetName() << std::endl;
#endif // !__DEBUG
}

void PlayerController::OnTriggerExit(Collider* other)
{
	#ifdef _DEBUG
	cwout << "PlayerController::OnTriggerExit: " << other->GetOwner()->GetName() << std::endl;
#endif // !__DEBUG
}
