#pragma once


namespace core::modules::Math {
	bool Init();
	void Shutdown();
	double sin(double deg);
	double cos(double deg);
	double tan(double deg);
	double atan2(double dy, double dx);
	double deg2rad(double deg);
	double rad2deg(double rad);
}