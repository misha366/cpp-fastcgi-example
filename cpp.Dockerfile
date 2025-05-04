FROM gcc:latest
WORKDIR /app/

RUN apt-get update && apt-get install -y libfcgi-dev

ENTRYPOINT g++ -lfcgi -o fastcgi_manager main.cpp && ./fastcgi_manager
