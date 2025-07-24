#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::SetSize(float width, float height)
{
	if(m_transform == nullptr)
	{
		assert(false && "Ʈ�������� �ʱ�ȭ���� �ʾ���");
		return;
	}
	m_renderInfo.m_destRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

	m_transform->SetSpriteSize(D2D1::SizeF(width, height)); // Transform ���� ��������Ʈ ũ�� ����
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
