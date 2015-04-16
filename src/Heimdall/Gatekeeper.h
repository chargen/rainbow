// Copyright (c) 2010-15 Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#ifndef HEIMDALL_GATEKEEPER_H_
#define HEIMDALL_GATEKEEPER_H_

#ifdef USE_HEIMDALL

#include <mutex>
#include <unordered_map>

#include "Common/List.h"
#include "Director.h"
#include "Heimdall/ChangeMonitor.h"
#include "Heimdall/DebugInfo.h"
#include "Heimdall/Overlay.h"
#include "Heimdall/OverlayActivator.h"
#include "Input/InputListener.h"

struct Touch;

namespace heimdall
{
	/// Overlay for debugging options.
	class Gatekeeper final : public rainbow::Director, public InputListener
	{
	public:
		Gatekeeper();

		/* Director overrides */

		void draw()
		{
			Director::draw();
			scenegraph_.draw();
		}

		void init(const Vec2i &screen);
		void update(const unsigned long dt);

	private:
#if !defined(USE_LUA_SCRIPT) || USE_LUA_SCRIPT
		List<std::unique_ptr<char[]>> changed_files_;
#endif  // USE_LUA_SCRIPT
		Overlay overlay_;
		OverlayActivator overlay_activator_;
		std::unique_ptr<DebugInfo> info_;
		SceneGraph::Node scenegraph_;
		std::unordered_map<unsigned int, Button*> pressed_;
#if !defined(USE_LUA_SCRIPT) || USE_LUA_SCRIPT
		std::mutex changed_files_mutex_;
		ChangeMonitor monitor_;
#endif  // USE_LUA_SCRIPT

		void post_init();
		void pre_init(const Vec2i &screen);

		/* Implement InputListener */

		bool on_touch_began_impl(const unsigned int,
		                         const Touch *const) override;
		bool on_touch_canceled_impl() override;
		bool on_touch_ended_impl(const unsigned int,
		                         const Touch *const) override;
		bool on_touch_moved_impl(const unsigned int,
		                         const Touch *const) override;
	};
}

using Director = heimdall::Gatekeeper;

#endif  // USE_HEIMDALL
#endif  // HEIMDALL_GATEKEEPER_H_
