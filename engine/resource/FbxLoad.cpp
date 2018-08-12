#include "FbxLoad.h"
#include "Scene.h"
#include "QuarkObject.h"
#include "Mesh.h"
#include "MeshFilter.h"
#include "Transform.h"

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <fbxsdk.h>


#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))
#endif

void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
void GetContent(FbxScene* pScene, std::shared_ptr<qe::core::Scene> scene);
void GetContent(FbxNode* pNode, std::shared_ptr<qe::core::QuarkObject> node);
void GetMesh(FbxNode* pNode, std::shared_ptr<qe::core::QuarkObject> node);
void GetPolygons(FbxMesh* pMesh, std::shared_ptr<qe::core::Mesh> mesh);
void GetProperties(FbxObject* pObject, std::shared_ptr<qe::core::QuarkObject> node);

void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);


std::shared_ptr<qe::core::Scene> qe::resource::FBXLoad::Load(const std::string & path)
{
    auto kscene = std::make_shared<qe::core::Scene>();

    FbxManager* lSdkManager = NULL;
    FbxScene* lScene = NULL;
    bool lResult;

    // Prepare the FBX SDK.
    InitializeSdkObjects(lSdkManager, lScene);
    // Load the scene.

    FbxString lFilePath(path.c_str());
    if (lFilePath.IsEmpty())
    {
        lResult = false;
    }
    else
    {
        lResult = LoadScene(lSdkManager, lScene, lFilePath.Buffer());
    }

    if (lResult == false)
    {
    }
    else
    {
        if (gVerbose) GetContent(lScene, kscene);
    }

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);

    return kscene;
}

void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
    //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    pManager = FbxManager::Create();
    if (!pManager)
    {
        exit(1);
    }

    //Create an IOSettings object. This object holds all import/export settings.
    FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
    pManager->SetIOSettings(ios);

    //Load plugins from the executable directory (optional)
    FbxString lPath = FbxGetApplicationDirectory();
    pManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    pScene = FbxScene::Create(pManager, "My Scene");
    if (!pScene)
    {
        exit(1);
    }
}

bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
{
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor, lSDKMinor, lSDKRevision;
    //int lFileFormat = -1;
    int i, lAnimStackCount;
    bool lStatus;
    char lPassword[1024];

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    FbxImporter* lImporter = FbxImporter::Create(pManager, "");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if (!lImportStatus)
    {
        return false;
    }

    if (lImporter->IsFBX())
    {

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

        lAnimStackCount = lImporter->GetAnimStackCount();

        // Set the import states. By default, the import states are always set to 
        // true. The code below shows how to change these states.
        IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
        IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
        IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
        IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
        IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
        IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
        IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    }

    // Import the scene.
    lStatus = lImporter->Import(pScene);

    if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
    {
        lPassword[0] = '\0';

        FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
            scanf("%s", lPassword);
        FBXSDK_CRT_SECURE_NO_WARNING_END

            FbxString lString(lPassword);

        IOS_REF.SetStringProp(IMP_FBX_PASSWORD, lString);
        IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

        lStatus = lImporter->Import(pScene);

    }

    // Destroy the importer.
    lImporter->Destroy();

    return lStatus;
}

void GetContent(FbxScene* pScene, std::shared_ptr<qe::core::Scene> scene)
{
    int i;
    FbxNode* lNode = pScene->GetRootNode();
    auto root = scene->AddRoot();

    if (lNode)
    {
        for (i = 0; i < lNode->GetChildCount(); i++)
        {
            auto node = std::make_shared<qe::core::QuarkObject>();
            root->AddChild(node);

            GetContent(lNode->GetChild(i), node);
        }
    }
}

