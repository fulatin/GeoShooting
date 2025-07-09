#pragma once
#include <cmath>
namespace GeoShooting
{
	class Vector {
	public:
		float x, y; // 向量的x和y分量
		Vector(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
		// 向量加法
		Vector operator+(const Vector& other) const {
			return Vector(x + other.x, y + other.y);
		}
		// 向量减法
		Vector operator-(const Vector& other) const {
			return Vector(x - other.x, y - other.y);
		}
		// 向量乘以标量
		Vector operator*(float scalar) const {
			return Vector(x * scalar, y * scalar);
		}
		// 向量除以标量
		Vector operator/(float scalar) const {
			return Vector(x / scalar, y / scalar);
		}
		float length() const {
			return sqrt(x * x + y * y);
		}
		float distance(const Vector& other) const {
			return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
		}
		void normalize() {
			float len = length();
			if (len > 0) {
				x /= len;
				y /= len;
			}
		}
		// 向量旋转
		Vector rotate(float radians) {
			float cosTheta = cos(radians);
			float sinTheta = sin(radians);
			return Vector(x * cosTheta - y * sinTheta, x * sinTheta + y * cosTheta);
		}
	};
}