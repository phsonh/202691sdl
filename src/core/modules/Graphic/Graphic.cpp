#include "Graphic.h"
#include "core/runtime/Log/Log.h"


namespace core::modules::Graphic {
	namespace {
		bool Initialized = false;
	}
	bool Init() {
		if (Initialized)
			return true;

		Initialized = true;

		core::runtime::Log::Debug(
			"Graphic module initialized"
		);

		return true;
	}
	void Shutdown() {
		if (!Initialized)
			return;

		Initialized = false;

		core::runtime::Log::Debug(
			"Graphic module shutdown"
		);
	}
}