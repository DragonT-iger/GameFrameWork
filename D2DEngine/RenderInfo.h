#pragma once
#include <wrl/client.h>
#include <d2d1_3helper.h>

using Matrix3x2 = D2D1::Matrix3x2F;

struct RenderInfo {
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
	D2D1_RECT_F m_destRect;
	D2D1_RECT_F m_srcRect;
	bool isFlip;
	D2D1::Matrix3x2F worldTM;
};

enum ColliderType
{
	Rect = 1,
	Circle = 2,

};

struct RectInfo
{
	ColliderType type = ColliderType::Rect;
	
	float left;
	float top;
	float right;
	float bottom;
	D2D1::Matrix3x2F worldTM;
};

struct CircleInfo
{
	ColliderType type = ColliderType::Circle;

	float radius;
	D2D1::Matrix3x2F worldTM;
};
