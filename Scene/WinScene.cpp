#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"
#include "PlayScene.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

int WinScene::finalScore = 0;
std::string GetCurrentDateTime() { // GET LOCAL TIME
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void WinScene::Initialize() {
    nowTime = GetCurrentDateTime();
    std::cout << "Now time : " << nowTime << "\n";
    std::cout << "Score : " << finalScore << "\n";
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");
    // username input
    Engine::ImageButton *inputbox;
    inputbox = new Engine::ImageButton("win/InputBox.png", "win/InputBox.png", halfW/2, halfH / 4+23, 800, 70);
    inputbox->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this,2));
    AddNewControlObject(inputbox);
    record_username = "TEST"; // default
    UserName = new Engine::Label(record_username, "pirulen.ttf", 48, halfW/2+20, halfH / 4+25, 255, 255, 255);
    AddNewObject(UserName);
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}

void WinScene::OnKeyDown(int keyCode){// username input
    IScene::OnKeyDown(keyCode);
    std::cout << "now " << keyCode << "\n";
    if(keyCode>=ALLEGRO_KEY_A && keyCode<= ALLEGRO_KEY_Z){
        char input = 'A' + (keyCode-ALLEGRO_KEY_A);
        record_username+=input;
        UserName->Text = record_username;
    }
    else if(keyCode>=ALLEGRO_KEY_0 && keyCode<= ALLEGRO_KEY_9){
        char input = '0' + (keyCode-ALLEGRO_KEY_0);
        record_username+=input;
        UserName->Text = record_username;
    }
    else if(keyCode==ALLEGRO_KEY_BACKSPACE && !record_username.empty()){ // DELETE
        record_username.pop_back();
        UserName->Text = record_username;
    }
}


void WinScene::BackOnClick(int stage) {
    std::ofstream outputfile("../SaveGame.txt", std::ios::app);
    if (outputfile.is_open()) {// record formate : username score date
        outputfile << UserName->Text << " " << finalScore << " " << nowTime << "\n";
        outputfile.close();
    } else {
        std::cout << "Error\n";
    }

    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
