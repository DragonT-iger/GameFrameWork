#include "pch.h"
#include "Camera.h"
#include "Scene.h"



Camera::~Camera()
{
    // ���� ��� �ִٸ� ��� ����
    if (Scene* s = SceneManager::Instance().GetActiveScene())
        s->UnregisterCamera(this);
}

void Camera::Awake()
{
    // Ȱ�� ���� �ڽ��� ���� ī�޶�� ���
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Camera::Awake - Active Scene is null!");
    s->RegisterCamera(this);
    SetScreenSize();
}

void Camera::LateUpdate(float deltaTime)
{
    auto* tr = GetComponent<Transform>();

	float w = static_cast<float>(m_screensize.right - m_screensize.left);
	float h = static_cast<float>(m_screensize.bottom - m_screensize.top);

    D2D1::Matrix3x2F invWorld = tr->GetWorldMatrix();
    invWorld.Invert();

    // ��(Scale) ����
    D2D1::Matrix3x2F zoomTM = D2D1::Matrix3x2F::Scale(m_zoom, -m_zoom);

    //ī�޶� ȭ�� �߾����� �̵�
    D2D1::Matrix3x2F moveCenterTM = D2D1::Matrix3x2F::Translation((w / 2), (h / 2));

    m_viewTM = invWorld * zoomTM * moveCenterTM ;
    // �����Բ��� ��� �Ǿ��ִ��� �̰� ��Ƽ�÷��� ���� �־�ߵ��� �𸣰ڳ�
    // �ϴ� ���� �̽� ����� �׶� ���� �׸� ���� ���ϰ� Ŀ������ ����
    // ��� ī�޶� �����̴� �����ϼ��� �ְ�
}

void Camera::SetScreenSize()
{
    ::GetClientRect(D2DRenderer::Instance().GetHandle(), &m_screensize);
}
