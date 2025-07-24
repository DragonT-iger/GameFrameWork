#pragma once
#include "MonoBehaviour.h"
#include "SpriteRenderer.h"
#include "AnimationClip.h"



class Animator : public MonoBehaviour
{
public:
	Animator() = default;
	virtual ~Animator() noexcept = default;

	virtual void Awake() override;

	virtual void Update(float deltaTime) override;

	void AddClip(const std::string& name, std::shared_ptr<AnimationClip> clip);

	void ChangeState(const std::string& name);

	void SetEntryState(const std::string& name);

	// ��������Ʈ ������ ��Ʈ�� �ٲٴ°Ŷ�(���� �ٲ� ��)
	// �ִϸ��̼� ������ �ٲ��ִ°� �־����
private:
	SpriteRenderer* m_sRenderer;
	std::unordered_map<std::string, std::shared_ptr<AnimationClip>> m_animations;
	std::shared_ptr<AnimationClip>																	m_curClip;
	std::vector<FrameData>																			m_frameDatas;
	std::vector<FrameData>::iterator																m_curFrame;
	float 																										m_duration = 0.0f;
};
