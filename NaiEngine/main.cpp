#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include "Mesh3d.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"
#include "EditorGrid.hpp"

using namespace std;

const char* vertexShaderSource = R"(
#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 atexCoord;
layout (location=3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // The model matrix now includes scaling, so this calculation is simpler.
  vec4 worldPos = model * vec4(aPos, 1.0);
  fragPos = vec3(worldPos);
  gl_Position = projection * view * worldPos;
  vertexColor = aColor;
  texCoord = atexCoord;
  normal = normalize(mat3(transpose(inverse(model))) * aNormal);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D mytexture; 
uniform float ambientIntensity;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
  vec3 ambientLight = ambientIntensity * lightColor;
  vec3 norm = normalize(normal);
  vec3 lightDirection = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuseLight = diff * lightColor;

  vec3 lighting = ambientLight + diffuseLight;
  FragColor = vec4(lighting, 1.0) * texture(mytexture, texCoord);
}
)";

// --- Shaders for the Editor Grid and Axes ---
const char* lineVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 lineColor;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    lineColor = aColor;
}
)";

const char* lineFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec3 lineColor;
void main()
{
    FragColor = vec4(lineColor, 1.0);
}
)";

unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);
    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader_id;
}

unsigned int createShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

unsigned int createShaderProgram()
{
    return createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

int main(void)
{
    if (!glfwInit()) { return -1; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "NaiEngine", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { return -1; }
    glViewport(0, 0, 1280, 720);
    glEnable(GL_DEPTH_TEST);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    EditorGrid grid(20.0f, 20);

    SoundManager::GetInstance().AddSound("music", "assets/Start.mp3");
    SoundManager::GetInstance().AddSound("impact", "assets/yuno-miles-robot.mp3");
    SoundManager::GetInstance().Play("music");

    unsigned int cubeShaderProgram = createShaderProgram();
    Texture texture("assets/brick.jpg");
    Mesh cube = Mesh::CreateCube(1.0f);

    glm::vec3 position = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float size = 1.0f;

    glm::vec3 cam_position(2.0f, 3.0f, 8.0f);
    glm::vec3 cam_center(0.0f, 0.0f, 0.0f);
    float cameraFov = 45.0f;

    float ambientIntensity = 0.2f;
    glm::vec3 lightPos(3.0f, 5.0f, 3.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    
    static float masterVolume = 1.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cam_position, cam_center, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(cameraFov), 1280.0f / 720.0f, 0.1f, 100.0f);

        grid.Draw(view, projection);

        glUseProgram(cubeShaderProgram);
        texture.Bind(0);
        glUniform1i(glGetUniformLocation(cubeShaderProgram, "mytexture"), 0);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(size));

        glUniformMatrix4fv(glGetUniformLocation(cubeShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glUniform1f(glGetUniformLocation(cubeShaderProgram, "ambientIntensity"), ambientIntensity);
        glUniform3fv(glGetUniformLocation(cubeShaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(cubeShaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
        
        cube.Draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Inspector");
        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", &position.x, 0.01f);
        ImGui::DragFloat3("Rotation", &rotation.x, 1.0f, -360.0f, 360.0f);
        ImGui::SliderFloat("Size", &size, 0.1f, 3.0f);
        ImGui::Separator();
        ImGui::Text("Camera");
        ImGui::DragFloat3("Cam Position", &cam_position.x, 0.05f);
        ImGui::DragFloat3("Cam Center", &cam_center.x, 0.05f);
        ImGui::SliderFloat("Zoom (FOV)", &cameraFov, 1.0f, 90.0f);
        ImGui::Separator();
        ImGui::Text("Lighting");
        ImGui::DragFloat3("Light Position", &lightPos.x, 0.1f);
        ImGui::ColorEdit3("Light Color", &lightColor.x);
        ImGui::SliderFloat("Ambient Intensity", &ambientIntensity, 0.0f, 1.0f);
        ImGui::Separator();
        ImGui::Text("Audio");
        if (ImGui::Button("Play Impact Sound")) { SoundManager::GetInstance().Play("impact"); }
        if (ImGui::SliderFloat("Master Volume", &masterVolume, 0.0f, 1.0f)) { SoundManager::GetInstance().SetVolume(masterVolume); }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}