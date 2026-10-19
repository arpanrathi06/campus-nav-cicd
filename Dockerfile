FROM gcc:latest
WORKDIR /app
COPY smart.cpp .
RUN g++ -o campus_nav smart.cpp
CMD ["./campus_nav"]
