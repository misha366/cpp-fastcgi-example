# Sample FastCGI manager on C++

1. `docker compose up`
2. open `http://localhost`


receives a fastcgi request from a web server and generates a response with a hello world html page, the requested route, and the user agent


if in the lines with the formation of responses we will check the URL received from `envp` with the existing php files in the system of our server and in case of their COINCIDENCE call the php interpreter in a separate process for the file whose path matched - we will get a simplified analogue of php-fpm.


<b>This is the essence of this project - to show how fastcgi under the hood forms lines for an http response, which it will then transmit to the web server via fastcgi.</b>
