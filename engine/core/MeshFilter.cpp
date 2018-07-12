#include "MeshFilter.h"
#include "Mesh.h"

qe::core::MeshFilter::MeshFilter()
{

}

qe::core::MeshFilter::~MeshFilter()
{

}

auto qe::core::MeshFilter::get_mesh() -> std::shared_ptr<Mesh>
{
    return mesh_;
}

void qe::core::MeshFilter::set_mesh(std::shared_ptr<Mesh> mesh)
{
    mesh_ = mesh;
}
