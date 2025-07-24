#pragma once
#include "Component.h"

/*
일단 교수님 렌더러 코드 옮겨둠

-구조 변경해야됨

*/

class D2DRenderer : public MonoBehaviour {
public:

    static D2DRenderer& Instance() {
		static D2DRenderer instance;
		return instance;
    }

    D2DRenderer(const D2DRenderer&) = delete;
    D2DRenderer& operator=(const D2DRenderer&) = delete;
	D2DRenderer(D2DRenderer&&) = delete;
	D2DRenderer& operator=(D2DRenderer&&) = delete;

    D2DRenderer() = default;

    ~D2DRenderer() { Uninitialize(); }

    void Initialize(HWND hwnd);

    void Uninitialize();

    void Resize(UINT width, UINT height);

    void DrawLine(float x1, float y1, float x2, float y2, const D2D1::ColorF& color);

	void DrawCircle(float x, float y, float radius, const D2D1::ColorF& color);

    void DrawRectangle(float left, float top, float right, float bottom, const D2D1::ColorF& color);

    void DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F dest);

    void DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F destRect, D2D1_RECT_F srcRect, float opacity = 1.0f);

    void DrawMessage(const wchar_t* text, float left, float top, float width, float height, const D2D1::ColorF& color);

    void SetTransform(const D2D1_MATRIX_3X2_F tm);

    void RenderBegin();

    void RenderEnd(bool bPresent = true);

    void Present();

    void CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1*& outBitmap);

    ID3D11Device* GetD3DDevice() const { return m_d3dDevice.Get(); }

    ID3D11DeviceContext* GetD3DContext() const { return m_d3dContext.Get(); }

    ID3D11RenderTargetView* GetD3DRenderTargetView() const { return m_d3dRenderTV.Get(); }

    HWND GetHandle() const { return m_hwnd; }

private:

    void CreateDeviceAndSwapChain(HWND hwnd);

    void CreateRenderTargets();

    void CreateWriteResource();

    void ReleaseRenderTargets();

private:
    HWND m_hwnd = nullptr;

    WRL::ComPtr<ID3D11Device>           m_d3dDevice;
    WRL::ComPtr<IDXGISwapChain1>        m_swapChain;

    WRL::ComPtr<ID3D11DeviceContext>    m_d3dContext;
    WRL::ComPtr<ID3D11RenderTargetView> m_d3dRenderTV; // D3D render target view

    WRL::ComPtr<ID2D1Bitmap1>           m_targetBitmap; // D2D render target bitmap
    WRL::ComPtr<ID2D1SolidColorBrush>   m_brush;
    WRL::ComPtr<ID2D1SolidColorBrush>   m_textBrush;
    WRL::ComPtr <IDWriteTextFormat>     m_textFormat;

    WRL::ComPtr<ID2D1Device7>           m_d2dDevice;
    WRL::ComPtr<ID2D1DeviceContext7>    m_d2dContext;

    WRL::ComPtr<IWICImagingFactory>     m_wicFactory;
};
