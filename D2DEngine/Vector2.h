#pragma once

/// ��¥ / �̸� / ��������
/// 2025-07-02 �ǿ�� ���ʹ��� �ۼ�'
/// 2025-07-08 �ǿ�� Get, Set �Լ� �߰�

/// <summary>
/// Unity Like ���� Ŭ����
/// </summary>
class Vector2
{
public:

	Vector2() : x(0.f), y(0.f) {}
	Vector2(float x, float y) : x(x), y(y) {}
	// ������ �����ε�

	Vector2 operator+(const Vector2& rhs) const; // R-value ����
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(float rhs) const;
	friend Vector2 operator*(float lhs, const Vector2& rhs); //  (float) * (Vector2) �϶� ó��
	Vector2 operator/(float rhs) const; // ������� ���� �ݴ�� �����°� ���� ���� ������


	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator*=(const Vector2& rhs);
	Vector2& operator/=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs); // float ���ϱ�� �Ǽ��ұ�� �׳� ���� ������

	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;

	Vector2& Scale(float scale);

	/// <summary>
	/// ������ �������ͷ� ����
	/// </summary>
	Vector2& Normalize();


	/// <summary>
	/// �������͸� ������
	/// </summary>
	Vector2 Normalized() const; // ����Ƽ�� n���� ���������� �ϴ� �������� ���� �빮�ڷ�


	float Magnitude() const;
	float SqrMagnitude() const;


	//static �� ���� �Լ��� �ν��Ͻ��� ���� ���� Vector2::Dot �̷������� ���� ���� ����� ����

	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static float Distance(const Vector2& a, const Vector2& b);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	//static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal); // �ʿ��ҋ� ����
	// 
	// SqrMagnitude 

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 left;
	static const Vector2 right;

	// get, set �Լ�
	float GetX() const { return x; }
	float GetY() const { return y; }

	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	
	float x;
	float y;
};

