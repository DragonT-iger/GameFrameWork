#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::SetSize(float width, float height)
{
	if(m_transform == nullptr)
	{
		assert(false && "트랜스폼이 초기화되지 않았음");
		return;
	}
	m_renderInfo.m_destRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

	m_transform->SetSpriteSize(D2D1::SizeF(width, height)); // Transform 에서 스프라이트 크기 설정
}

RenderInfo& SpriteRenderer::GetRenderInfo()
{
	m_renderInfo.worldTM = m_transform->GetWorldMatrix();

	return m_renderInfo;
}

void SpriteRenderer::Awake()
{
	m_transform = GetOwner()->GetComponent<Transform>();
}
