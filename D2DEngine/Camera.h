#pragma once


/// <summary>
/// ¾À´ç 1 ´ë Ä«¸Þ¶ó ÄÄÆ÷³ÍÆ®
/// </summary>
class D2DRenderer;

class Camera : public MonoBehaviour
{
public:
    Camera() = default;                                    
    virtual ~Camera();

    void  SetZoom(float zoom) { m_zoom = zoom; }
    float GetZoom()        const { return m_zoom; }

    const D2D1::Matrix3x2F& GetViewTM() const { return m_viewTM; }

    void LateUpdate(float deltaTime) override;

    void SetScreenSize();

protected:
    void Awake() override;                      

private:
    Camera* s_main = nullptr; 
    RECT            m_screensize;
    D2D1::Matrix3x2F m_viewTM = D2D1::Matrix3x2F::Identity();
    float            m_zoom = 1.f;
};

