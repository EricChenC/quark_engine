set(DEPS "D:/depend_library")

file(GLOB CORE core/*.*)
file(GLOB RENDER render/vulkan/*.*)
file(GLOB RESOURCE resource/*.*)

source_group("Core" FILES ${CORE})
source_group("Render\\Vulkan" FILES ${RENDER})
source_group("Resource" FILES ${RESOURCE})

set(SHADER_DIR ../media/shader/)
file(GLOB SHADERS "${SHADER_DIR}/*.bat" "${SHADER_DIR}/*.shader" "${SHADER_DIR}/*.vert" "${SHADER_DIR}/*.frag" "${SHADER_DIR}/*.geom" "${SHADER_DIR}/*.tesc" "${SHADER_DIR}/*.tese")

source_group("Resource\\Shaders" FILES ${SHADERS})

include_directories(
${DEPS}
${DEPS}/glm
${DEPS}/vulkan/include
${DEPS}/boost_1_64_0
${DEPS}/stb
${DEPS}/fbx/include
core
render/vulkan
resource
)

link_directories(
${DEPS}/vulkan/lib
${DEPS}/fbx/lib/x64
)

add_library(engine SHARED ${CORE} ${RENDER} ${RESOURCE} ${SHADERS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

target_link_libraries( 
engine
vulkan-1
libfbxsdk-md
)

include (GenerateExportHeader)

GENERATE_EXPORT_HEADER(
engine        
EXPORT_MACRO_NAME dll_EXPORTS
)




































