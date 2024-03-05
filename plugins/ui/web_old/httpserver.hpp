#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstdint>
#include <chrono>
#include <functional>
#include <map>
#include <random>
#include <string>
#include <thread>
#include <utility>

#include "http_message.h"
#include "uri.h"

#include "../uiplugin.hpp"


namespace YatePlugin {

constexpr size_t kMaxBufferSize = 4096;
constexpr size_t kMaxPathLength = 1024;

struct EventData {
  EventData();
  int fd;
  ssize_t content_length;
  size_t length;
  size_t cursor;
  char buffer[kMaxBufferSize];
  char path[kMaxPathLength];
};

using HttpRequestHandler_t = std::function<HttpResponse(const HttpRequest&)>;

class HttpServer {
public:
    explicit HttpServer(const std::string& host, std::uint16_t port);
    ~HttpServer() = default;

    HttpServer() = default;
    HttpServer(HttpServer&&) = default;
    HttpServer& operator=(HttpServer&&) = default;

    virtual void start();
    virtual void stop();

    void register_http_request_handler(const std::string& path, HttpMethod method, const HttpRequestHandler_t callback);
    void register_http_request_handler(const Uri& uri, HttpMethod method, const HttpRequestHandler_t callback);

    inline std::string host() const { return m_host; }
    inline std::uint16_t port() const { return m_port; }
private:
    static constexpr int kBacklogSize = 1000;
    static constexpr int kMaxConnections = 10000;
    static constexpr int kMaxEvents = 10000;
    static constexpr int kThreadPoolSize = 5;

    std::string m_host;
    std::uint16_t m_port;
    int m_sock_fd;
    bool m_running;

    std::thread m_listener_thread;
    std::thread m_worker_threads[kThreadPoolSize];

    int m_worker_epoll_fd[kThreadPoolSize];
    epoll_event m_worker_events[kThreadPoolSize][kMaxEvents];
    std::map<Uri, std::map<HttpMethod, HttpRequestHandler_t>> m_request_handlers;
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_sleep_times;

    void create_socket();
    void setup_epoll();
    void m_listen();
    void process_events(int worker_id);
    void handle_epoll_event(int epoll_fd, EventData* event, std::uint32_t events);
    void handle_http_data(const EventData& request, EventData* response);
    HttpResponse handle_http_request(const HttpRequest& request);


    void control_epoll_event(int epoll_fd, int op, int fd,
                            std::uint32_t events = 0, void* data = nullptr);

    ssize_t send_file(int sockfd, EventData* response);
    void init_frontend();

};

class WebUiServer : public UiPlugin {
public:
    explicit WebUiServer(const std::string& host, std::uint16_t port);
    virtual void start();
    virtual void stop();
private:
    HttpServer m_server;
    //JsonWrapper m_wrapper;

    void init_frontend();
};
}

#endif
