#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <string>
class WinScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;
public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void OnKeyDown(int keyCode) override;
    Engine::Label *UserName;
    std::string record_username;
    std::string nowTime;
    static int finalScore;
};

#endif   // WINSCENE_HPP