void GetContent(FbxNode* pNode, std::shared_ptr<qe::core::QuarkObject> node)
{
    FbxNodeAttribute::EType lAttributeType;
    int i;

    if (pNode->GetNodeAttribute() != NULL)
    {
        lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

        switch (lAttributeType)
        {
        default:
            break;
        case FbxNodeAttribute::eMesh:
        {
            GetMesh(pNode, node);
            break;
        }
        }
    }

    for (i = 0; i < pNode->GetChildCount(); i++)
    {
        auto child_node = std::make_shared<qe::core::QuarkObject>();
        node->AddChild(child_node);

        GetContent(pNode->GetChild(i), child_node);
    }
}

void GetMesh(FbxNode* pNode, std::shared_ptr<qe::core::QuarkObject> node)
{
    FbxMesh* lMesh = (FbxMesh*)pNode->GetNodeAttribute();
    auto meshFilter = node->AddComponent<qe::core::MeshFilter>();
    auto mesh = std::make_shared<qe::core::Mesh>();
    meshFilter->set_mesh(mesh);

    GetProperties(pNode, node);
    GetPolygons(lMesh, mesh);
}

void GetProperties(FbxObject* pObject, std::shared_ptr<qe::core::QuarkObject> node)
{

    // Display all the properties
    int i, lCount = 0;
    FbxProperty lProperty = pObject->GetFirstProperty();
    while (lProperty.IsValid())
    {
        lCount++;
        lProperty = pObject->GetNextProperty(lProperty);
    }

    FbxString lTitleStr = "    Property Count: ";

    if (lCount == 0)
        return; // there are no properties to display

    node->set_name((char *)pObject->GetName());
    auto transform = node->GetComponent<qe::core::Transform>();

    i = 0;
    lProperty = pObject->GetFirstProperty();
    while (lProperty.IsValid())
    {
        // exclude user properties

        FbxString lString;
        lString = lProperty.GetLabel();
        lString = lProperty.GetName();
        lString = lProperty.GetPropertyDataType().GetName();

        switch (lProperty.GetPropertyDataType().GetType())
        {
        case eFbxBool:
            break;

        case eFbxDouble:
            break;

        case eFbxDouble4:
        {
            FbxColor lDefault;
            char      lBuf[64];

            lDefault = lProperty.Get<FbxColor>();
            FBXSDK_sprintf(lBuf, 64, "R=%f, G=%f, B=%f, A=%f", lDefault.mRed, lDefault.mGreen, lDefault.mBlue, lDefault.mAlpha);
        }
        break;

        case eFbxInt:
            break;

        case eFbxDouble3:
        {
            FbxDouble3 lDefault;
            char   lBuf[64];

            lDefault = lProperty.Get<FbxDouble3>();
            FBXSDK_sprintf(lBuf, 64, "X=%f, Y=%f, Z=%f", lDefault[0], lDefault[1], lDefault[2]);

            if (lProperty.GetName() == "Lcl Translation") {
                transform->set_local_translation(glm::vec3(lDefault[0], lDefault[1], lDefault[2]));
            }
            
            if (lProperty.GetName() == "Lcl Rotation") {
                transform->set_local_rotate(glm::vec3(lDefault[0], lDefault[1], lDefault[2]));
            }

            if (lProperty.GetName() == "Lcl Scaling") {
                transform->set_local_scale(glm::vec3(lDefault[0], lDefault[1], lDefault[2]));
            }

        }
        break;
        case eFbxFloat:
            break;
        case eFbxString:
            lString = lProperty.Get<FbxString>();
            break;

        default:
            break;
        }
        i++;
        lProperty = pObject->GetNextProperty(lProperty);
    }
}

