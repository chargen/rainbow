// Copyright (c) 2010-present Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#ifndef HEIMDALL_GATEKEEPER_H_
#define HEIMDALL_GATEKEEPER_H_

#if USE_LUA_SCRIPT
#   include <functional>
#   include <queue>
#   include "Heimdall/ChangeMonitor.h"
#   include "Threading/Synchronized.h"
#endif  // USE_LUA_SCRIPT

#include "Director.h"
#include "Heimdall/Overlay.h"
#include "Heimdall/OverlayActivator.h"

namespace heimdall
{
    /// <summary>Overlay for debugging options.</summary>
    class Gatekeeper final
    {
    public:
        Gatekeeper();

        void init(const rainbow::Vec2i& screen);

        bool active() const { return director_.active(); }
        auto error() const { return director_.error(); }
        auto input() -> rainbow::Input& { return director_.input(); }
        auto terminated() const { return director_.terminated(); }

        void draw()
        {
            director_.draw();
            overlay_.draw();
        }

        void terminate() { director_.terminate(); }
        void terminate(const char* error) { director_.terminate(error); }
        void update(uint64_t dt);

        void on_focus_gained() { director_.on_focus_gained(); }
        void on_focus_lost() { director_.on_focus_lost(); }
        void on_memory_warning() { director_.on_memory_warning(); }

    private:
        rainbow::Director director_;
        Overlay overlay_;
        OverlayActivator overlay_activator_;
#if USE_LUA_SCRIPT
        rainbow::Synchronized<std::queue<std::function<void()>>> changed_files_;
        ChangeMonitor monitor_;
#endif  // USE_LUA_SCRIPT
    };
}

using Director = heimdall::Gatekeeper;

#endif  // HEIMDALL_GATEKEEPER_H_
