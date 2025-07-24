#pragma once
#include "Component.h"
/// 날짜 / 이름 / 수정내용
/// 2025-07-02 권용범 최초버전 작성

/// <summary>
/// 컴포넌트를 껐다 켤수 있음
/// </summary>
class Behaviour : public Component {
public:
    Behaviour() : m_enabled(true) {}
    virtual ~Behaviour() = default;

    void Enable() { m_enabled = true; }
    void Disable() { m_enabled = false; }
    void SetEnabled(bool state) { m_enabled = state; }
    bool IsEnabled() const { return m_enabled; }

private:
    bool m_enabled;
};
