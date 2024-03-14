#include "animator.h"



Animator::Animator(u32 keyframeCount, u32 frameTime){
    this->keyFramesCount = keyframeCount;
    this->frameTime = frameTime;

    keyframes = (KeyFrame*)calloc(keyframeCount, sizeof(KeyFrame));
}



Animator::~Animator(){
    free(keyframes);
}

void Animator::SetupAnimatorUI(){
    ImGui::Begin("Timeline");
            ImGui::SeparatorText("Keyframes");
            if(ImGui::Button("Play")){

            } ImGui::SameLine();
            if(ImGui::Button("Pause")){

            } ImGui::SameLine();
            if(ImGui::Button("Reset")){
                currentFrame = 0;
            }

            if(ImGui::Button("Save keyframe")){
                
            } ImGui::SameLine();
            if(ImGui::Button("Delete keyframe")){
                                
            }
            ImGui::Text("Keyframe count: %d ", keyFramesCount); ImGui::SameLine();
            
            ImGui::PushButtonRepeat(true);
            if(ImGui::ArrowButton("##left", ImGuiDir_Left)) { 
                keyFramesCount--;
                if(keyFramesCount < 0){
                    keyFramesCount = 0;
                }
            }
            ImGui::SameLine();
            if(ImGui::ArrowButton("##right", ImGuiDir_Right)) { 
                keyFramesCount++;
                if(keyFramesCount > 40){
                    keyFramesCount = 40;
                }
            }
            ImGui::PopButtonRepeat();

            ImGui::Text("Current frame: %d", currentFrame);
            ImGui::Text("Has keyframe: %d", keyframes[currentFrame].hasKeyframe);            
            for(i32 i = 0; i < keyFramesCount; i++){
                if(ImGui::Button(std::to_string(i).c_str())){
                    currentFrame = i;
                }
                ImGui::SameLine();
            }
        ImGui::End();
}
