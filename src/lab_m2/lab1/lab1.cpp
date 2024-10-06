#include <algorithm>

#include "lab_m2/lab1/lab1.h"


using namespace std;
using namespace m2;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    minInstances = 8;
    maxInstances = 16;
    nrInstances = minInstances;

    min_scale_coeff = 0.1f;
    max_scale_coeff = 2.0f;
    step_scale_coeff = 0.25f;
    scale_coeff = 1.0f;

    auto camera = GetSceneCamera();
    camera->SetPositionAndRotation(glm::vec3(0, 5, 4), glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
    camera->Update();

    // Load a mesh from file into GPU memory
    {
        Mesh* mesh = new Mesh("bamboo");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation", "bamboo"), "bamboo.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for rendering to texture
    {
        Shader *shader = new Shader("Instances");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M2, "lab1", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M2, "lab1", "shaders", "GeometryShader.glsl"), GL_GEOMETRY_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M2, "lab1", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    ClearScreen();

    {
        auto shader = shaders["Instances"];

        shader->Use();

        int loc_instances = shader->GetUniformLocation("instances");
        glUniform1i(loc_instances, nrInstances);

        // student: Add a shrinking parameter for scaling each
        // triangle in the geometry shader
        glUniform1f(shader->GetUniformLocation("scale_coeff"), scale_coeff);

        // Note that we only render a single mesh!
        RenderMesh(meshes["bamboo"], shaders["Instances"], glm::vec3(-3.3f, 0.5f, 0), glm::vec3(0.1f));
    }
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input with window->KeyHold()

    // student: Add events for modifying the shrinking parameter
    const float deltaScale = step_scale_coeff * deltaTime;

    if (window->KeyHold(GLFW_KEY_K))
    {
        scale_coeff = min(scale_coeff + deltaScale, max_scale_coeff);
    }
    if (window->KeyHold(GLFW_KEY_J))
    {
        scale_coeff = max(scale_coeff - deltaScale, min_scale_coeff);
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event

    if (key == GLFW_KEY_EQUAL)
    {
        nrInstances = min(nrInstances + 1, maxInstances);
    }

    if (key == GLFW_KEY_MINUS)
    {
        nrInstances = max(nrInstances - 1, minInstances);
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
