FROM gcc:latest
WORKDIR /app/
ENTRYPOINT g++ -o main main.cpp && ./main