void GetPolygons(FbxMesh* pMesh, std::shared_ptr<qe::core::Mesh> mesh)
{
    int i, j, lPolygonCount = pMesh->GetPolygonCount();
    FbxVector4* lControlPoints = pMesh->GetControlPoints();
    char header[100];

    auto vertexs = std::make_shared<std::vector<glm::vec3>>();
    auto uvs = std::make_shared<std::vector<glm::vec2>>();
    auto normals = std::make_shared<std::vector<glm::vec3>>();

    int vertexId = 0;
    for (i = 0; i < lPolygonCount; i++)
    {
        int l;

        std::vector<glm::vec3> face_vertexs;
        std::vector<glm::vec2> face_uvs;
        std::vector<glm::vec3> face_normals;

        for (l = 0; l < pMesh->GetElementPolygonGroupCount(); l++)
        {
            FbxGeometryElementPolygonGroup* lePolgrp = pMesh->GetElementPolygonGroup(l);
            switch (lePolgrp->GetMappingMode())
            {
            case FbxGeometryElement::eByPolygon:
                if (lePolgrp->GetReferenceMode() == FbxGeometryElement::eIndex)
                {
                    FBXSDK_sprintf(header, 100, "        Assigned to group: ");
                    int polyGroupId = lePolgrp->GetIndexArray().GetAt(i);
                    break;
                }
            default:
                // any other mapping modes don't make sense
                break;
            }
        }

        int lPolygonSize = pMesh->GetPolygonSize(i);

        for (j = 0; j < lPolygonSize; j++)
        {
            int lControlPointIndex = pMesh->GetPolygonVertex(i, j);

            auto point = lControlPoints[lControlPointIndex];

            glm::vec3 vertex((float)point[0], (float)point[1], (float)point[2]);
            face_vertexs.push_back(vertex);

            for (l = 0; l < pMesh->GetElementVertexColorCount(); l++)
            {
                FbxGeometryElementVertexColor* leVtxc = pMesh->GetElementVertexColor(l);
                FBXSDK_sprintf(header, 100, "            Color vertex: ");

                switch (leVtxc->GetMappingMode())
                {
                default:
                    break;
                case FbxGeometryElement::eByControlPoint:
                    switch (leVtxc->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        break;
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                    break;

                case FbxGeometryElement::eByPolygonVertex:
                {
                    switch (leVtxc->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        break;
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leVtxc->GetIndexArray().GetAt(vertexId);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                }
                break;

                case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
                case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
                case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
                    break;
                }
            }
            for (l = 0; l < pMesh->GetElementUVCount(); ++l)
            {
                FbxGeometryElementUV* leUV = pMesh->GetElementUV(l);
                FBXSDK_sprintf(header, 100, "            Texture UV: ");

                switch (leUV->GetMappingMode())
                {
                default:
                    break;
                case FbxGeometryElement::eByControlPoint:
                    switch (leUV->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    {
                        auto fbx_uv = leUV->GetDirectArray().GetAt(lControlPointIndex);
                        glm::vec2 uv((float)fbx_uv[0], (float)fbx_uv[1]);
                        face_uvs.push_back(uv);
                        break;
                    }
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
                        auto fbx_uv = leUV->GetDirectArray().GetAt(id);
                        glm::vec2 uv((float)fbx_uv[0], (float)fbx_uv[1]);
                        face_uvs.push_back(uv);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                    break;

                case FbxGeometryElement::eByPolygonVertex:
                {
                    int lTextureUVIndex = pMesh->GetTextureUVIndex(i, j);
                    switch (leUV->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        auto fbx_uv = leUV->GetDirectArray().GetAt(lTextureUVIndex);
                        glm::vec2 uv((float)fbx_uv[0], (float)fbx_uv[1]);
                        face_uvs.push_back(uv);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                }
                break;

                case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
                case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
                case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
                    break;
                }
            }

            for (l = 0; l < pMesh->GetElementNormalCount(); ++l)
            {
                FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(l);
                FBXSDK_sprintf(header, 100, "            Normal: ");

                if (leNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (leNormal->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    {
                        auto fbx_normal = leNormal->GetDirectArray().GetAt(vertexId);
                        glm::vec3 normal((float)fbx_normal[0], (float)fbx_normal[1], (float)fbx_normal[2]);
                        face_normals.push_back(normal);
                        break;
                    }
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leNormal->GetIndexArray().GetAt(vertexId);
                        auto fbx_normal = leNormal->GetDirectArray().GetAt(id);
                        glm::vec3 normal((float)fbx_normal[0], (float)fbx_normal[1], (float)fbx_normal[2]);
                        face_normals.push_back(normal);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                }

                if (leNormal->GetMappingMode() == FbxGeometryElement::eByControlPoint) {
                    if (leNormal->GetReferenceMode() == FbxGeometryElement::eDirect) {

                        auto fbx_normal = leNormal->GetDirectArray().GetAt(i);
                        glm::vec3 normal((float)fbx_normal[0], (float)fbx_normal[1], (float)fbx_normal[2]);
                        face_normals.push_back(normal);
                    }
                }


            }
            for (l = 0; l < pMesh->GetElementTangentCount(); ++l)
            {
                FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent(l);
                FBXSDK_sprintf(header, 100, "            Tangent: ");

                if (leTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (leTangent->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        break;
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leTangent->GetIndexArray().GetAt(vertexId);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                }

            }
            for (l = 0; l < pMesh->GetElementBinormalCount(); ++l)
            {

                FbxGeometryElementBinormal* leBinormal = pMesh->GetElementBinormal(l);

                FBXSDK_sprintf(header, 100, "            Binormal: ");
                if (leBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (leBinormal->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        break;
                    case FbxGeometryElement::eIndexToDirect:
                    {
                        int id = leBinormal->GetIndexArray().GetAt(vertexId);
                    }
                    break;
                    default:
                        break; // other reference modes not shown here!
                    }
                }
            }
            vertexId++;
        } // for polygonSize

        if (face_vertexs.size() == 4) {
            vertexs->push_back(face_vertexs[0]);
            vertexs->push_back(face_vertexs[1]);
            vertexs->push_back(face_vertexs[2]);

            vertexs->push_back(face_vertexs[0]);
            vertexs->push_back(face_vertexs[2]);
            vertexs->push_back(face_vertexs[3]);

            uvs->push_back(face_uvs[0]);
            uvs->push_back(face_uvs[1]);
            uvs->push_back(face_uvs[2]);

            uvs->push_back(face_uvs[0]);
            uvs->push_back(face_uvs[2]);
            uvs->push_back(face_uvs[3]);

            normals->push_back(face_normals[0]);
            normals->push_back(face_normals[1]);
            normals->push_back(face_normals[2]);

            normals->push_back(face_normals[0]);
            normals->push_back(face_normals[2]);
            normals->push_back(face_normals[3]);
            
        }
        else if (face_vertexs.size() == 3) {
            vertexs->push_back(face_vertexs[0]);
            vertexs->push_back(face_vertexs[1]);
            vertexs->push_back(face_vertexs[2]);

            uvs->push_back(face_uvs[0]);
            uvs->push_back(face_uvs[1]);
            uvs->push_back(face_uvs[2]);

            normals->push_back(face_normals[0]);
            normals->push_back(face_normals[1]);
            normals->push_back(face_normals[2]);
          
        }

        face_vertexs.swap(std::vector<glm::vec3>());
        face_uvs.swap(std::vector<glm::vec2>());
        face_normals.swap(std::vector<glm::vec3>());

    } // for polygonCount

    mesh->set_vertexs(vertexs);
    mesh->set_vertexs_count(vertexs->size());
    mesh->set_uvs(uvs);
    mesh->set_uvs_count(uvs->size());
    mesh->set_normals(normals);
    mesh->set_normals_count(normals->size());

    auto indexs = std::make_shared<std::vector<unsigned int>>();
    for (int i = 0; i < vertexs->size(); i++) {
        indexs->push_back(i);
    }

    mesh->set_indexs(indexs);
    mesh->set_indexs_count(indexs->size());
}

void DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
{
    //Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
    if (pManager) pManager->Destroy();
}