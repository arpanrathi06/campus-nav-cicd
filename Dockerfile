FROM gcc:latest
WORKDIR /app
COPY main.cpp .
RUN g++ -o campus_nav smart.cpp
CMD ["./campus_nav"]
