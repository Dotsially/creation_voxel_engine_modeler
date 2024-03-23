#define SDL_MAIN_HANDLED
#include "depedencies.h"
#include "window.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "camera.h"
#include "texture.h"
#include "mesh.h"
#include "shader.h"
#include "grid.h"
#include "node.h"
#include "animator.h"
#include "sekai_reader.h"

void InputHandler(Window* gameWindow, const u8* keystate, Camera* camera);


int main(int argc, char* args[]){
    Window editorWindow = Window(1280, 720, "Creation Editor");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(editorWindow.GetWindow() ,editorWindow.GetGLContext());
    ImGui_ImplOpenGL3_Init("#version 130");

    SekaiReader sekaiReader;
    Shader gridShader = Shader("grid_vertex.glsl", "grid_fragment.glsl");
    Shader cubeShader = Shader("cube_vertex.glsl", "cube_fragment.glsl");
    Camera viewport = Camera(glm::vec3{0});

    Grid grid = Grid(16);
    
    glm::fvec3 selectPosition = glm::fvec3{0};
    glm::fvec3 selectRotation = glm::fvec3{0};
    glm::fvec3 selectSize = glm::fvec3{1};
    glm::fvec3 selectPivot = glm::fvec3{0};
    glm::fvec3 targetPosition = glm::fvec3{0};

    Node nodes;
    Animator animator = Animator(30, 60);


    
    while(!editorWindow.WindowShouldClose()){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        ImGui::ShowIDStackToolWindow();

        ImGui::Begin("Hierachy");
            if(ImGui::Button("Save")){
                sekaiReader.SaveModel(nodes.GetItems());
            } ImGui::SameLine();
            if(ImGui::Button("Load")){
                sekaiReader.LoadModel(&nodes, "model.json");
            }  
            ImGui::DragFloat3("Translation", glm::value_ptr(selectPosition), 1);
            ImGui::DragFloat3("Rotation", glm::value_ptr(selectRotation),1, -360, 360);
            ImGui::DragFloat3("Size", glm::value_ptr(selectSize),0.5);
            
            ImGui::DragFloat3("Pivot", glm::value_ptr(selectPivot),0.5);

            ImGui::SameLine();
            if(ImGui::Button("Center")){
                nodes.CenterCube(&selectPivot);
            }

            if(ImGui::Button("Cube")){
                nodes.AddCube();
            } ImGui::SameLine();
            if(ImGui::Button("Bone")){
                nodes.AddBone();
            } ImGui::SameLine();
            if(ImGui::Button("Delete")){
                nodes.DeleteNode();
            }

            nodes.SetupNodeUI(&selectPosition, &selectRotation, &selectSize, &selectPivot);
			
        ImGui::End();

        nodes.Update(selectPosition, selectRotation, selectSize, selectPivot);
        animator.SetupAnimatorUI();

        editorWindow.PollEvents();
        const u8* keystate = SDL_GetKeyboardState(NULL); 
        InputHandler(&editorWindow, keystate, &viewport);
        

        if(keystate[SDL_SCANCODE_SPACE]){
            targetPosition.y += 0.1f;
        }
        else if(keystate[SDL_SCANCODE_LSHIFT]){
            targetPosition.y -= 0.1f;
        }

        viewport.Update(keystate, targetPosition);


        glm::mat4 perspective = viewport.GetProjectMatrix();
        glm::mat4 view = viewport.GetViewMatrix();
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1,0.1,0.1,1.0);  

        gridShader.UseProgram();
            glUniformMatrix4fv(0, 1, false, glm::value_ptr(perspective));
            glUniformMatrix4fv(1, 1, false, glm::value_ptr(view));
        grid.Draw();

        cubeShader.UseProgram();
            glUniformMatrix4fv(0, 1, false, glm::value_ptr	(perspective));
            glUniformMatrix4fv(1, 1, false, glm::value_ptr(view));
        nodes.Draw();

        ImGui::Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());    

        editorWindow.SwapBuffers();
    }
    

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return 0;
}


void InputHandler(Window* gameWindow, const u8* keystate, Camera* camera){
    SDL_Event e = gameWindow->GetEvent();
    ImGui_ImplSDL2_ProcessEvent(&e);

    if(e.type == SDL_MOUSEWHEEL){
        i32 y = e.wheel.y;
        camera->UpdateTargetDistance(y);
    }

    if(e.type == SDL_QUIT){
        gameWindow->Quit();
    }
    if(keystate[SDL_SCANCODE_ESCAPE]){
        gameWindow->Quit();    
    }
}