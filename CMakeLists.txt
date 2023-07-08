cmake_minimum_required(VERSION 3.13)
project(GeographicInformationSystem)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES GIS.cpp SystemManager.cpp SystemManager.hpp
CommandProcessor.cpp CommandProcessor.hpp PRQuadTree.cpp PRQuadTree.hpp
GISRecord.cpp GISRecord.hpp Storage.cpp Storage.hpp HashTable.cpp
HashTable.hpp DMS.cpp DMS.hpp Logger.cpp Logger.hpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(GeographicInformationSystem ${SOURCE_FILES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GeographicInformationSystem)