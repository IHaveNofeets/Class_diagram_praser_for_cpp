cmake_minimum_required(VERSION 3.5)

project(class_diagram LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(class_diagram main.cpp
    aLine.h aLine.cpp
    aClass.h aClass.cpp
    Loader.h Loader.cpp
    EnumClass.h EnumClass.cpp
    StructClass.h StructClass.cpp
    Arrow.h Arrow.cpp)

find_package(Qt6 REQUIRED COMPONENTS Sql)

include(GNUInstallDirs)
install(TARGETS class_diagram
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_link_libraries(class_diagram PRIVATE Qt6::Sql)
