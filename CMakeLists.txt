cmake_minimum_required(VERSION 3.0.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(myserver server.c)

add_executable(myserver server.c thread_pool.c thread_pool.h segel.c segel.h request.h request.h client.c output.c)