#pragma once
#include <cmath>
namespace GeoShooting
{
	class Vector {
	public:
		float x, y; // ������x��y����
		Vector(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
		// �����ӷ�
		Vector operator+(const Vector& other) const {
			return Vector(x + other.x, y + other.y);
		}
		// ��������
		Vector operator-(const Vector& other) const {
			return Vector(x - other.x, y - other.y);
		}
		// �������Ա���
		Vector operator*(float scalar) const {
			return Vector(x * scalar, y * scalar);
		}
		// �������Ա���
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
		// ������ת
		Vector rotate(float radians) {
			float cosTheta = cos(radians);
			float sinTheta = sin(radians);
			return Vector(x * cosTheta - y * sinTheta, x * sinTheta + y * cosTheta);
		}
	};
}