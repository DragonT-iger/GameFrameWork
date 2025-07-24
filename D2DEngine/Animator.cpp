#include "pch.h"
#include "GameObject.h"
#include "Animator.h"


void Animator::Awake()
{
	m_sRenderer = GetOwner()->GetComponent<SpriteRenderer>();
}

void Animator::Update(float deltaTime)
{
	if (m_curFrame->duration <= m_duration)
	{
		if (++m_curFrame == m_frameDatas.end())
			m_curFrame = m_frameDatas.begin();

		m_sRenderer->SetSrcRect(m_curFrame->ToRectF());

		m_duration = 0.0f;
	}

	m_duration += deltaTime;
}

void Animator::ChangeState(const std::string& name)
{
#ifdef _DEBUG
	if (m_animations.find(name) == m_animations.end())
	{
		throw std::runtime_error("Animator::ChangeState: Animation clip not found: " + name);
	}
#endif
	m_curClip = m_animations.at(name);

	m_sRenderer->SetBitmap(m_curClip->GetBitmap());
	m_frameDatas = m_curClip->GetFrames();
	m_curFrame = m_frameDatas.begin();
	m_sRenderer->SetSrcRect(m_curFrame->ToRectF());
}

void Animator::SetEntryState(const std::string& name)
{
	ChangeState(name);
}

void Animator::AddClip(const std::string& name, std::shared_ptr<AnimationClip> clip)
{
	m_animations.emplace(name, clip);
}
