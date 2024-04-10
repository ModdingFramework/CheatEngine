#pragma once

#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace CheatEngine::Plugin {

    class CheatEnginePlugin {
    public:
        enum class Status {
            Uninitialized,
            Initialized,
            Disabled,
            Enabled,
        };

    private:
        Status _status = Status::Uninitialized;

        // Plugin name provided by Cheat Engine when enabled
        std::optional<int> _pluginId = std::nullopt;

        // User-specified plugin name
        std::string _pluginName;

        // Callbacks which return a bool and can be used to cancel the operation
        std::vector<std::function<bool()>> _pluginInitCallbacks;
        std::vector<std::function<bool()>> _pluginEnableCallbacks;
        std::vector<std::function<bool()>> _pluginDisableCallbacks;

        // Callbacks which do not return a value
        std::vector<std::function<void()>> _onPluginInitCallbacks;
        std::vector<std::function<void()>> _onPluginEnableCallbacks;
        std::vector<std::function<void()>> _onPluginDisableCallbacks;

        // Disable the copy constructor and assignment operator
        CheatEnginePlugin(const CheatEnginePlugin&)            = delete;
        CheatEnginePlugin& operator=(const CheatEnginePlugin&) = delete;

    public:
        CheatEnginePlugin()  = default;
        ~CheatEnginePlugin() = default;

        Status           GetStatus() const { return _status; }
        bool             HasPluginId() const { return _pluginId.has_value(); }
        int              GetPluginId() const { return _pluginId.has_value() ? _pluginId.value() : -1; }
        void             SetPluginId(int pluginId) { _pluginId = pluginId; }
        std::string_view GetPluginName() const { return _pluginName; }
        void             SetPluginName(std::string_view pluginName) { _pluginName = pluginName; }
        void RegisterPluginInitCallback(std::function<bool()> callback) { _pluginInitCallbacks.push_back(callback); }
        void RegisterPluginEnableCallback(std::function<bool()> callback) {
            _pluginEnableCallbacks.push_back(callback);
        }
        void RegisterPluginDisableCallback(std::function<bool()> callback) {
            _pluginDisableCallbacks.push_back(callback);
        }
        void RegisterOnPluginInitCallback(std::function<void()> callback) {
            _onPluginInitCallbacks.push_back(callback);
        }
        void RegisterOnPluginEnableCallback(std::function<void()> callback) {
            _onPluginEnableCallbacks.push_back(callback);
        }
        void RegisterOnPluginDisableCallback(std::function<void()> callback) {
            _onPluginDisableCallbacks.push_back(callback);
        }
        bool Initialize() {
            if (_status != Status::Uninitialized) return false;
            for (auto& callback : _pluginInitCallbacks)
                if (!callback()) return false;
            for (auto& callback : _onPluginInitCallbacks) callback();
            _status = Status::Initialized;
            return true;
        }
        bool Enable() {
            if (_status != Status::Initialized) return false;
            for (auto& callback : _pluginEnableCallbacks)
                if (!callback()) return false;
            for (auto& callback : _onPluginEnableCallbacks) callback();
            _status = Status::Enabled;
            return true;
        }
        bool Disable() {
            if (_status != Status::Enabled) return false;
            for (auto& callback : _pluginDisableCallbacks)
                if (!callback()) return false;
            for (auto& callback : _onPluginDisableCallbacks) callback();
            _status = Status::Disabled;
            return true;
        }
    };
}
