#include "../webui.hpp"
#include "../../../../utils/log.hpp"

using namespace Yate::Utils;

namespace Yate::Plugin {

constexpr const char* DOMAIN = "YPLUGIN:UI";

std::string file_extension_to_mime_type(const std::string& file_ext){
    if(file_ext == "html" || file_ext == "htm"){
        return "text/html";
    } else if(file_ext == "css") {
        return "text/css";
    } else if(file_ext == "js"){
        return "text/javascript";
    } else if(file_ext == "json"){
        return "application/json";
    }
    // TODO ...
    return "text/plain";
}

WebUi::WebUi(const std::string& host, std::uint16_t port)
  : Core::Api::IUiPlugin("WebUi"),
    m_server(host, port),
    m_event_source()
{

}

void WebUi::start_plugin()
{
    register_uris();
    m_server.start();
}

void WebUi::stop_plugin()
{
    m_server.stop();
}

void WebUi::notify_frontend(const std::string& event, const std::string& msg)
{
    m_event_source.send_event("event: " + event + "\ndata:" + msg + "\n\n");
}

void WebUi::register_uris()
{
    auto on_receive_frontend_file_request = [](const HttpRequest& http_request, HttpResponse& http_response) {
        log(Log_t::INFO, DOMAIN, "Preparing for delivery of '%s'\n", http_request.path().c_str());
        http_response.set_status_code(HttpStatusCode::Ok);
        const std::string& accept_content = http_request.header("Accept");
        std::string path = http_request.path();

        if(path == "/"){
            path = "./frontend/index.html";
        } else {
            path.insert(0, "./frontend");
        }

        const std::string file_ext = path.substr(path.find('.', 2)+1);
        log(Log_t::DEBUG, DOMAIN, "File extension: %s\n", file_ext.c_str());
        std::string mime_type = file_extension_to_mime_type(file_ext);//accept_content.substr(0, accept_content.find(","));

        if (std::ifstream ifs { path }) {
            log(Log_t::DEBUG, DOMAIN, "File %s opened\n", path.c_str());
            std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            http_response.set_content(data);
        } else {
            http_response.set_status_code(HttpStatusCode::NotFound);
            log(Log_t::ERROR, DOMAIN, "Cannot open file %s\n", path.c_str());
        }
        http_response.add_header("Content-Length", std::to_string(http_response.content().length()));
        http_response.add_header("Content-Type", mime_type);
        return http_response;
    };

    auto on_receive_file_cmd_request = [this](const HttpRequest& http_request, HttpResponse& http_response) {
        log(Log_t::DEBUG, DOMAIN, "Command request received\n");

        emit_event("cmd_request", http_request.content());

        http_response.set_status_code(HttpStatusCode::Ok);
        http_response.set_version(HttpVersion::Http_11);
        http_response.add_header("Content-Length", std::to_string(http_response.content().length()));
        log(Log_t::VERBOSE, DOMAIN, "Command request processed\n");
        return http_response;
    };

    m_server.register_uri_handler("/", HttpMethod::GET, on_receive_frontend_file_request);
    m_server.register_uri_handler("/index.html", HttpMethod::GET, on_receive_frontend_file_request);
    m_server.register_uri_handler("/css/style.css", HttpMethod::GET, on_receive_frontend_file_request);
    m_server.register_uri_handler("/js/main.js", HttpMethod::GET, on_receive_frontend_file_request);
    //m_server.register_uri_handler("/js/highlightWorker.js", HttpMethod::GET, on_receive_frontend_file_request);

    m_server.register_uri_handler("/cmd", HttpMethod::POST, on_receive_file_cmd_request);

    m_server.register_event("/event", &m_event_source);
}

} // end namespace Yate::Plugin
