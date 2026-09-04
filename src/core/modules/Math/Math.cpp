#include "Math.h"
#include <cmath>
#include <numbers>

namespace core::modules::Math {
	namespace {
		bool Initialized = false;
        const double DEG2RAD_FACTOR = std::numbers::pi / 180.0;
        const double RAD2DEG_FACTOR = 180.0 / std::numbers::pi;
	}
    bool Init() {
        if (Initialized) {
            return true;
        }
        Initialized = true;
        return true;
    }
    double sin(double deg) {
        return std::sin(deg * DEG2RAD_FACTOR);
    }
    double cos(double deg) {
        return std::cos(deg * DEG2RAD_FACTOR);
    }
    double tan(double deg) {
        return std::tan(deg * DEG2RAD_FACTOR);
    }
    double atan2(double dy, double dx) {
        return std::atan2(dy, dx) * RAD2DEG_FACTOR;
    }
    double deg2rad(double deg) {
        return deg * DEG2RAD_FACTOR;
    }
    double rad2deg(double rad) {
        return rad * RAD2DEG_FACTOR;
    }
    void Shutdown() {
        if (!Initialized) {
            return;
        }
        Initialized = false;
    }
}