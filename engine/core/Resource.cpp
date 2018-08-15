#include "Resource.h"
#include "QuarkString.h"
#include "FbxLoad.h"
#include "TextureLoad.h"
#include "ShaderLoad.h"
#include "QuarkObject.h"
#include "Texture.h"
#include "Shader.h"

qe::core::Resource::Resource()
{
    fbx_load_ = std::make_shared <resource::FBXLoad > ();
    texture_load_ = std::make_shared<resource::TextureLoad>();
    shader_load_ = std::make_shared<resource::ShaderLoad>();
}

qe::core::Resource::~Resource()
{
}

std::shared_ptr<qe::core::CoreObject> qe::core::Resource::Load(const std::string & path)
{
    auto format = qe::core::QuarkString::FileFormat(path);
    if (format == "obj" || format == "fbx") {
        return std::dynamic_pointer_cast<qe::core::CoreObject>(fbx_load_->Load(path));
    }
    else if (format == "jpg" || format == "png") {
        return std::dynamic_pointer_cast<qe::core::CoreObject>(texture_load_->Load(path));
    }
    else if (format == "shader") {
        return std::dynamic_pointer_cast<qe::core::CoreObject>(shader_load_->Load(path));
    }

    return nullptr;
}




