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
#include "cube.h"

void InputHandler(Window* gameWindow, const u8* keystate);


int main(int argc, char* args[]){
    Window editorWindow = Window(1280, 720, "Creation Editor");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(editorWindow.GetWindow() ,editorWindow.GetGLContext());
    ImGui_ImplOpenGL3_Init("#version 130");


    Shader gridShader = Shader("grid_vertex.glsl", "grid_fragment.glsl");
    Shader cubeShader = Shader("cube_vertex.glsl", "cube_fragment.glsl");
    Camera viewport = Camera(glm::vec3{0});

    Grid grid = Grid(11);
    Cube cube = Cube(glm::vec3{0,0,0});
    bool show_demo_window = true;

    while(!editorWindow.WindowShouldClose()){

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&show_demo_window);

        editorWindow.PollEvents();
        const u8* keystate = SDL_GetKeyboardState(NULL); 
        InputHandler(&editorWindow, keystate);
        
        viewport.Update(keystate, glm::vec3{0,0,0});
        glm::mat4 perspective = viewport.GetProjectMatrix();
        glm::mat4 view = viewport.GetViewMatrix();
        
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1,0.1,0.1,1.0);  

        gridShader.UseProgram();
            glUniformMatrix4fv(0, 1, false, glm::value_ptr(perspective));
            glUniformMatrix4fv(1, 1, false, glm::value_ptr(view));
        grid.Draw();

        cubeShader.UseProgram();
            glUniformMatrix4fv(0, 1, false, glm::value_ptr(perspective));
            glUniformMatrix4fv(1, 1, false, glm::value_ptr(view));
        cube.Draw();

        ImGui::Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());    

        editorWindow.SwapBuffers();
    }

    return 0;
}


void InputHandler(Window* gameWindow, const u8* keystate){
    SDL_Event e = gameWindow->GetEvent();
    ImGui_ImplSDL2_ProcessEvent(&e);

    if(e.type == SDL_QUIT){
        gameWindow->Quit();
    }
    if(keystate[SDL_SCANCODE_ESCAPE]){
        gameWindow->Quit();    
    }
}