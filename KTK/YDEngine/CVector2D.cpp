#include "CVector2D.h"
#include <cmath>

CVector2D CVector2D::operator+(const CVector2D& v)
{
	CVector2D r;
	r.x = this->x + v.x;
	r.y = this->y + v.y;
	return r;
}

CVector2D CVector2D::operator-(const CVector2D& v)
{
	CVector2D r;
	r.x = this->x - v.x;
	r.y = this->y - v.y;
	return r;
}

CVector2D CVector2D::operator*(const float& f)
{
	CVector2D r;
	r.x = this->x * f;
	r.y = this->y * f;
	return r;
}

CVector2D CVector2D::operator/(const float& f)
{
	CVector2D r;
	r.x = this->x / f;
	r.y = this->y / f;

	return r;
}

CVector2D CVector2D::operator+(const float& v)
{
	CVector2D r;
	r.x = this->x + v;
	r.y = this->y + v;
	return r;
}

CVector2D CVector2D::Normalize()
{
	CVector2D r;
	float normal = GetMagnitude();
	r.x = x / normal;
	r.y = y / normal;
	return r;
}

CVector2D CVector2D::DistanceTo(const CVector2D& v)
{
	CVector2D r;
	float distance;
	r.x = (v.x - this->x);
	r.y = (v.y - this->y);
	if (r.x == 0 && r.y == 0)
		return CVector2D(0, 0);
	distance = sqrt(pow(r.x, 2) + pow(r.y, 2));
	r.x = r.x / distance;
	r.y = r.y / distance;
	return r;
}

float CVector2D::Theta(CVector2D position)
{
	// position 과 (1,0)의 내적을 바탕으로 cos(theta)를 구한다.
	float costheta = position.x / sqrt(pow(position.x, 2) + pow(position.y, 2));
	float theta = acos(costheta);
	return theta * 52.2954;
}

float CVector2D::GetMagnitude()
{
	float normal;
	normal = sqrt(pow(x, 2) + pow(y, 2));
	return normal;
}