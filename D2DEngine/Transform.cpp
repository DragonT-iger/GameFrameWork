#include "pch.h"
#include "Transform.h"
#include "TMHelper.h"

Transform::~Transform()
{
	for (auto* child : m_children)
		child->m_parent = nullptr;
}

void Transform::AddChild(Transform* child)
{
	// �ڽ��� ���� ��ǥ�� �θ� ��ǥ��� ��ȯ
	// �ڽ��� ���� Ʈ ������ * �θ��� ���� Ʈ�������� ������� ���ϰ� ���� ����
	D2D1::Matrix3x2F chiledLocalTM = child->GetLocalMatrix();
	chiledLocalTM = chiledLocalTM * GetInverseWorldMatrix();

	auto M_noPivot = MYTM::RemovePivot(chiledLocalTM, child->GetPivotPoint());
	MYTM::DecomposeMatrix3x2(M_noPivot, child->m_position, child->m_rotation, child->m_scale);

	m_children.push_back(child);
}

void Transform::RemoveChild(Transform* child)
{
	// ����� ������.
	D2D1::Matrix3x2F chiledLocalTM = child->GetLocalMatrix();
	chiledLocalTM = chiledLocalTM * GetWorldMatrix();

	auto M_noPivot = MYTM::RemovePivot(chiledLocalTM, child->GetPivotPoint());
	MYTM::DecomposeMatrix3x2(M_noPivot, child->m_position, child->m_rotation, child->m_scale);

	m_children.erase(
		std::remove(m_children.begin(), m_children.end(), child),
		m_children.end()
	);
}

void Transform::SetDirty()
{

	m_dirty = true;

	for (auto* child : m_children) {
		child->SetDirty();
	}
}

void Transform::UpdateMatrices()
{
	const auto P = D2D1::Matrix3x2F::Translation(-m_pivot.x, -m_pivot.y);

	const auto S = D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y);

	const auto R = D2D1::Matrix3x2F::Rotation(m_rotation);

	const auto T1 = D2D1::Matrix3x2F::Translation(m_pivot.x, m_pivot.y);

	const auto T2 = D2D1::Matrix3x2F::Translation(m_position.x, m_position.y);

	m_matrixLocal = P * S * R * T1 * T2;
	//m_matrixLocal = S * R * T2;

	if (m_parent)
		m_matrixWorld = m_matrixLocal * m_parent->GetWorldMatrix();
	else
		m_matrixWorld = m_matrixLocal;

	m_dirty = false;
}

Vector2 Transform::GetForward() const
{
	float radian = MYHelper::DegreeToRadian(m_rotation);
	return { std::cosf(radian), std::sinf(radian) };
}

void Transform::SetParent(Transform* parent)
{
	assert(parent != this); // �ڱ� �ڽ��� �θ�� ������ �� ����
	assert(m_parent == nullptr); // DetachFromParent �� ���� ȣ���ϰ� �ٽ� SetParent�� ȣ���ؾ� ��

	m_parent = parent;
	m_parent->AddChild(this);

	SetDirty();
}

void Transform::DetachChildren()
{
	if (m_parent == nullptr) return;

	m_parent->RemoveChild(this);

	m_parent = nullptr;

	SetDirty();
}

const Matrix3x2& Transform::GetLocalMatrix()
{
	if (m_dirty) UpdateMatrices();

	return m_matrixLocal;
}

const Matrix3x2& Transform::GetWorldMatrix()
{
	if (m_dirty) UpdateMatrices();

	return m_matrixWorld;
}

Matrix3x2 Transform::GetInverseWorldMatrix()
{
	Matrix3x2 inv = GetWorldMatrix();
	inv.Invert();
	return inv;
}

Vector2 Transform::GetPivotPoint() const
{
	return m_pivot;
}

void Transform::SetPivotPreset(PivotPreset preset)
{

	switch (preset)
	{
	case PivotPreset::TopLeft:
		m_pivot = { 0.0f, 0.0f };
		break;
	case PivotPreset::TopRight:
		m_pivot = { m_spriteSize.width, 0.0f };
		break;
	case PivotPreset::BottomLeft:
		m_pivot = { 0.0f, -m_spriteSize.height };
		break;
	case PivotPreset::BottomRight:
		m_pivot = { m_spriteSize.width, -m_spriteSize.height };
		break;
	case PivotPreset::Center:
		m_pivot = { m_spriteSize.width * 0.5f, -(m_spriteSize.height * 0.5f) };
		break;
	}

	
}
