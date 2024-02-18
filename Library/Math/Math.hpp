#pragma once

namespace swn::Math {
	/// <summary>
	/// �~����
	/// </summary>
	constexpr double pi = 3.141592653589793;

	/// <summary>
	/// �x�������W�A���ɕϊ����邽�߂̌W��
	/// </summary>
	constexpr double DEG_TO_RAD_FACTOR = 1.0 / 180.0;

	/// <summary>
	/// �x�������W�A���ɕϊ�����
	/// </summary>
	/// <param name="deg">�x��</param>
	/// <returns>���W�A��</returns>
	double toRadian(double deg);

	/// <summary>
	/// �x�������W�A���ɕϊ����� (float)
	/// </summary>
	/// <param name="deg">�x��</param>
	/// <returns>���W�A��</returns>
	float tofRadian(float deg) { return (float)toRadian(deg); }
}
