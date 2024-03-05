#include "../webui.hpp"
#include "../../../../utils/log.hpp"

using namespace YateUtils;

namespace YatePlugin {

WebUi::WebUi(const std::string& host, std::uint16_t port)
  : UiPlugin("WebUi"),
    m_server_socket(-1),
    m_server(host, port)
{

}

void WebUi::start()
{
    set_status(YateCore::IPlugin::STATUS::STARTING);
    register_uris();

    std::vector<std::future<void>> futures;
    bool accepting = false;
    m_server.initialize_socket();
    m_server.open_socket(m_server_socket, accepting);
    m_server.bind_socket(m_server_socket);
    m_server.listen_socket(futures, m_server_socket, accepting);
    set_status(YateCore::IPlugin::STATUS::RUNNING);
}

void WebUi::stop()
{
  //m_server.stop();
    bool accepting = false;
    m_server.close_socket(m_server_socket, accepting);
    set_status(YateCore::IPlugin::STATUS::STOPPED);
}

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

void WebUi::register_uris()
{
    /*
  auto provide_file = [](const HttpRequest& request) -> HttpResponse {
    HttpResponse response(HttpStatusCode::Ok);
    std::string mimeType;
    std::getline(std::istringstream(request.header("Accept")), mimeType, ',');
    if(!mimeType.empty()){
      response.add_header("Content-Type", mimeType);
    } else {
      response.add_header("Content-Type", "text/plain");
    }

    log(Log_t::DEBUG, "Request URI %s\n", request.uri().path().c_str());
    if(request.uri().path() == "/"){
      response.set_file_path("frontend/index.html");
    } else {
      response.set_file_path("frontend" + request.uri().path());
    }

    return response;
  };

  auto provide_dir = [](const HttpRequest& request) -> HttpResponse {
    HttpResponse response(HttpStatusCode::Ok);
    std::string mimeType;
    std::getline(std::istringstream(request.header("Accept")), mimeType, ',');
    if(!mimeType.empty()){
      response.SetHeader("Content-Type", mimeType);
    } else {
      response.SetHeader("Content-Type", "text/plain");
    }
    return response;
  };

  auto provide_open_file = [this](const HttpRequest& request) -> HttpResponse {

      HttpResponse response(HttpStatusCode::Ok);
      std::string file_name = request.query_parameter("file");
      log(Log_t::INFO, "File name:\n%s", file_name.c_str());
      response.SetHeader("Content-Type", "application/json");
      std::string content =  m_wrapper->get_document(file_name);
      log(Log_t::INFO, "Content:\n%s", content.c_str());
      response.SetContent(content);
      return response;
  };

  m_server.register_uri_handler("/", HttpMethod::HEAD, provide_file);
  m_server.register_uri_handler("/", HttpMethod::GET, provide_file);

  m_server.register_uri_handler("/css/style.css", HttpMethod::HEAD, provide_file);
  m_server.register_uri_handler("/css/style.css", HttpMethod::GET, provide_file);

  m_server.register_uri_handler("/open", HttpMethod::HEAD, provide_open_file);
  m_server.register_uri_handler("/open", HttpMethod::GET, provide_open_file);
  */

    auto provide_file = [](const HttpRequest& http_request) -> HttpResponse {
        std::cout << "Preparing file for serving..." << http_request.path() << std::endl;
        HttpResponse http_response;
        http_response.set_status_code(HttpStatusCode::Ok);
        const std::string& accept_content = http_request.header("Accept");
        std::string path = http_request.path();

        if(path == "/"){
            path = "./frontend/index.html";
        } else {
            path.insert(0, "./frontend");
        }

        const std::string file_ext = path.substr(path.find('.', 2)+1);
        log(Log_t::DEBUG, "File extension: %s\n", file_ext.c_str());
        std::string mime_type = file_extension_to_mime_type(file_ext);//accept_content.substr(0, accept_content.find(","));

        if (std::ifstream ifs { path }) {
            std::cout << "File opened " << http_request.path() << std::endl;
            std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            // use data here
            //std::cout << data << '\n';
            http_response.set_content(data);
        } else {
            http_response.set_status_code(HttpStatusCode::NotFound);
            std::cout << "Cannot open file\n";
        }
        http_response.add_header("Content-Length", std::to_string(http_response.content().length()));
        http_response.add_header("Content-Type", mime_type);
        return http_response;
    };

    auto provide_open_file = [](const HttpRequest& http_request) -> HttpResponse {
        std::cout << "Preparing file for serving... " << http_request.query_parameter("file") << std::endl;
        HttpResponse http_response;
        http_response.set_status_code(HttpStatusCode::Ok);
        const std::string& accept_content = http_request.header("Accept");
        std::string mime_type = accept_content.substr(0, accept_content.find(","));
        std::string path = http_request.query_parameter("file");
        if(path == "/"){
            path = "./frontend/index.html";
        } else {
            path.insert(0, "./frontend");
        }

        if (std::ifstream ifs { path }) {
            std::cout << "File opened " << path << std::endl;
            std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            // use data here
            //std::cout << data << '\n';
            http_response.set_content(data);
        } else {
            http_response.set_status_code(HttpStatusCode::NotFound);
            std::cout << "Cannot open file " << path << std::endl;
        }
        http_response.add_header("Content-Length", std::to_string(http_response.content().length()));
        http_response.add_header("Content-Type", mime_type);
        return http_response;
    };

    auto post_file = [](const HttpRequest& http_request) -> HttpResponse {
        HttpResponse http_response;
        http_response.set_status_code(HttpStatusCode::Created);
        http_response.add_header("Content-Length", "0");
        log(Log_t::DEBUG, "POST REQUEST");
        //http_request.content();

        return http_response;
    };

    m_server.register_uri_handler("/", HttpMethod::GET, provide_file);
    m_server.register_uri_handler("/index.html", HttpMethod::GET, provide_file);
    m_server.register_uri_handler("/index.html", HttpMethod::POST, post_file);
    m_server.register_uri_handler("/css/style.css", HttpMethod::GET, provide_file);
    m_server.register_uri_handler("/css/prism.css", HttpMethod::GET, provide_file);
    m_server.register_uri_handler("/js/main.js", HttpMethod::GET, provide_file);
    m_server.register_uri_handler("/js/prism.js", HttpMethod::GET, provide_file);
    m_server.register_uri_handler("/open", HttpMethod::GET, provide_open_file);
}

}
