cmake_minimum_required(VERSION 2.8)

project(EndlessRunner)

set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake-modules/")

set(SRCS
	src/AnimationMgr.cpp        
	src/BoxCollider.cpp         
	src/CircleCollider.cpp      
	src/Coin.cpp              
	src/Collideable.cpp
	src/EndlessCliff.cpp
	src/Game.cpp
	src/Global.cpp
	src/Hero.cpp
	src/Island.cpp
	src/main.cpp
	src/ScreenRenderer.cpp
	src/SoundMgr.cpp
	src/Sphere.cpp
)

set(HEADERS
	src/AnimationMgr.h          
	src/BoxCollider.h           
	src/CircleCollider.h      
	src/Coin.h                
	src/Collideable.h
	src/Collider.h
	src/EndlessCliff.h
	src/Game.h
	src/Global.h
	src/Hero.h
	src/Input.h
	src/Island.h
	src/ScreenRenderer.h
	src/SoundMgr.h
	src/Sphere.h
)

set(SDL2_ROOT_DIR CACHE PATH "SDL2 root directory")
set(SFML_ROOT CACHE PATH "SFML root directory")

# As for now before I create FindFHL.cmake file
set(FHL_ROOT_DIR CACHE PATH "FHL root directory")
set(FHL_LIBRARY_DEBUG CACHE FILEPATH "FHL debug lib")
set(FHL_LIBRARY_RELEASE CACHE FILEPATH "FHL release lib")
set(FHL_LIBRARIES
		optimized 	${FHL_LIBRARY_RELEASE}
		debug		${FHL_LIBRARY_DEBUG}
)
set(FHL_INCLUDE_DIR ${FHL_ROOT_DIR}/src/ ${FHL_ROOT_DIR}/src/FHL/GL/)

add_executable(EndlessRunner ${HEADERS} ${SRCS})

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SRCS})

find_package(SFML 2 COMPONENTS system audio REQUIRED)
find_package(SDL2 REQUIRED)

target_include_directories(EndlessRunner PUBLIC ${SDL2_INCLUDE_DIR} ${SFML_INCLUDE_DIR} ${FHL_INCLUDE_DIR})
target_link_libraries(EndlessRunner ${SDL2_LIBRARY} ${SFML_LIBRARIES} ${FHL_LIBRARIES})
	