#ifndef WEBUI_HPP
#define WEBUI_HPP

#include <uiplugin.hpp>
#include <httpserver.hpp>

namespace YatePlugin {
class WebUi : public UiPlugin {
public:
    explicit WebUi(const std::string& host, std::uint16_t port);
    virtual void start();
    virtual void stop();
private:
    SOCKET m_server_socket;
    HttpServer m_server;

    void register_uris();
};
}
#endif
