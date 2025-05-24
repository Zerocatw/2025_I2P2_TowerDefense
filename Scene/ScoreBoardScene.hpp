
#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
#include "Engine/IObject.hpp"
class ScoreBoardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<Engine::Label*> page_label;
    int crtpage = 0;
    const int limit_page_num = 5;
public:
    explicit ScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void BackOnClick(int stage);
    void ReloadPage();
   //void Update(float deltaTime) override;
};
#endif   // SCOREBOARDSCENE_HPP
