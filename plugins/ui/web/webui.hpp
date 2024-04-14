#ifndef WEBUI_HPP
#define WEBUI_HPP

#include <iuiplugin.hpp>
#include <httpserver.hpp>

namespace Yate::Plugin {

class WebUi : public Core::Api::IUiPlugin {
public:
    explicit WebUi(const std::string& host, std::uint16_t port);

    //virtual void onCoreUpdateMessage(const Utils::Event& event) override;
protected:
    virtual void start_plugin() override;
    virtual void stop_plugin() override;

    virtual void notify_frontend(const std::string& event, const std::string& msg);

private:
    Http::Server m_server;
    Http::EventSource m_event_source;

    void register_uris();
};

} // end namespace Yate::Plugin
#endif
