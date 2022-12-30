cmake_minimum_required(VERSION 3.0.0)
project(web_client_linux VERSION 0.1.0)

include(CTest)
enable_testing()

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
include_directories(INCLUDE_DIR )


add_executable(web_client_linux ${CMAKE_SOURCE_DIR}/main.cpp ${INCLUDE_DIR}/Util.h ${INCLUDE_DIR}/Socket.h ${INCLUDE_DIR}/Socket.cpp ${INCLUDE_DIR}/SocketException.h )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
