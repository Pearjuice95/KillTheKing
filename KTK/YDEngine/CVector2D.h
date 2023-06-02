#pragma once

class CVector2D
{
public:
	CVector2D()
	{
		x = 0;
		y = 0;
	}
	CVector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float x;
	float y;

	CVector2D operator+(const CVector2D& v);
	CVector2D operator-(const CVector2D& v);

	CVector2D operator*(const float& v);
	CVector2D operator/(const float& v);

	CVector2D operator+(const float& v);

	CVector2D Normalize(); // 단위 벡터를 생성함
	
	CVector2D DistanceTo(const CVector2D& _to);
	
	float Theta(CVector2D position);
private:
	float GetMagnitude();

};