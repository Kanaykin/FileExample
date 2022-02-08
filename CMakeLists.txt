cmake_minimum_required(VERSION 3.10)

# set the project name
project(ResourcesRepositoryExample)

# add the executable
set(SOURCES Main.cpp Threaded.hpp ResourcesFile.hpp ResourcesRepository.hpp SingleThreaded.hpp)
add_executable(ResourcesRepositoryExample ${SOURCES})