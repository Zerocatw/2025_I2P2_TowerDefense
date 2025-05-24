#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Engine/IObject.hpp"
#include "PlayScene.hpp"
#include "StageSelectScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreBoardScene.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

struct Player{
    std::string name;
    int score;
    std::string date;
    std::string time;
};

int cmp(const void* a, const void* b){ // Score -> Name_Acsii -> Date -> Time
    const Player* player_a = (const Player*)a;
    const Player* player_b = (const Player*)b;
    if(player_a->score != player_b->score) return player_a->score > player_b->score ? -1:1;
    if(player_a->name != player_b->name)  return player_a->name < player_b->name ? -1:1;
    if(player_a->date != player_b->date) return player_a->date < player_b->date ? -1:1;
    if(player_a->time != player_b->time) return player_a->time < player_b->time ? -1:1;
    return 0;
}

void ScoreBoardScene::Initialize() {
    std::cout << "hello!\n";
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    // scoreboard
    AddNewObject(new Engine::Label("SCOREBOARD", "pirulen.ttf", 48, halfW, halfH / 3-50, 10, 255, 255, 255, 0.5, 0.5));
    page_label.clear();
    std::ifstream UserData("../SaveGame.txt");
    std::string user;
    std::string name, date, time;
    int score;
    std::vector<Player> players;
    while (UserData >> name >> score >> date >> time) {
        players.push_back({name, score, date + " " + time});
    }
    qsort(players.data(), players.size(), sizeof(Player), cmp);


    int lineNum = 0;
    int starthigh = halfH / 3;
    int linehigh = 60;
    for(int i = 0; i < players.size(); i++){
        int y = starthigh + lineNum * linehigh;
        std::string user = players[i].name + " " + std::to_string(players[i].score) + " " + players[i].date + " " + players[i].time;
        auto nowlable = new Engine::Label(user, "pirulen.ttf", 35, halfW, y, 255, 255, 255, 0, 0.5, 0);
        page_label.push_back(nowlable);
        lineNum++;
        if(lineNum == 5){// record 5
            lineNum = 0;
        }
    }
    for (int i = 0; i < page_label.size(); ++i) {
        AddNewObject(page_label[i]);
    }
    Engine::ImageButton *btn;
    // Back
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2+20, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2+70, 0, 0, 0, 255, 0.5, 0.5));
    // Prev page
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2+20, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PREV PAGE", "pirulen.ttf", 48, halfW-500, halfH * 3 / 2+70, 0, 0, 0, 255, 0.5, 0.5));
    // Next page
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW+300, halfH * 3 / 2+20, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("NEXT PAGE", "pirulen.ttf", 48, halfW+500, halfH * 3 / 2+70, 0, 0, 0, 255, 0.5, 0.5));
    crtpage = 0;
    ReloadPage();
}
void ScoreBoardScene::Terminate() {
    crtpage = 0;
    IScene::Terminate();
}


void ScoreBoardScene::ReloadPage() {
    int start = crtpage * limit_page_num; 
    int end   = std::min((int)page_label.size(), start + limit_page_num);
    for (int i = 0; i < page_label.size(); i++) {
        if (i >= start && i < end) {
            // 顯示這一頁的 Label
            page_label[i]->Color = al_map_rgba(255, 255, 255, 255);
            std::cout << "suss\n";
        } else {
            // 隱藏其他 Label
            page_label[i]->Color = al_map_rgba(255, 255, 255, 0);
        }
    }
}

void ScoreBoardScene::BackOnClick(int stage) {
    crtpage = 0;
    ReloadPage();
    std::cout <<"set invis!\n";
    for(auto it:page_label){
        it->Color = al_map_rgba(255, 255, 255, 0);
    }
    int range = std::min(std::max(5, (int)page_label.size()), (int)page_label.size());
    std::cout <<"set vail!\n";
    for(int i = 0; i < range; i++){
        page_label[i]->Color = al_map_rgba(255, 255, 255, 255);
    }
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void ScoreBoardScene::PlayOnClick(int stage) {
    std::cout <<"stage : " <<  stage << "\n";
    std::cout <<"crtpage : " <<  crtpage << "\n";
    if(stage == 1){ // prev page
        if(crtpage>0){
            crtpage--;
            ReloadPage();
        }
    }
    else if(stage == 2){ // next page
        if((crtpage+1)*5 < page_label.size()){
            crtpage++;
            ReloadPage();
        }   
    }
}
