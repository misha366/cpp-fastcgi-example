#include <string>
#include <cstring>
#include "fcgi_stdio.h"
#include <stdlib.h>

// извлечение нужных переменных окружения
const char* get_env(FCGX_ParamArray envp, const char* key) {
    for (int i = 0; envp[i]; ++i) {
        if (strncmp(envp[i], key, strlen(key)) == 0 && envp[i][strlen(key)] == '=') {
            return envp[i] + strlen(key) + 1;
        }
    }
    return nullptr;
}

int main(int argc, char* const argv[]) {

    std::string port = ":9000";

    int listenQueueBacklog = 400; // глубина стека запросов

    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp; // массив переменных окружения по спецификации cgi

    if (FCGX_Init()) exit(1);

    int listen_socket = FCGX_OpenSocket(port.c_str(), listenQueueBacklog); // сокет, который будет слушать веб сервер
    if (listen_socket < 0) exit(1);

    FCGX_Request request;

    if (FCGX_InitRequest(&request, listen_socket, 0)) exit(1);

    while (FCGX_Accept_r(&request) == 0) { // ждём входящий запрос от nginx
        // как только запрос приходит он заполнит request данными

        const char* user_agent = get_env(request.envp, "HTTP_USER_AGENT");
        const char* uri = get_env(request.envp, "REQUEST_URI");

        // записываем строки хттп ответа для передачи по fastcgi обратно на сервер
        FCGX_FPrintF(request.out, "Content-type: text/html\r\n\r\n");
        FCGX_FPrintF(request.out, "<title>Hello, world</title>\n");
        FCGX_FPrintF(request.out, "<h1>Fastcgi: Hello world.</h1>\n");
        
        if (user_agent) {
            FCGX_FPrintF(request.out, "<p>User-Agent: %s</p>\n", user_agent);
        }

        if (uri) {
            FCGX_FPrintF(request.out, "<p>URI: %s</p>\n", uri);
        }
        
        FCGX_Finish_r(&request); // завершает орбаботку текущего запроса и передаёт запрос на сервер
    }

    return 0;
}
