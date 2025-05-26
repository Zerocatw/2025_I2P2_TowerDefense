
#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP

#include "Engine/IScene.hpp"
#include "Engine/IObject.hpp"
class ScoreBoardScene final : public Engine::IScene {
private:
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
};
#endif   // SCOREBOARDSCENE_HPP
