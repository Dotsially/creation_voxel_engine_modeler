#define SDL_MAIN_HANDLED
#include "depedencies.h"
#include "window.h"
#include "camera.h"
#include "texture.h"
#include "mesh.h"
#include "shader.h"
#include "grid.h"
#include "cube.h"

void InputHandler(Window* gameWindow, const u8* keystate);


int main(int argc, char* args[]){
    Window editorWindow = Window(1280, 720, "Creation Editor");

    Shader gridShader = Shader("grid_vertex.glsl", "grid_fragment.glsl");
    Shader cubeShader = Shader("cube_vertex.glsl", "cube_fragment.glsl");
    Camera viewport = Camera(glm::vec3{-3, 10, -3});

    Grid grid = Grid(11);
    Cube cube = Cube(glm::vec3{5.5,0,5.5});
    while(!editorWindow.WindowShouldClose()){
        editorWindow.PollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1,0.1,0.1,1.0);        
        const u8* keystate = SDL_GetKeyboardState(NULL);  

        viewport.Update(keystate, glm::vec3{5.5,0,5.5});

        glm::mat4 perspective = viewport.GetProjectMatrix();
        glm::mat4 view = viewport.GetViewMatrix();

        InputHandler(&editorWindow, keystate);

        gridShader.UseProgram();
            glUniformMatrix4fv(0, 1, false, glm::value_ptr(perspective));
            glUniformMatrix4fv(1, 1, false, glm::value_ptr(view));
        grid.Draw();

        cubeShader.UseProgram();
            glUniformMatrix4fv(0, 1, false, glm::value_ptr(perspective));
            glUniformMatrix4fv(1, 1, false, glm::value_ptr(view));
        cube.Draw();


        editorWindow.SwapBuffers();
    }

    return 0;
}


void InputHandler(Window* gameWindow, const u8* keystate){
    SDL_Event e = gameWindow->GetEvent();
    if(e.type == SDL_QUIT){
        gameWindow->Quit();
    }
    if(keystate[SDL_SCANCODE_ESCAPE]){
        gameWindow->Quit();    
    }
}