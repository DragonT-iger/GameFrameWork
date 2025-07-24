#include "pch.h"
#include "DinoRunScene.h"
#include "DinoController.h"
#include "Spawner.h"

void DinoRunScene::Awake()
{
    if(!IsActive())
		return;



    GameObject* dino = Instantiate(L"Dino");
    SpriteRenderer* sr = dino->AddComponent<SpriteRenderer>();


    dino->AddComponent<BoxCollider>();
    dino->AddComponent<DinoController>();
	dino->AddComponent<Animator>();
    dino->GetComponent<Transform>()->SetPosition({ -300.f, -300.f }); // ¹Ù´Ú¼³Á¤µµµÊ Y = 300

    GameObject* spawner = Instantiate(L"Spawner");
    spawner->AddComponent<Spawner>();

    Scene::Awake();
}
