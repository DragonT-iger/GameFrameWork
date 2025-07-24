#pragma once
class ExampleScene : public Scene
{
	void Awake() override;



	Transform* m_playerTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
	GameObject* m_Camera = nullptr;
	GameObject* m_player = nullptr;
	GameObject* m_player2 = nullptr;
};

