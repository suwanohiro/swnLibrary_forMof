#pragma once

namespace swn::Math {
	/// <summary>
	/// 円周率
	/// </summary>
	constexpr double pi = 3.141592653589793;

	/// <summary>
	/// 度数をラジアンに変換するための係数
	/// </summary>
	constexpr double DEG_TO_RAD_FACTOR = 1.0 / 180.0;

	/// <summary>
	/// 度数をラジアンに変換する
	/// </summary>
	/// <param name="deg">度数</param>
	/// <returns>ラジアン</returns>
	double toRadian(double deg);

	/// <summary>
	/// 度数をラジアンに変換する (float)
	/// </summary>
	/// <param name="deg">度数</param>
	/// <returns>ラジアン</returns>
	float tofRadian(float deg) { return (float)toRadian(deg); }
}
