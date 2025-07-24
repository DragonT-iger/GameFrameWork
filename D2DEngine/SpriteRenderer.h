#pragma once  
#include "MonoBehaviour.h"
#include "RenderInfo.h"
#include "Transform.h"


class SpriteRenderer : public MonoBehaviour
{
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;

	void Awake() override;

	void SetBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap1>& bitmap) {
		m_renderInfo.m_bitmap = bitmap;
	}  //�⺻ ��������Ʈ ����

	void SetSize(float width, float height);

	void SetSrcRect(const D2D1_RECT_F& rect) {
		m_renderInfo.m_srcRect = rect;
		m_renderInfo.m_destRect = { -(rect.right - rect.left) / 2, -(rect.bottom - rect.top) / 2, (rect.right - rect.left) / 2 , (rect.bottom - rect.top) / 2 };
	}

	void SetFlip(bool flip) { m_renderInfo.isFlip = flip; }
	bool IsFlip() { return m_renderInfo.isFlip; }

	RenderInfo& GetRenderInfo();

private:
	Transform*									m_transform = nullptr;
	RenderInfo                                                  m_renderInfo; //������ ����, �ִϸ��̼��̸� �ִϸ��̼� ������ ��
};
