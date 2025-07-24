#include "pch.h"
#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(float rhs) const
{
	return Vector2(x * rhs, y * rhs);	
}

Vector2 Vector2::operator/(float rhs) const
{
	return Vector2(x / rhs, y / rhs);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) const
{

	return x != rhs.x || y != rhs.y;
}

Vector2& Vector2::Scale(float scale)
{
	this->x * scale;
	this->y * scale;
	return *this;
}

Vector2& Vector2::Normalize()
{
	float length = std::sqrt(x * x + y * y);
	if (length != 0.0f)
	{
		x /= length;
		y /= length;
	}
	return *this;
}

Vector2 Vector2::Normalized() const
{
	float length = sqrt(x * x + y * y);
	if (length != 0.0f)
	{
		return Vector2(x / length, y / length);
	}
	return Vector2(0.0f, 0.0f);
}

float Vector2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

float Vector2::SqrMagnitude() const
{
	return x * x + y * y;
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	return (a - b).Magnitude();
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

Vector2 operator*(float lhs, const Vector2& rhs)
{
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}

const Vector2 Vector2::zero(0.f, 0.f);
const Vector2 Vector2::one(1.f, 1.f);
const Vector2 Vector2::up(0.f, 1.f);
const Vector2 Vector2::down(0.f, -1.f);
const Vector2 Vector2::left(-1.f, 0.f);
const Vector2 Vector2::right(1.f, 0.f);