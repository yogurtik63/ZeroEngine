cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME ZeroEngine)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Renderer/Texture2D.cpp
	src/Renderer/Texture2D.h
	src/Renderer/Sprite.cpp
	src/Renderer/Sprite.h
	src/Renderer/VertexBuffer.cpp
	src/Renderer/VertexBuffer.h
	src/Renderer/IndexBuffer.cpp
	src/Renderer/IndexBuffer.h
	src/Renderer/VertexArray.cpp
	src/Renderer/VertexArray.h
	src/Renderer/VertexBufferLayout.cpp
	src/Renderer/VertexBufferLayout.h
	src/Renderer/Renderer.cpp
	src/Renderer/Renderer.h
	src/Renderer/SpriteAnimator.cpp
	src/Renderer/SpriteAnimator.h
	
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
	src/Resources/stb_image.h
	
	src/Game/Game.cpp
	src/Game/Game.h
	
	src/Game/GameStates/IGameState.h
	src/Game/GameStates/StartScreen.cpp
	src/Game/GameStates/StartScreen.h
	src/Game/GameStates/Level.cpp
	src/Game/GameStates/Level.h
	
	src/System/Timer.cpp
	src/System/Timer.h
	
	src/Physics/PhysicsEngine.cpp
	src/Physics/PhysicsEngine.h
	
	src/Game/GameObjects/Player.cpp
	src/Game/GameObjects/Player.h
	src/Game/GameObjects/Home.cpp
	src/Game/GameObjects/Home.h
	src/Game/GameObjects/Grass.cpp
	src/Game/GameObjects/Grass.h
	src/Game/GameObjects/Empty.cpp
	src/Game/GameObjects/Empty.h
	src/Game/GameObjects/Tree.cpp
	src/Game/GameObjects/Tree.h
	src/Game/GameObjects/Log.cpp
	src/Game/GameObjects/Log.h
	src/Game/GameObjects/Bullet.cpp
	src/Game/GameObjects/Bullet.h
	src/Game/GameObjects/Stone.cpp
	src/Game/GameObjects/Stone.h
	src/Game/GameObjects/Border.cpp
	src/Game/GameObjects/Border.h
	src/Game/GameObjects/IGameObject.cpp
	src/Game/GameObjects/IGameObject.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)