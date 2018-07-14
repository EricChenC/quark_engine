set(DEPS "D:/depend_library")

include_directories(
${DEPS}/glm
${DEPS}
${DEPS}/vulkan/include
${DEPS}/fbx/include
${PROJECT_SOURCE_DIR}/engine/core
${PROJECT_SOURCE_DIR}/engine/render/vulkan
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

link_directories(
${DEPS}/vulkan/lib
${DEPS}/fbx/lib/x64
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(QT_USE_QTOPENGL ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

file(GLOB SOURCE ./*.*)
add_executable(quark ${SOURCE})

target_link_libraries(
quark 
engine
vulkan-1
Qt5::Core 
Qt5::Widgets
)