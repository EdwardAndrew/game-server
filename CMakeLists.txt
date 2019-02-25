cmake_minimum_required(VERSION 2.6)
set (CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-pthread")
SET(PROJECT_NAME game-server)
SET(CMAKE_CONFIGURATION_TYPES Debug)
SET(BOOST_1_69_PATH "C:/Boost/boost_1_69_0" CACHE PATH "Boost 1.69.0 Path")
SET(GLM_PATH "C:/glm" CACHE PATH "GLM path")
SET(HEADER_FILES
	Client.h
	ClientState.h
	Config.h
	ConnectionHandler.h
	MessageQueue.h
	PacketMapper.h
	PacketTypes.h
	Player.h
	UDPCommunication.h
)
SET(SOURCES
	Client.cpp
	ConnectionHandler.cpp
	MessageQueue.cpp
	PacketMapper.cpp
	Player.cpp
	UDPCommunication.cpp
	game-server.cpp
)

IF (WIN32)
    include_directories("${GLM_PATH}/include")
    include_directories("${BOOST_1_69_PATH}")
    link_directories("${BOOST_1_69_PATH}/stage/lib")
    add_executable(server game-server.cpp ${HEADER_FILES} ${SOURCES})
ELSE()

    find_package(Boost REQUIRED system)
    if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
    endif()
    find_package(glm)

    add_executable(server game-server.cpp ${HEADER_FILES} ${SOURCES})

    target_link_libraries(server LINK_PUBLIC ${Boost_LIBRARIES} glm)

ENDIF()




