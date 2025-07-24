#pragma once
#include "Component.h"
/// ��¥ / �̸� / ��������
/// 2025-07-02 �ǿ�� ���ʹ��� �ۼ�

/// <summary>
/// ������Ʈ�� ���� �Ӽ� ����
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
