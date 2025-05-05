# Simple FastCGI manager on C++

1. `docker compose up`
2. open `http://localhost`


receives a fastcgi request from a web server and generates a response with a hello world html page, the requested route, and the user agent


if we start accepting the `SCRIPT_FILENAME` parameter (absolute path to the executable file) in our main.cpp, launch, for example, the php interpreter for this file and send the resulting html via fastcgi, we will end up with a simplified version of php-fpm.

the purpose of managers is to accept many connections, for each of which the gateway will decide which file the manager should execute, the manager itself will raise workers with an interpreter for each such request and return the response back to the gateway.

Even if the backend and gateway are on different hosts, their file systems must be synchronized to avoid conflicts when requesting executable files.

<b>This is the essence of this project - to show how fastcgi under the hood forms lines for an http response, which it will then transmit to the web server via fastcgi.</b>
