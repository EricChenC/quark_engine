#include "Transform.h"


qe::core::Transform::Transform()
    : 
    local_rotate_(glm::vec3(0.0, 0.0, 0.0)),
    world_rotate_(glm::vec3(0.0, 0.0, 0.0)),
    local_scale_(glm::vec3(1.0, 1.0, 1.0)),
    world_scale_(glm::vec3(1.0, 1.0, 1.0)),
    local_translation_(glm::vec3(0.0, 0.0, 0.0)),
    world_translation_(glm::vec3(0.0, 0.0, 0.0))
{

}

qe::core::Transform::~Transform()
{
}



